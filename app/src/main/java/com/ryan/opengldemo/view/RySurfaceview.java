package com.ryan.opengldemo.view;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import androidx.annotation.NonNull;

public class RySurfaceview extends SurfaceView implements SurfaceHolder.Callback {
    static {
        System.loadLibrary("glesdemo");
    }

    private void initView(){
        this.getHolder().addCallback(this);
    }

    public RySurfaceview(Context context) {
        super(context);
        initView();
    }

    public RySurfaceview(Context context, AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    public RySurfaceview(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initView();
    }

    public RySurfaceview(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
        initView();
    }

    @Override
    public void surfaceCreated(@NonNull SurfaceHolder holder) {
    }

    @Override
    public void surfaceChanged(@NonNull SurfaceHolder holder, int format, int width, int height) {
    }

    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder holder) {

    }



    public native void openglDraw(Object surface);
}
