//
// Created by peter.d.kim on 11/7/2019.
//

#ifndef ELIN_RENDERER_H
#define ELIN_RENDERER_H

#include <pthread.h>
#include <EGL/egl.h>
#include <GLES/gl.h>

class Renderer final {
public:
    Renderer();
    ~Renderer();

    void start();
    void stop();
    void setWindow(ANativeWindow* window);

private:

    enum RenderThreadMessage {
        MSG_NONE = 0,
        MSG_WINDOW_SET,
        MSG_RENDER_LOOP_EXIT
    };

    bool initialize();
    void destroy();

    void drawFrame();

    // RenderLoop is called in a rendering thread started in start() method
    // It creates rendering context and renders scene until stop() is called
    void renderLoop();

    static void* threadStartCallback(void *myself);

    pthread_t _threadId = 0;
    pthread_mutex_t _mutex = { 0, };

    // android window, supported by NDK r5 and newer
    ANativeWindow* _window;

    EGLDisplay  _display = 0;
    EGLSurface _surface = 0;
    EGLContext _contex = 0;
    GLfloat _angle = 0.f;

    RenderThreadMessage _msg = MSG_NONE;
};


#endif //ELIN_RENDERER_H
