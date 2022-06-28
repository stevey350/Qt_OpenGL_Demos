#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

class MyOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
public:
    MyOpenGLWidget(QWidget *parent);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

private:
    unsigned int VBO, VAO;
    unsigned int shaderProgram;
};

#endif // MYOPENGLWIDGET_H
