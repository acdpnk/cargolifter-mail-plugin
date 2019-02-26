#!/bin/bash

if [ $# -lt 1 ]; then
    echo "You need to specify the target directory for the class-dumps"
    exit 1
fi

MAC_OS_VERSION=$(sw_vers -productVersion)
BASE_DIR="$1"
TARGET_DIR="$BASE_DIR/$MAC_OS_VERSION"

if [ -e $TARGET_DIR ]; then
    echo "You already have headers for $MAC_OS_VERSION ... no need to re-run!"
else
	# start fresh
    rm -rf "$TARGET_DIR/*"
    
    ./class-dump -H -S -o "$TARGET_DIR/Mail" /Applications/Mail.app/Contents/MacOS/Mail
    ./class-dump -H -S -o "$TARGET_DIR/Mail-Framework" /System/Library/PrivateFrameworks/Mail.framework/Mail
    ./class-dump -H -S -o "$TARGET_DIR/MailCore-Framework" /System/Library/PrivateFrameworks/MailCore.framework/MailCore
    ./class-dump -H -S -o "$TARGET_DIR/MailService-Framework" /System/Library/PrivateFrameworks/MailService.framework/MailService
    ./class-dump -H -S -o "$TARGET_DIR/MailUI-Framework" /System/Library/PrivateFrameworks/MailUI.framework/MailUI
		./class-dump -H -S -o "$TARGET_DIR/EmailAddressing" /System/Library/PrivateFrameworks/EmailAddressing.framework/EmailAddressing
    
    if [ -e /System/Library/PrivateFrameworks/EmailCore.framework/EmailCore ]; then
        ./class-dump -H -S -o "$TARGET_DIR/EmailCore-Framework" /System/Library/PrivateFrameworks/EmailCore.framework/EmailCore
    fi
fi

# remove unnecessary includes and fix formats
export LC_CTYPE=C

find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' -e '5a\'$'\n''#pragma clang system_header' {} \;

find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' '/^#import "NS/d' {} \;

find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/unsigned long long/NSUInteger/g' {} \;

find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/<Mail\//</g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/<MailCore\//</g' {} \;

find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' '/cxx_destruct/d' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' '/CDStruct_/d' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' '/sqlite3/d' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/CDUnknownBlockType/id/g' {} \;

find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/Interface\.h/Interface-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/Delegate\.h/Delegate-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/Target\.h/Target-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/Agent\.h/Agent-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/Handler\.h/Handler-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/Listener\.h/Listener-Protocol.h/g' {} \;

find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/MCMailAccount\.h/MCMailAccount-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/MCRemoteStoreAccount\.h/MCRemoteStoreAccount-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/MCMailbox\.h/MCMailbox-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/MFUIMailbox\.h/MFUIMailbox-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/MCMessageDataSource\.h/MCMessageDataSource-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/MailboxSelectionOwner\.h/MailboxSelectionOwner-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/PopoutAnimationContentProvider\.h/PopoutAnimationContentProvider-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/MCAccount\.h/MCAccount-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/MCGmailLabel\.h/MCGmailLabel-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/IMAPAccount\.h/IMAPAccount-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/IMAPMessage\.h/IMAPMessage-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/IMAPMessageDataSource\.h/IMAPMessageDataSource-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/IMAPPersistedMessage\.h/IMAPPersistedMessage-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/MCChanging\.h/MCChanging-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/SelectionOwner\.h/SelectionOwner-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/MUIActionContactDataProvider\.h/MUIActionContactDataProvider-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/MUIAddressFieldContextProvider\.h/MUIAddressFieldContextProvider-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/MFScriptingMessage\.h/MFScriptingMessage-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/MailInspectorBarClient\.h/MailInspectorBarClient-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/MCCIDURLProtocolDataProvider\.h/MCCIDURLProtocolDataProvider-Protocol.h/g' {} \;
find "$TARGET_DIR" -name "*.h" -type f -exec sed -i '' 's/MCPersistentIDFetching\.h/MCPersistentIDFetching-Protocol.h/g' {} \;
