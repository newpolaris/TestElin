//
// Created by peter.d.kim on 11/8/2019.
//

#ifndef ELIN_LOGGER_H
#define ELIN_LOGGER_H

#include <cstring>
#include <android/log.h>

#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif //ELIN_LOGGER_H
