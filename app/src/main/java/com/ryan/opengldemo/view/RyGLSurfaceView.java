package com.ryan.opengldemo.view;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class RyGLSurfaceView extends GLSurfaceView implements GLSurfaceView.Renderer {
    static {
        System.loadLibrary("glesdemo");
    }

    private void initView() {
        setEGLContextClientVersion(2);
        setRenderer(this);
    }

    public RyGLSurfaceView(Context context) {
        super(context);
        initView();
    }

    public RyGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        nativeInit();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        nativeResize(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        nativeRender();
    }

    private native void nativeInit();

    private native void nativeResize(int width, int height);

    private native void nativeRender();
}
