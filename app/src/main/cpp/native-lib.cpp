/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <cstring>
#include <jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <assert.h>

#include "logger.h"
#include "renderer.h"

constexpr char LOG_TAG[] = "EGL_SAMPLE";

static ANativeWindow *window = nullptr;
static Renderer *renderer = nullptr;

extern "C"
JNIEXPORT void JNICALL
Java_com_example_elin_MainActivity_nativeOnStart(JNIEnv *env, jobject thiz) {
    LOG_INFO("nativeOnStart");
    renderer = new Renderer();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_elin_MainActivity_nativeOnResume(JNIEnv *env, jobject thiz) {
    assert(renderer != nullptr);
    renderer->start();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_elin_MainActivity_nativeOnPause(JNIEnv *env, jobject thiz) {
    assert(renderer != nullptr);
    renderer->stop();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_elin_MainActivity_nativeOnStop(JNIEnv *env, jobject thiz) {
    delete renderer;
    renderer = nullptr;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_elin_MainActivity_nativeSetSurface(JNIEnv *env, jobject thiz, jobject surface) {
    if (surface != 0) {
        window = ANativeWindow_fromSurface(env, surface);
        LOG_INFO("Got window %p", window);
        renderer->setWindow(window);

    } else {
        LOG_INFO("Releasing window");
        ANativeWindow_release(window);
    }
}
