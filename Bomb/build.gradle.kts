plugins {
    id("com.android.library")
}

android {
    namespace = "com.anago.bomb"
    compileSdk = 34

    defaultConfig {
        minSdk = 23

        ndk {
            abiFilters.add("arm64-v8a")
            abiFilters.add("armeabi-v7a")
            abiFilters.add("x86")
            abiFilters.add("x86_64")
        }
    }

    externalNativeBuild {
        ndkBuild {
            path = file("src/main/jni/Android.mk")
        }
    }
}