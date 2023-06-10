#include <jni.h>
#include "react-native-totp-utils.h"
#include "helpers.cpp"

extern "C"
JNIEXPORT void JNICALL
Java_com_totputils_TotpUtilsModule_nativeInstall(JNIEnv *env, jobject thiz, jlong jsi) {
    auto runtime = reinterpret_cast<Runtime *>(jsi);

    if (runtime) {
        totputils::install(*runtime);
    }
}
