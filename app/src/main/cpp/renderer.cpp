//
// Created by peter.d.kim on 11/7/2019.
//

#include "renderer.h"
#include "logger.h"

constexpr char LOG_TAG[] = "EGL_SAMPLE";

Renderer::Renderer()
{
    pthread_mutex_init(&_mutex, 0);
}

Renderer::~Renderer() {
    pthread_mutex_destroy(&_mutex);
}

void Renderer::start() {
    LOG_INFO("Creating renderer thread");
    pthread_create(&_threadId, 0, threadStartCallback, this);
}

void Renderer::stop() {
    LOG_INFO("Stopping renderer thread");

    // send message to render thread to stop rendering
    pthread_mutex_lock(&_mutex);
    _msg = MSG_RENDER_LOOP_EXIT;
    pthread_mutex_unlock(&_mutex);

    pthread_join(_threadId, 0);
    LOG_INFO("Renderer thread stopped");
}

void Renderer::setWindow(ANativeWindow *window) {
    // notify render thread that window has changed
    pthread_mutex_lock(&_mutex);
    _msg = MSG_WINDOW_SET;
    _window = window;
    pthread_mutex_unlock(&_mutex);
}

bool Renderer::initialize() {

    EGLDisplay display = nullptr;
    if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
        return false;
    }

    if (!eglInitialize(display, 0, 0)) {
        LOG_ERROR("eglInitialize() returned error %d", eglGetError());
        return false;
    }

    // _display = display;
    // _surface = surface;

    return true;
}

void Renderer::drawFrame() {

}

void Renderer::destroy() {

}

void Renderer::renderLoop() {
    bool renderingEnabled = true;

    LOG_INFO("renderLoop()");

    while (renderingEnabled)
    {
        pthread_mutex_lock(&_mutex);

        // process incoming messages
        switch (_msg) {
            case MSG_WINDOW_SET:
                initialize();
                break;

            case MSG_RENDER_LOOP_EXIT:
                renderingEnabled = false;
                destroy();
                break;

            default:
                break;
        }
        _msg = MSG_NONE;

        if (_display) {
            drawFrame();
            if (!eglSwapBuffers(_display, _surface)) {
                LOG_ERROR("eglSwapBuffers() returned error %d", eglGetError());
            }
        }

        pthread_mutex_unlock(&_mutex);
    }

    LOG_INFO("Render loop exits");
}

void *Renderer::threadStartCallback(void *myself) {
    Renderer *renderer = (Renderer*)myself;
    if (renderer) {
        renderer->renderLoop();
    }
    pthread_exit(nullptr);

    return nullptr;
}
