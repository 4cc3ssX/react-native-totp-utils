#include <jni.h>
#include <string>

std::string JStringToString(JNIEnv *env, jstring jstr)
{
    const char *cstr = env->GetStringUTFChars(jstr, nullptr);
    std::string str(cstr);
    env->ReleaseStringUTFChars(jstr, cstr);
    return str;
}

int JDoubleToInt(jdouble jdbl)
{
    return static_cast<int>(jdbl);
}

jstring StringToJString(JNIEnv *env, const std::string &str)
{
    return env->NewStringUTF(str.c_str());
}

jobject BoolToJObject(JNIEnv *env, jclass clazz, jboolean value)
{
    // Get the Boolean class and the constructor method ID
    jclass booleanClass = env->FindClass("java/lang/Boolean");
    jmethodID constructor = env->GetMethodID(booleanClass, "<init>", "(Z)V");

    // Create a new Boolean object using the constructor
    jobject booleanObject = env->NewObject(booleanClass, constructor, value);

    return booleanObject;
}
