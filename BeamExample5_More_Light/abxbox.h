#ifndef ABXBOX_H
#define ABXBOX_H

#include <QWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QVector3D>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QKeyEvent>

class ABXBox : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit ABXBox(QWidget *parent = nullptr);
    unsigned int VBO, VAO, VBO2, VAO2;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLShaderProgram shaderProgram2;
    QVector3D lightPos;
    void repaintGL(bool ck);
    QTimer timer;
    void changeColor();
    QTime time;

    QVector3D autodiffuseColor;
    QVector3D autoambientColor;

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    void keyPressEvent(QKeyEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
//    void wheelEvent(QWheelEvent* e);

    int xpos;
    int ypos;

    QVector3D cameraPos;
    QVector3D cameraUp;
    QVector3D cameraFront;
    float fov;
    QPoint lastPoint;

signals:

};

#endif // ABXBOX_H
