#ifndef BOMB_LOGGER_H
#define BOMB_LOGGER_H

#include "android/log.h"

#define TAG "Bomb"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

#endif //BOMB_LOGGER_H