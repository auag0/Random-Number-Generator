#include <jni.h>
#include <dlfcn.h>
#include <unistd.h>
#include "includes/Logger.h"
#include "dobby/dobby.h"

const char *LIB_NAME = "libnative-lib.so";
const char *SYMBOL_NAME = "_Z15getRandomNumberP7_JNIEnvP7_jclass";

jint (*orig_getRandomNumber)(_JNIEnv *, _jclass *);

jint fake_getRandomNumber(_JNIEnv *env, _jclass *clazz) {
    int result = orig_getRandomNumber(env, clazz);
    LOGD("called getRandomNumber() = %d", result);
    return 99999;
}

__attribute__((constructor))
void constructor() {
    LOGD("constructor");
    LOGD("PID: %d", getpid());
    LOGD("Hook setup");
    void *handle = dlopen(LIB_NAME, RTLD_LAZY);
    if (handle == nullptr) {
        LOGE("Failed to load library: %s", dlerror());
        return;
    }

    void *targetAddress = dlsym(handle, SYMBOL_NAME);
    if (targetAddress == nullptr) {
        LOGE("Failed to resolve symbol: %s in %s", SYMBOL_NAME, LIB_NAME);
        return;
    }

    if (DobbyHook(targetAddress, (dobby_dummy_func_t) fake_getRandomNumber,
                  (dobby_dummy_func_t *) &orig_getRandomNumber) != 0) {
        LOGE("Hooking failed");
        return;
    }

    LOGD("Hooked %s in %s", SYMBOL_NAME, LIB_NAME);
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGD("JNI_OnLoad");

    JNIEnv *env;
    int getEnvResult = vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6);
    if (getEnvResult != JNI_OK) {
        LOGD("Failed to get env");
        return getEnvResult;
    }

    LOGD("JNI_OnLoaded %p", env);
    return JNI_VERSION_1_6;
}