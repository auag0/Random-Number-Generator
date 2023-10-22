package com.anago.randomnumber

object AppNative {
    init {
        System.loadLibrary("native-lib")
    }

    @JvmStatic
    external fun getRandomNumber(): Int
}