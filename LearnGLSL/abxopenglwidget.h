#ifndef ABXOPENGLWIDGET_H
#define ABXOPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QTimer>
#include <QTime>

class ABXOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    enum Shape {None, Rect, Circle, Triangle};
    explicit ABXOpenGLWidget(QWidget *parent = nullptr);
    ~ABXOpenGLWidget();
    unsigned int VAO, VBO, EBO;
    QOpenGLShaderProgram shaderProgram;
    void drawShape(Shape shape);
    void wireDraw(bool wireshape);
public slots:
    void onTimeout();
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    Shape m_shape;
    QTimer timer;

signals:

};


#endif // ABXOPENGLWIDGET_H
