#ifdef __cplusplus
#import "react-native-totp-utils.h"
#endif

#ifdef RCT_NEW_ARCH_ENABLED
#import "RNTotpUtilsSpec.h"

@interface TotpUtils : NSObject <NativeTotpUtilsSpec>
#else
#import <React/RCTBridgeModule.h>

@interface TotpUtils : NSObject <RCTBridgeModule>
#endif

@end
