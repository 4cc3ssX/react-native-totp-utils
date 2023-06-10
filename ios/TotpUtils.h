#ifdef __cplusplus
#import "react-native-totp-utils.h"
#endif

#import <React/RCTBridgeModule.h>

@interface TotpUtils : NSObject <RCTBridgeModule>

@property (nonatomic, assign) BOOL setBridgeOnMainQueue;

@end
