package com.example.elin;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

public class ElinSurfaceView extends GLSurfaceView {
    private ElinRenderer mRenderer;

    public ElinSurfaceView(Context context) {
        super(context);
        init();
    }

    public ElinSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    private void init() {
        setEGLContextClientVersion(2);
        setPreserveEGLContextOnPause(true);
        mRenderer = new ElinRenderer();
        setRenderer(mRenderer);
        // setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }
}
