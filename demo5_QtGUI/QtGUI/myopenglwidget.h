#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

class MyOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
public:
    enum Shape{None, Rect, Circle, Triangle};
    MyOpenGLWidget(QWidget *parent);
    ~MyOpenGLWidget();

    void draw_shape(Shape shape);
    void set_wire_frame(bool is_wire_frame);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

private:
    unsigned int VBO, VAO, EBO;
    unsigned int shaderProgram;

    Shape m_shape;
};

#endif // MYOPENGLWIDGET_H
