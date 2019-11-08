package com.example.elin;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.MotionEvent;

public class ElinSurfaceView extends GLSurfaceView {
    private ElinRenderer mRenderer;

    private final float touch_scale_factor = 180.f / 320;
    private float previousX;
    private float previousY;

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
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        // MotionEvent reports input details from the touch screen
        // and other input controls. In this case, you are only
        // interested in events where the touch position changed.

        float x = event.getX();
        float y = event.getY();

        switch (event.getAction()) {
            case MotionEvent.ACTION_MOVE:

                float dx = x - previousX;
                float dy = y - previousY;

                // reverse direction of rotation above the mid-line
                if (y > getHeight() / 2) {
                    dx = dx * -1 ;
                }

                // reverse direction of rotation to left of the mid-line
                if (x < getWidth() / 2) {
                    dy = dy * -1 ;
                }

                mRenderer.setAngle(
                        mRenderer.getAngle() +
                                ((dx + dy) * touch_scale_factor));
                requestRender();
        }

        previousX = x;
        previousY = y;
        return true;
    }
}
