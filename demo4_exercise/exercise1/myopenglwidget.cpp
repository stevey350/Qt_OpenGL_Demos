#include "myopenglwidget.h"
#include <QDebug>

float vertices[]={
    -0.5f,-0.5f,0.0f,
    0.5f,-0.5f,0.0f,
    0.0f,0.5f,0.0f
};

float firstTriangle[] = {
-0.9f,-0.5f,0.0f,   //1eft
-0.0f,-0.5f,0.0f,   //right
-0.45f,0.5f,0.0f,   //to9
};

float secondTriangle[] = {
0.0f,-0.5f,0.0f,    //left
0.9f,-0.5f,0.0f,    //right
0.45f,0.5f,0.0f     //top
};

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location=0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
                                 "}\0";

const char *fragmentshaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
                                   "}\n\0";

const char *fragment2shaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor = vec4(1.0f,1.0f,0.0f,1.0f);\n"
                                   "}\n\0";

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent): QOpenGLWidget(parent)
{

}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    //绑定VBO和VAO对象
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

    //为当前绑定到target的缓冲区对象创建一个新的数据存储。
    //如果data不是NULL,则使用来自此指针的数据初始化数据存储
    glBufferData(GL_ARRAY_BUFFER,sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    //告知显卡如何解析缓冲里的属性值
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void *)0);

    //开启VAOs[0]管理的第一个属性值
    glEnableVertexAttribArray(0);

    // 解绑VAO和VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //----------------------------------------------
    //绑定VBO和VAO对象
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);

    //为当前绑定到target的缓冲区对象创建一个新的数据存储。
    //如果data不是NULL,则使用来自此指针的数据初始化数据存储
    glBufferData(GL_ARRAY_BUFFER,sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    //告知显卡如何解析缓冲里的属性值
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void *)0);

    //开启VAOs[0]管理的第一个属性值
    glEnableVertexAttribArray(0);

    // 解绑VAO和VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // 顶点着色器
    unsigned int vertexShader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    GLint success; char infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        qDebug()<<"ERROR:SHADER:VERTEX:COMPILATION_FAILED\n"<<infoLog;
    }

    // 片断着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentshaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader,512,NULL, infoLog);
        qDebug()<<"ERROR:SHADER:FRAGMENT:COMPILATION_FAILED\n"<<infoLog;
    }
    // 片断着色器2
    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragment2shaderSource, NULL);
    glCompileShader(fragmentShader2);
    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader2,512,NULL, infoLog);
        qDebug()<<"ERROR:SHADER:FRAGMENT:COMPILATION_FAILED\n"<<infoLog;
    }

    // link
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader (shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        qDebug()<<"ERROR:SHADER:PROGRAM::LINKING_FAILED\n"<<infoLog;
    }
    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader (shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);
    glGetProgramiv(shaderProgram2,GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        qDebug()<<"ERROR:SHADER:PROGRAM::LINKING_FAILED\n"<<infoLog;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);
}

void MyOpenGLWidget::resizeGL(int w, int h)
{

}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES,0,3);

    glUseProgram(shaderProgram2);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES,0,3);
}
