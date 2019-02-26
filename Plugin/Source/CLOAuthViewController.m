// Copyright (C) 2019 Mailbutler GmbH
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  CLOAuthViewController.m
//  CargoLifter
//
//  Created by Fabian Jäger on 13.01.19.
//  Copyright © 2019 Mailbutler. All rights reserved.
//

#import "CLOAuthViewController.h"

#import <WebKit/WebKit.h>
#import "AFOAuth2Manager.h"
#import "AFOAuthCredential.h"
#import "CLOAuthUploader.h"

@interface CLOAuthViewController ()
@property (weak) IBOutlet NSWindow *window;
@property (weak) IBOutlet NSButton *cancelButton;
@property (weak) IBOutlet NSSegmentedControl *navigationButton;

@property (strong) WKWebView* webView;
@property (weak) IBOutlet NSBox *loadingOverlay;
@property (weak) IBOutlet NSProgressIndicator *progressIndicator;

@property (weak) NSWindow* parentWindow;

@property (weak) CLOAuthUploader* service;
@end

@implementation CLOAuthViewController

- (instancetype)initWithNibName:(NSNibName)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if(self = [super initWithNibName:nibNameOrNil bundle:PLUGIN_BUNDLE]) {
        [self loadView];
    }
    return self;
}

- (void)loadView {
    [super loadView];

    WKWebViewConfiguration* nonPersistentConfiguration = [[WKWebViewConfiguration alloc] init];
    nonPersistentConfiguration.websiteDataStore = [WKWebsiteDataStore nonPersistentDataStore];

    WKWebView* webView = [[WKWebView alloc] initWithFrame:CGRectZero configuration:nonPersistentConfiguration];
    webView.translatesAutoresizingMaskIntoConstraints = NO;
    webView.navigationDelegate = self;

    [self.view addSubview:webView];

    self.webView = webView;

    // Add constraints
    NSView* cancelButton = self.cancelButton;
    [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|-0-[webView(450)]-0-|" options:0 metrics:nil views:NSDictionaryOfVariableBindings(webView)]];
    [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|-0-[webView(>=550)]-12-[cancelButton]-|" options:0 metrics:nil views:NSDictionaryOfVariableBindings(webView, cancelButton)]];

    [self.loadingOverlay removeFromSuperview];
    [self.view addSubview:self.loadingOverlay positioned:NSWindowAbove relativeTo:nil];

    NSView* loadingView = self.loadingOverlay;
    [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|-0-[loadingView(450)]-0-|" options:0 metrics:nil views:NSDictionaryOfVariableBindings(loadingView)]];
    [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|-0-[loadingView(>=550)]-12-[cancelButton]-|" options:0 metrics:nil views:NSDictionaryOfVariableBindings(loadingView, cancelButton)]];

    self.loadingOverlay.hidden = NO;

    [self.progressIndicator startAnimation:self];

    // Setup navigation button
    [self.navigationButton setEnabled:false forSegment:0];
    [self.navigationButton setEnabled:false forSegment:1];
}

- (void) authorizeService:(CLOAuthUploader*)uploadService attachedToWindow:(NSWindow*)parentWindow withHandler:(void (^)(BOOL success))completionBlock {
    self.service = uploadService;
    self.parentWindow = parentWindow;

    [self.webView loadRequest:[NSURLRequest requestWithURL:uploadService.oauthStartURL]];

    [self.parentWindow beginSheet:self.window completionHandler:^(NSModalResponse returnCode) {
        [self.window orderOut:nil];

        completionBlock(returnCode == NSModalResponseOK);
    }];
}

- (IBAction)cancel:(id)sender {
    [self.parentWindow endSheet:self.window returnCode:NSModalResponseCancel];
}

- (IBAction)refresh:(id)sender {
    [self.webView reload];
}

- (IBAction)navigate:(NSSegmentedControl*)sender {
    switch (sender.selectedSegment) {
        case 0:
            if([self.webView canGoBack])
                [self.webView goBack];
            break;

        case 1:
            if([self.webView canGoForward])
                [self.webView goForward];
            break;
    }
}

- (void) webView:(WKWebView *)webView didStartProvisionalNavigation:(null_unspecified WKNavigation *)navigation {
    self.loadingOverlay.hidden = NO;
}

- (void) webView:(WKWebView *)webView didFinishNavigation:(WKNavigation *)navigation {
    [self.navigationButton setEnabled:[self.webView canGoBack] forSegment:0];
    [self.navigationButton setEnabled:[self.webView canGoForward] forSegment:1];

    if(![[[webView URL] host] containsString:@"mailbutler.io"]) {
        self.loadingOverlay.animator.hidden = YES;
        return;
    }

    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [webView evaluateJavaScript:@"document.body.textContent" completionHandler:^(id _Nullable textContent, NSError * _Nullable error) {
            [self processCallbackResponse:textContent];
        }];
    });
}

- (void) processCallbackResponse:(NSString*)content {
    if([content isKindOfClass:[NSString class]] && [content containsString:@"success"]) {
        NSError* error;
        NSData* jsonData = [content dataUsingEncoding:NSUTF8StringEncoding];
        NSDictionary* jsonObject = [NSJSONSerialization JSONObjectWithData:jsonData options:0 error:&error];

        if(error == nil) {
            NSString* code = [jsonObject valueForKeyPath:@"credentials.code"];
            if(code) {
                // use code for authentication
                AFOAuth2Manager *OAuth2Manager = [[AFOAuth2Manager alloc] initWithBaseURL:self.service.authBaseURL clientID:self.service.clientID secret:self.service.clientSecret];
                OAuth2Manager.useHTTPBasicAuthentication = NO;

                [OAuth2Manager authenticateUsingOAuthWithURLString:self.service.getTokenPath code:code redirectURI:self.service.redirectURL.absoluteString success:^(AFOAuthCredential *credential) {

                    if( credential == nil ) {
                        NSLog(@"💥 CARGOLIFTER: Failed to decode create OAuth credentials");
                        [self.parentWindow endSheet:self.window returnCode:NSModalResponseStop];
                        return;
                    }

                    // save authentication
                    [AFOAuthCredential storeCredential:credential withIdentifier:self.service.service.uniqueIdentifier];

                    [self.parentWindow endSheet:self.window returnCode:NSModalResponseOK];
                } failure:^(NSError *error) {
                    NSLog(@"💥 CARGOLIFTER: ERROR: %@", error);
                    [self.parentWindow endSheet:self.window returnCode:NSModalResponseStop];
                }];
            }
        } else {
            NSLog(@"💥 CARGOLIFTER: Failed to decode JSON response from OAuth callback: %@", error.localizedDescription);
            [self.parentWindow endSheet:self.window returnCode:NSModalResponseStop];
        }
    }
}

@end
