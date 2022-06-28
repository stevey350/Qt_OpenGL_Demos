#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent): QOpenGLWidget(parent)
{

}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
}

void MyOpenGLWidget::resizeGL(int w, int h)
{

}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
