#include <jni.h>
#include "react-native-totp-utils.h"
#include "helpers.cpp"

extern "C" JNIEXPORT jstring JNICALL
Java_com_totputils_TotpUtilsModule_nativeGenerateSecretKey(JNIEnv *env, jclass type, jdouble length)
{

    std::string otp = totputils::generateSecretKey(JDoubleToInt(length));
    return StringToJString(env, otp);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_totputils_TotpUtilsModule_nativeGenerateOTP(JNIEnv *env, jclass type, jstring secret, jdouble digits,
                                           jdouble timeStep)
{

    std::string otp = totputils::generateOTP(JStringToString(env, secret), JDoubleToInt(digits), JDoubleToInt(timeStep));
    return StringToJString(env, otp);
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_totputils_TotpUtilsModule_nativeValidateOTP(JNIEnv *env, jclass type, jstring secret, jstring otp, jdouble digits,
                                           jdouble timeStep, jdouble window)
{

    bool isValid = totputils::validateOTP(JStringToString(env, secret), JStringToString(env, otp), JDoubleToInt(digits), JDoubleToInt(timeStep),
                                     JDoubleToInt(window));
    return BoolToJObject(env, type, isValid);
}
