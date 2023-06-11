#import "TotpUtils.h"

#import <React/RCTBridge+Private.h>
#import <React/RCTUtils.h>
#import <jsi/jsi.h>

@implementation TotpUtils

@synthesize bridge = _bridge;
@synthesize methodQueue = _methodQueue;

RCT_EXPORT_MODULE()

+ (BOOL)requiresMainQueueSetup {

    return YES;
}

- (void)setBridge:(RCTBridge *)bridge {
    _bridge = bridge;
    _setBridgeOnMainQueue = RCTIsMainQueue();
}


RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(install)
{
    NSLog(@"Installing TotpUtils Bindings...");
    RCTCxxBridge* cxxBridge = (RCTCxxBridge*) self.bridge;
    if (cxxBridge == nil) {
        return @false;
    }
    
    // Totp JSI Binding
    totputils::install(*(facebook::jsi::Runtime *)cxxBridge.runtime);
    
    NSLog(@"Installed TotpUtils Bindings!");
    return @true;
}

@end
