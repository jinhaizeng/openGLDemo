//
// Created by Ryan on 2023/10/7.
//

#include <jni.h>
#include <GLES3/gl3.h>
#include "drawDemo/rectangleDemo.h"

#include <android/native_window.h>
#include <android/native_window_jni.h>

#include <EGL/egl.h>

#define STB_IMAGE_IMPLEMENTATION
#include <string>
#include "CommonUtil.h"


extern "C"
JNIEXPORT void JNICALL
Java_com_ryan_opengldemo_view_RySurfaceview_openglDraw(JNIEnv *env, jobject thiz, jobject surface) {
    ANativeWindow *window = ANativeWindow_fromSurface(env, surface);


}
extern "C"
JNIEXPORT void JNICALL
Java_com_ryan_opengldemo_view_RyGLSurfaceView_nativeInit(JNIEnv *env, jobject thiz) {
    rect_nativeInit();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ryan_opengldemo_view_RyGLSurfaceView_nativeResize(JNIEnv *env, jobject thiz, jint width,
                                                           jint height) {
    glViewport(0, 0, width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ryan_opengldemo_view_RyGLSurfaceView_nativeRender(JNIEnv *env, jobject thiz) {
    rect_nativeRender();
}