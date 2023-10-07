#include <jni.h>
#include <GLES3/gl3.h>

#include <android/log.h>
#include <stdbool.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "CommonUtil.h"

static GLuint program;
static GLuint positionHandle;
static GLuint colorHandle;
static GLuint texCoordHandle;
static GLuint textureId;
static int width, height, channels;
static unsigned char *imageData;

//
// Created by ryan on 2023/8/23.
//


void rect_nativeInit() {
    const char *vertexShaderCode =
            "#version 300 es\n"
            "layout(location = 0) in vec4 a_Position;\n"
            "layout(location = 1) in vec4 a_Color;\n"
            "layout (location = 2) in vec2 a_TexCoord;\n"
            "out vec4 v_Color;\n"
            "out vec2 v_TexCoord;\n"
            "uniform mat4 model;\n"
            "uniform mat4 view;\n"
            "uniform mat4 projection;\n"
            "void main() {\n"
            "  v_Color = a_Color;\n"
            "  gl_Position = projection * view * model * a_Position;\n"
            //            "  v_TexCoord = vec2(a_TexCoord.x, 1.0 - a_TexCoord.y);\n"
            "  v_TexCoord = a_TexCoord;\n"
            "}\n";

    const char *fragmentShaderCode =
            "#version 300 es\n"
            "precision mediump float;\n"
            "in vec4 v_Color;\n"
            "in vec2 v_TexCoord;\n"
            "out vec4 o_Color;\n"
            "uniform sampler2D ourTexture;\n"
            "void main() {\n"
            "  o_Color = texture(ourTexture, v_TexCoord);\n"
            "}\n";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    positionHandle = glGetAttribLocation(program, "a_Position");
    colorHandle = glGetAttribLocation(program, "a_Color");
    texCoordHandle = glGetAttribLocation(program, "a_TexCoord");
    stbi_set_flip_vertically_on_load(true);
    imageData = stbi_load("/sdcard/Pictures/monkey.png", &width, &height, &channels,
                          STBI_rgb_alpha);

// 创建纹理对象，并设置纹理参数
    glGenTextures(1, &textureId); // 生成一个纹理单元
    glBindTexture(GL_TEXTURE_2D, textureId); // 绑定纹理
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

// 将图片数据上传到纹理对象中
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 imageData); // 利用imageData生成纹理对象
// 以上为生成纹理的代码
}

void rect_nativeRender() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat vertices[] = {
            -0.5f, 0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f
    };

    GLfloat colors[] = {
            1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f
    };

    GLfloat texCoords[] = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
    };

    glUseProgram(program);

    glVertexAttribPointer(positionHandle, 4, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionHandle);

    glVertexAttribPointer(colorHandle, 4, GL_FLOAT, GL_FALSE, 0, colors);
    glEnableVertexAttribArray(colorHandle);

    glVertexAttribPointer(texCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, texCoords);
    glEnableVertexAttribArray(texCoordHandle);

//    glm::mat4 trans =  glm::mat4(1.0f);
//    trans = glm::rotate(trans, glm::radians(-55.0f), glm::vec3(1.0, 0.0, 0.0));
//    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
//    LOGW("imageData， %d, %d, transformLoc: %d", width, height, transformLoc);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 view = glm::mat4(1.0f);
// 注意，我们将矩阵向我们要进行移动场景的反方向移动。
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

    glGetError();
    GLint modelLoc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    GLint viewLoc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    GLint projectionLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    LOGW("glGetError, %d", glGetError());
    glDrawArrays(GL_TRIANGLE_STRIP, 0 , 4);
    LOGW("glGetError end, %d", glGetError());
}