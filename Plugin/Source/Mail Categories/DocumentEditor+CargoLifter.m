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
//  DocumentEditor+CargoLifter.m
//  CargoLifter
//
//  Created by Fabian Jäger on 22/09/15.
//  Copyright © 2015 Mailbutler. All rights reserved.
//

#import "DocumentEditor+CargoLifter.h"

#import <WebKit/WebKit.h>

#import "NSString+CLAdditions.h"
#import "NSImage+CLAdditions.h"

#import "CLPluginDelegate.h"
#import "CLServicesManager.h"

#import "CLGlobalFunctions.h"

#import "EditingMessageWebView.h"
#import "ComposeBackEnd.h"
#import "MailApp.h"

#import "HeadersEditor+CargoLifter.h"

#import "DOMNode-MailExtras.h"

#import "Reachability.h"

@interface DocumentEditor_CargoLifter ()

@property (nonatomic, strong) CLSendAttachmentsUploadController* cl_uploadController;

- (NSArray*) cl_attachments;
- (NSUInteger) cl_totalAttachmentSize;

- (void) cl_replaceAttachmentsWithURLs:(NSArray<NSDictionary*>*)attachmentFileStats;
- (void) cl_addLinksToMessageBodyforURLs:(NSArray<NSDictionary*>*)attachmentFileStats removeDeativatedAttachments:(BOOL)removeDeativated;

// processing steps
- (void) cl_checkForAttachmentUploadingWithCompletionBlock:(void (^ __nullable)(CLSendProcessAction returnCode))handler;
@end

@implementation DocumentEditor_CargoLifter
@dynamic cl_uploadController;

#pragma mark Swizzled Methods

- (IBAction)cargoLifter_send:(id)sender
{
    __weak typeof(self)weakSelf = self;
    
    // second step: check for large attachments to be uploaded to the cloud
    [weakSelf cl_checkForAttachmentUploadingWithCompletionBlock:^(CLSendProcessAction returnCode) {

        if( returnCode == CLProcessContinue )
        {
            [weakSelf cargoLifter_send:sender];
        }
    }];
}

- (void)cargoLifter_updateAttachmentStatus
{
    [self cargoLifter_updateAttachmentStatus];
    
    HeadersEditor_CargoLifter* headersEditor = (HeadersEditor_CargoLifter*)[(EditorClass*)self headersEditor];
    
    // check reachability
    Reachability* reachability = [Reachability reachabilityForInternetConnection];
    if(!([reachability isReachable] && ![reachability isInterventionRequired])) {
        [headersEditor setCl_uploadAttachments:@NO];
        return;
    }
    
    // if we don't have a service, we cannot upload
    NSArray* availableServices = [[CLServicesManager sharedManager] linkedServices];
    if(availableServices.count == 0) {
        [headersEditor setCl_uploadAttachments:@NO];
        return;
    }

    BOOL setBefore = [headersEditor cl_uploadAttachments] != nil;
    if([PLUGIN_DEFAULTS boolForKey:CLAutomaticallyUploadAttachments]) {
        CGFloat minFileSizeInMB = [PLUGIN_DEFAULTS floatForKey:CLMinAttachmentSize]*1024*1024;
        if(!setBefore && [self cl_totalAttachmentSize] >= minFileSizeInMB) {
            [headersEditor setCl_uploadAttachments:@YES];
        }
    }
}

+ (void) load
{
    NSError* swizzleError;
    
    // add our methods as category
    CLAddClassAsCategory([self class], @class(ComposeViewController));
    CLAddClassAsCategory([self class], @class(ComposeWindowController));

    // swizzling
    [@class(ComposeViewController) jr_swizzleMethod:@selector(send:) withMethod:@selector(cargoLifter_send:) error:&swizzleError];
    if(swizzleError) NSLog(@"💥 CARGOLIFTER: Swizzle Error: %@", swizzleError);
    [@class(ComposeViewController) jr_swizzleMethod:@selector(updateAttachmentStatus) withMethod:@selector(cargoLifter_updateAttachmentStatus) error:&swizzleError];
    if(swizzleError) NSLog(@"💥 CARGOLIFTER: Swizzle Error: %@", swizzleError);
    
    NSAssert(swizzleError==nil, @"Something went wrong during method swizzling: %@", swizzleError);
}

#pragma mark Helper Methods

- (NSWindow*) cl_composeWindow
{
    return (NSWindow*)[(EditorClass*)self window];
}

#pragma mark Processing Steps Methods

- (void) cl_checkForAttachmentUploadingWithCompletionBlock:(void (^)(CLSendProcessAction))handler
{
    HeadersEditor_CargoLifter* headersEditor = (HeadersEditor_CargoLifter*)[(EditorClass*)self headersEditor];
    BOOL uploadAttachments = [headersEditor.cl_uploadAttachments boolValue];
    
    // check for attachments to be uploaded to the cloud
    NSArray* attachments = [self cl_attachments];
    if( uploadAttachments && [attachments count] > 0 )
    {
        // attachments to be handled by uploader
        self.cl_uploadController = [[CLSendAttachmentsUploadController alloc] initWithDelegate:self forMailWindow:[self cl_composeWindow]];
        self.cl_uploadController.completionBlock = handler;
        [self.cl_uploadController uploadAttachments:attachments];
    }
    else
    {
        // no attachments or not to be uploaded --> continue as usual
        if(handler)
            handler(CLProcessContinue);
    }
}

#pragma mark Delegate Methods

- (void) cl_willStartUploadingAttachmentsWithIDs:(NSArray*)attachmentIDs
{
    //
}

- (void) cl_receivedPublicLinks:(NSArray<NSDictionary*>*)shareLinkArray
{
    NSLog(@"📯 CARGOLIFTER: Received share links for attachments: %@", shareLinkArray);

    CLAttachmentLinkStyleType linkType = [PLUGIN_DEFAULTS integerForKey:CLAttachmentLinkStyle];
    
    switch(linkType)
    {
        case CLAttachmentLinkStyleURLFiles:
        {
            // replace original attachments with corresponding URL files
            [self cl_replaceAttachmentsWithURLs:shareLinkArray];
            break;
        }
        case CLAttachmentLinkStyleLinkList:
            [self cl_addLinksToMessageBodyforURLs:shareLinkArray removeDeativatedAttachments:YES];
            
            break;
        case CLAttachmentLinkStyleBoth:
        {
            // replace original attachments with corresponding URL files
            [self cl_replaceAttachmentsWithURLs:shareLinkArray];
            
            // additionally, add link list to message body
            [self cl_addLinksToMessageBodyforURLs:shareLinkArray removeDeativatedAttachments:NO];
            
            break;
        }
    }
}

- (void) cl_canceledUploadingAttachmentsWithIDs:(NSArray*)attachmentIDs
{
    //
}

- (void) cl_failedUploadingAttachmentsWithError:(NSError*)error forAttachmentIDs:(NSArray*)attachmentIDs
{
    // show error message
    CLRunAlertPanel(NSLocalizedString(@"Attachment Upload Error", nil), @"%@", nil, [error localizedDescription]);
}

- (CLService*) cl_uploadService
{
    HeadersEditor_CargoLifter* headersEditor = (HeadersEditor_CargoLifter*)[(EditorClass*)self headersEditor];
    
    return [headersEditor cl_uploadService];
}

#pragma mark Private Methods

- (NSURL*) cl_imageURLForFileExtension:(NSString*)fileExtension {
    NSURL* testURL = [NSURL URLWithString:[NSString stringWithFormat:@"https://images.mailbutler.io/file_ext/%@.png", fileExtension.lowercaseString]];
    NSImage* testImage = [[NSImage alloc] initWithContentsOfURL:testURL];

    return testImage ? testURL : [NSURL URLWithString:@"https://images.mailbutler.io/file_ext/dat.png"];
}

- (void) cl_addLinksToMessageBodyforURLs:(NSArray<NSDictionary*>*)attachmentFileStats removeDeativatedAttachments:(BOOL)removeDeativated
{
    // get html document
    WebViewEditorClass* webviewEditor = [(EditorClass*)self webViewEditor];
    EditingMessageWebView* webview = [webviewEditor webView];
    DOMHTMLElement* bodyElement = [webview contentElement];
    DOMDocument* document = [[webview mainFrame] DOMDocument];
    
    // create string for our URL list
    NSMutableString* attachmentBoxString = [NSMutableString stringWithCapacity:500];
    NSMutableString* boxSeparatorString = [NSMutableString stringWithCapacity:100];
    
    // handle plain text differently
    BOOL allowRich = [webviewEditor allowsRichText];
    if (!allowRich) // plain text message
    {
        NSLog(@"📯 CARGOLIFTER: Message is unformatted text");
        
        [attachmentBoxString appendString:@"Links for attached files:<br>"];
        
        // add links to our list
        NSMutableString* linkList = [NSMutableString stringWithCapacity:500];
        for(NSDictionary* attachmentDict in attachmentFileStats)
        {
            NSString* urlString = [attachmentDict[CLAttachmentFileLinkURL] absoluteString];
            NSString* attachmentName    = [attachmentDict[CLAttachmentOrigFileName] lastPathComponent];
            
            // get file size
            NSInteger byteCount = [attachmentDict[CLAttachmentFileSize] integerValue];
            NSString* byteString = [NSByteCountFormatter stringFromByteCount:byteCount countStyle:NSByteCountFormatterCountStyleFile];
            
            [linkList appendFormat:@"&nbsp;&nbsp;- %@ (%@): %@<br>", attachmentName, byteString, urlString];
        }
        
        [attachmentBoxString appendString:linkList];
        
        // separator
        [boxSeparatorString setString:@"========================================================================================<br>"];
    }
    else// html text message
    {
        NSLog(@"📯 CARGOLIFTER: Message is formatted (HTML) text");

        // add links to our list
        NSMutableString* linkList = [NSMutableString stringWithCapacity:500];
        [linkList appendString:@"<ul style=\"padding-left:0px;\">"];
        for(NSDictionary* attachmentDict in attachmentFileStats)
        {
            NSString* urlString = [attachmentDict[CLAttachmentFileLinkURL] absoluteString];
            NSString* attachmentName    = [attachmentDict[CLAttachmentOrigFileName] lastPathComponent];
            
            // get file size
            NSInteger byteCount = [attachmentDict[CLAttachmentFileSize] integerValue];
            NSString* byteString = [NSByteCountFormatter stringFromByteCount:byteCount countStyle:NSByteCountFormatterCountStyleFile];
            
            // get icon URL
            NSString* iconURL = attachmentDict[CLAttachmentFileIconURL];
            
            if(iconURL == nil)
                iconURL = [[self cl_imageURLForFileExtension:[attachmentName pathExtension]] absoluteString];
            
            [linkList appendFormat:@"<li style=\"background:url('%@') no-repeat;background-size:32px 32px;padding:1px 36px 2px;min-height:36px;list-style-type:none;\"><a href=\"%@\" data-uploaded=\"true\">%@</a><br><small style=\"color:#777;\">(%@)</small></li>", iconURL, urlString, attachmentName, byteString];
        }
        [linkList appendString:@"</ul>"];
        
        [attachmentBoxString appendString:linkList];
        
        // separator
        [boxSeparatorString setString:@"<hr>"];
    }
    
    // Create new HTML elements for list and separator
    DOMHTMLElement *linkListElement = (DOMHTMLElement*)[document createElement:@"div"];
    [linkListElement setIdName:@"CargoLifterAttachmentLinkList"];
    
    CLAttachmentLinkListPositionType listPosition = [PLUGIN_DEFAULTS integerForKey:CLAttachmentLinkListPosition];
    
    switch(listPosition)
    {
        case CLAttachmentLinkListPositionAboveMessage:
        {
            // add separator after link list
            [attachmentBoxString appendString:boxSeparatorString];
            [attachmentBoxString appendString:@"<br>"];
            
            // set HTML string of link list element
            [linkListElement setInnerHTML:attachmentBoxString];
            
            // add the URL list as first element, if available
            DOMNode* firstChild = [bodyElement firstChild];
            if(firstChild)
                [linkListElement insertAsSiblingBeforeNode:firstChild];
            else
                [bodyElement appendChild:linkListElement];  // no first element found, just append to body
            
            break;
        }
        case CLAttachmentLinkListPositionBelowMessage:
        {
            // add separator before link list
            [attachmentBoxString insertString:boxSeparatorString atIndex:0];
            [attachmentBoxString insertString:@"<br>" atIndex:0];
            [attachmentBoxString appendString:@"<br>"];
            
            // set HTML string of link list element
            [linkListElement setInnerHTML:attachmentBoxString];
            
            // add the URL list after original content element, if available
            DOMHTMLElement* originalContentNode = [bodyElement descendantsWithClassName:@"AppleOriginalContents"][0];
            if( originalContentNode )
                [linkListElement insertAsSiblingBeforeNode:originalContentNode];
            else
                [bodyElement appendChild:linkListElement];  // no original content found, just append to body
            
            break;
        }
    }

    if(removeDeativated)
    {
        // find object element for each uploaded attachment - replace eventually
        for( NSDictionary* attachmentDict in attachmentFileStats )
        {
            NSString* attachmentID = attachmentDict[CLAttachmentContentID];
            
            // get all objects (attachments) in document
            DOMNodeList *objectElements = [bodyElement getElementsByTagName:@"object"];
            DOMHTMLElement* attachmentObject = nil;
            for(unsigned int i=0; i<objectElements.length; i++)
            {
                NSString* objectID = [(DOMElement*)[objectElements item:i] getAttribute:@"data"];
                NSString* objectType = [(DOMElement*)[objectElements item:i] getAttribute:@"type"];
                
                if( [objectType isEqualToString:@"application/x-apple-msg-attachment"] && [objectID hasPrefix:@"cid:"] && [objectID containsString:attachmentID] )
                {
                    attachmentObject = (DOMHTMLElement*)[objectElements item:i];
                    break;
                }
            }
            
            // remove attachment object now
            if( attachmentObject )
            {
                [attachmentObject.parentNode removeChild:attachmentObject];
            }
        }
    }
}

- (void) cl_replaceAttachmentsWithURLs:(NSArray<NSDictionary*>*)attachmentFileStats
{
    // get html document
    WebViewEditorClass* webviewEditor = [(EditorClass*)self webViewEditor];
    
    // write URL files first
    NSMutableArray* urlFileURLs = [NSMutableArray arrayWithCapacity:attachmentFileStats.count];
    for( NSDictionary* attachmentDict in attachmentFileStats )
    {
        NSString* urlFileString = [NSString stringWithFormat:@"[InternetShortcut]\nURL=%@", [attachmentDict[CLAttachmentFileLinkURL] absoluteString]];
        
        NSString* attachmentFileName    = [attachmentDict[CLAttachmentOrigFileName] stringByAppendingPathExtension:@"url"];
        NSString *attachmentPath        = [NSTemporaryDirectory() stringByAppendingPathComponent:attachmentFileName];
        
        NSError* error = nil;
        BOOL success = [urlFileString writeToFile:attachmentPath atomically:YES encoding:NSUTF8StringEncoding error:&error];
        
        if(!success) {
            NSLog(@"💥 CARGOLIFTER: Could not write attachment URL file to %@", attachmentPath);
            continue;
        }
        
        [urlFileURLs addObject:[NSURL fileURLWithPath:attachmentPath]];
    }
    
    // add url files as new attachments
    [webviewEditor addAttachmentsForFiles:urlFileURLs];
    
    // first get all url file attachments, backup their properties and remove them (properties will be used to replace original attachments later)
    NSArray* attachments = [self cl_attachments];
    
    EditingMessageWebView* webview = [webviewEditor webView];
    DOMHTMLElement* bodyElement = [webview contentElement];
    
    DOMNodeList *objectElements = [bodyElement getElementsByTagName:@"object"];
    
    NSMutableDictionary* urlAttachmentAttributesMap = [NSMutableDictionary dictionaryWithCapacity:attachmentFileStats.count];
    for(unsigned int i=0; i<objectElements.length; i++)
    {
        DOMHTMLElement* objectElement = (DOMHTMLElement*)[objectElements item:i];
        
        NSString* objectID = [[objectElement getAttribute:@"data"] trimmedContentID];
        
        // get MCAttachment object for this object
        MCAttachment* attachment = nil;
        for(MCAttachment* anAttachment in attachments)
        {
            if([anAttachment.contentID containsString:objectID])
            {
                attachment = anAttachment;
                break;
            }
        }
        
        if(!attachment)
            continue;
        
        NSString* attachmentFileName = attachment.filename;
        
        if([attachmentFileName.pathExtension isEqualToString:@"url"])
        {
            NSString* origFileName = [attachmentFileName stringByDeletingPathExtension];
            
            // find contentID of original file (before upload)
            NSString* originalContentID = nil;
            for( NSDictionary* attachmentDict in attachmentFileStats )
            {
                if([attachmentDict[CLAttachmentOrigFileName] containsString:origFileName])
                {
                    originalContentID = attachmentDict[CLAttachmentContentID];
                    break;
                }
            }
            
            if(!originalContentID)
                continue;
            
            // backup all attributes of this node
            NSMutableDictionary* objectAttributes = [NSMutableDictionary dictionaryWithCapacity:8];
            
            DOMNamedNodeMap* nodeMap = objectElement.attributes;
            for(unsigned int i=0; i<nodeMap.length; i++)
            {
                DOMNode* attrNode = [nodeMap item:i];
                NSString* attrKey = attrNode.nodeName;
                NSString* attrVal = attrNode.nodeValue;
                
                objectAttributes[attrKey] = attrVal;
            }
            
            // save for later
            urlAttachmentAttributesMap[originalContentID] = objectAttributes;
            
            // remove this node now, as we will use it to replace the original attachment in the next step
            if( objectElement )
            {
                [objectElement.parentNode removeChild:objectElement];
            }
        }
    }
    
    // find object attachment element for each uploaded attachment - replace eventually
    for( NSDictionary* attachmentDict in attachmentFileStats )
    {
        NSString* attachmentID = attachmentDict[CLAttachmentContentID];
        
        DOMHTMLElement* attachmentObject = nil;
        
        // get all objects (attachments) in document
        DOMNodeList *objectElements = [bodyElement getElementsByTagName:@"object"];
        for(unsigned int i=0; i<objectElements.length; i++)
        {
            NSString* objectData = [(DOMElement*)[objectElements item:i] getAttribute:@"data"];
            NSString* objectType = [(DOMElement*)[objectElements item:i] getAttribute:@"type"];
            
            if( [objectType isEqualToString:@"application/x-apple-msg-attachment"] && [objectData hasPrefix:@"cid:"] && [objectData containsString:attachmentID] )
            {
                attachmentObject = (DOMHTMLElement*)[objectElements item:i];
                break;
            }
        }
        
        // copy attributes of URL file attachment to original attachment element
        if( attachmentObject )
        {
            NSDictionary* urlObjectAttributes = urlAttachmentAttributesMap[attachmentID];
            
            for(NSString* attrKey in urlObjectAttributes.allKeys)
            {
                [attachmentObject setAttribute:attrKey value:urlObjectAttributes[attrKey]];
            }
        }
    }
}

- (NSArray*) cl_attachments
{
    // get html document of message
    WebViewEditorClass* webviewEditor = [(EditorClass*)self webViewEditor];
    EditingMessageWebView* webview = [webviewEditor webView];
    DOMHTMLElement* bodyElement = [webview contentElement];
    
    NSError* error = nil;
    NSXMLDocument* parseDoc = [[NSXMLDocument alloc] initWithXMLString:bodyElement.outerHTML options:NSXMLDocumentTidyHTML error:&error];
    
    // get all objects (attachments) in document - store their content-ID
    NSMutableArray* attachmentIDArray = [NSMutableArray arrayWithCapacity:5];
    for( NSXMLElement* anObjectElement in [parseDoc nodesForXPath:@"//object" error:nil] )
    {
        NSString* dataAttribute = [[anObjectElement attributeForName:@"data"] stringValue];
        
        if( [dataAttribute hasPrefix:@"cid:"] )
        {
            NSString* contentID = [dataAttribute trimmedContentID];
        
            // add attachment ID
            [attachmentIDArray addObject:contentID];
        }
    }
    
    // analyze signatures for file attachments
    NSArray* signatures = [(MailApp*)NSApp signatures];
    NSMutableArray* signatureContentIDs = [NSMutableArray arrayWithCapacity:[signatures count]];
    
    for(SignatureClassName* signature in signatures)
    {
        @try
        {
            WebArchive* webarchive = [signature webArchive];
            if(webarchive)
            {
                // check signature attachments (like images)
                for(WebResource* aSubResource in [webarchive subresources])
                {
                    if( [[aSubResource MIMEType] containsString:@"attachment"] )
                    {
                        NSString* objectID = [[[aSubResource URL] absoluteString] trimmedContentID];
                        [signatureContentIDs addObject:objectID];
                    }
                }
            }
        }
        @catch (NSException *exception)
        {
            NSLog(@"💥 CARGOLIFTER: An exception occured while accessing a signature's resources: %@", exception);
        }
        @finally
        {
            continue;
        }
    }
    
    // construct final list of attachments
    ComposeBackEnd* backEnd = [(EditorClass*)self backEnd];
    NSArray* attachments = [backEnd attachments];
    
    NSMutableArray* attachmentsArray = [NSMutableArray arrayWithCapacity:attachmentIDArray.count];
    
    for( AttachmentViewControllerClassName* attachmentViewController in attachments )
    {
        MCAttachment* attachment = [attachmentViewController attachment];
        NSString* attachmentID = [[attachment contentID] trimmedContentID];
        
        // check if attachment is part of message (contentID)
        if(![attachmentIDArray containsObject:attachmentID])
            continue;
        
        // don't include signature attachments
        if([signatureContentIDs containsObject:attachmentID])
            continue;
        
        // add to final array with attachments
        [attachmentsArray addObject:attachment];
    }
    
    return attachmentsArray;
}

- (NSUInteger) cl_totalAttachmentSize
{
    NSUInteger totalSize = 0;
    for( MCAttachment* attachment in [self cl_attachments] ) {
        totalSize += [attachment approximateSizeForAccessLevel:0];
    }
    return totalSize;
}

#pragma mark Associated Objects

- (void)setCl_uploadController:(CLSendAttachmentsUploadController *)uploadController
{
    objc_setAssociatedObject(self, @selector(cl_uploadController), uploadController, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (CLSendAttachmentsUploadController*)cl_uploadController
{
    return objc_getAssociatedObject(self, @selector(cl_uploadController));
}

@end
