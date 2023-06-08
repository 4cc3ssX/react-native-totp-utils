#include <jni.h>
#include "react-native-totp-utils.h"

extern "C"
JNIEXPORT jint JNICALL
Java_com_totputils_TotpUtilsModule_nativeMultiply(JNIEnv *env, jclass type, jdouble a, jdouble b) {
    return totputils::multiply(a, b);
}
