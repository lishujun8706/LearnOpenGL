#ifndef ABXOPENGLWIDGET_H
#define ABXOPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QTimer>
#include <QTime>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <QKeyEvent>
#include <QVector>
#include <QVector3D>
#include <QMouseEvent>

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
    QOpenGLTexture *texture1, *texture2;

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    Shape m_shape;
    QTimer timer;
    void keyPressEvent(QKeyEvent* event);
    int xpos;
    int ypos;
    QMatrix4x4 view;

signals:

};


#endif // ABXOPENGLWIDGET_H
