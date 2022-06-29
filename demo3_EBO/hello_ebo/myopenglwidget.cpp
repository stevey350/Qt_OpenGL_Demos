#include "myopenglwidget.h"
#include <QDebug>

float vertices[]={
//        first triangle
    0.5f,0.5f,0.0f,     //top right
//        0.5f,-0.5f,0.0f,    //bottom right
//        -0.5f,0.5f,0.0f,    //top1eft

    //secondtriangle
    0.5f,-0.5f,0.0f,    //bottom right
    -0.5f,-0.5f,0.0f,   //bottomleft
    -0.5f,0.5f,0.0f     //top1eft
};

unsigned int indices[]={    //note that we start from 0!
    0,1,3,  //first triangle
    1,2,3   //second triangle
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


MyOpenGLWidget::MyOpenGLWidget(QWidget *parent): QOpenGLWidget(parent)
{

}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //绑定VBO和VAO对象
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //为当前绑定到target的缓冲区对象创建一个新的数据存储。/如果data不是NULL,则使用来自此指针的数据初始化数据存储
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);
    //告知显卡如何解析缓冲里的属性值
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void *)0);

    //开启VAO管理的第一个属性值
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);       // 解绑VBO （VAO不会存储VBO的解绑操作)
//    glBindVertexArray(0);                 // 解绑VAO

    // 顶点着色器
    unsigned int vertexShader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    GLint success; char infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS, &success);
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

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);   // VAO会存储EBO的解绑操作 (与VBO不同)
}

void MyOpenGLWidget::resizeGL(int w, int h)
{

}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);             // 指明显存中数据的属性
//    glDrawArrays(GL_TRIANGLES, 0, 6);   // 从EBO中取数据
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &indices);       // 如果EBO解绑了，第102行生效
}
