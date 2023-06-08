#import "TotpUtils.h"

@implementation TotpUtils
RCT_EXPORT_MODULE()

// See // https://reactnative.dev/docs/native-modules-ios
RCT_REMAP_METHOD(generateSecretKey,
                 generateSecretKeyWithLength:(int)length
                 withResolver:(RCTPromiseResolveBlock)resolve
                 withRejecter:(RCTPromiseRejectBlock)reject)
{
    NSString *result = @(totputils::generateSecretKey(length).c_str());

    resolve(result);
}

RCT_REMAP_METHOD(generateOTP,
                 generateOTPWithSecret:(NSString*)secret
                 generateOTPWithDigits:(int)digits
                 generateOTPWithtimeStep:(int)timeStep
                 withResolver:(RCTPromiseResolveBlock)resolve
                 withRejecter:(RCTPromiseRejectBlock)reject)
{
    NSString *result = @(totputils::generateOTP(std::string([secret UTF8String]), digits, timeStep).c_str());

    resolve(result);
}

RCT_REMAP_METHOD(validateOTP,
                 generateOTPWithSecret:(NSString*)secret
                 generateOTPWithOTP:(NSString*)otp
                 generateOTPWithDigits:(int)digits
                 generateOTPWithTimeStep:(int)timeStep
                 generateOTPWithWindow:(int)window
                 withResolver:(RCTPromiseResolveBlock)resolve
                 withRejecter:(RCTPromiseRejectBlock)reject)
{
    NSNumber *result = @(totputils::validateOTP(std::string([secret UTF8String]), std::string([otp UTF8String]), digits, timeStep, window));

    resolve(result);
}


// Don't compile this code when we build for the old architecture.
#ifdef RCT_NEW_ARCH_ENABLED
- (std::shared_ptr<facebook::react::TurboModule>)getTurboModule:
    (const facebook::react::ObjCTurboModule::InitParams &)params
{
    return std::make_shared<facebook::react::NativeTotpUtilsSpecJSI>(params);
}
#endif

- (void)generateOTP:(NSString *)secret digits:(double)digits timeStep:(double)timeStep resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject {
    NSString *result = @(totputils::generateOTP(std::string([secret UTF8String]), digits, timeStep).c_str());

    resolve(result);
}

- (void)generateSecretKey:(double)length resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject {
    NSString *result = @(totputils::generateSecretKey(length).c_str());

    resolve(result);
}

- (void)validateOTP:(NSString *)secret otp:(NSString *)otp digits:(double)digits timeStep:(double)timeStep window:(double)window resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject {
    NSNumber *result = @(totputils::validateOTP(std::string([secret UTF8String]), std::string([otp UTF8String]), digits, timeStep, window));

    resolve(result);
}

@end
