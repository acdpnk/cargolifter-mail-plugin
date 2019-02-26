//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class CNContact, CNContactPicker, CNContactProperty;

@protocol CNContactPickerDelegate <NSObject>

@optional
- (void)contactPicker:(CNContactPicker *)arg1 didSelectContact:(CNContact *)arg2;
- (void)contactPicker:(CNContactPicker *)arg1 didSelectContactProperty:(CNContactProperty *)arg2;
- (void)contactPickerDidClose:(CNContactPicker *)arg1;
- (void)contactPickerWillClose:(CNContactPicker *)arg1;
@end
