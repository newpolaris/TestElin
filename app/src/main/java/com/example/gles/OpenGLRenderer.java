package com.example.gles;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class OpenGLRenderer implements GLSurfaceView.Renderer {

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        GLES20.glClearColor(1, 1, 0, 1);
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

    }

    @Override
    public void onDrawFrame(GL10 gl) {
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
    }
}
