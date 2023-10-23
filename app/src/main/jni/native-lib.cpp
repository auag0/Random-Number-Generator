#include <jni.h>
#include <random>
#include "includes/Logger.h"

int generateRandomNumber() {
    std::random_device generator;
    int randomNumber = static_cast<int>(generator());
    return abs(randomNumber);
}

jint getRandomNumber(JNIEnv *env, jclass clazz) {
    return generateRandomNumber();
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGD("JNI_OnLoad");

    JNIEnv *env;
    int getEnvResult = vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6);
    if (getEnvResult != JNI_OK) {
        LOGD("Failed to get env");
        return getEnvResult;
    }

    const char *className = "com/anago/randomnumber/AppNative";
    jclass clazz = env->FindClass(className);
    if (clazz == nullptr) {
        LOGD("Failed to find class: %s", className);
        return JNI_ERR;
    }

    JNINativeMethod methods[] = {
            {"getRandomNumber", "()I", reinterpret_cast<void *>(getRandomNumber)}
    };
    int registerResult = env->RegisterNatives(clazz, methods,
                                              sizeof(methods) / sizeof(JNINativeMethod));
    if (registerResult != JNI_OK) {
        LOGD("Failed to register natives");
        return registerResult;
    }

    LOGD("JNI_OnLoaded %p", env);
    return JNI_VERSION_1_6;
}

__attribute__((constructor))
void constructor() {
    LOGD("constructor");
}