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
#include "model.h"
#include <QPoint>

class ABXBox:public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
public:
    explicit ABXBox(QWidget* parent);
    Model* model;
    void repaintGL(bool ck);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    QOpenGLShaderProgram shaderProgram;

    int xpos;
    int ypos;

    QVector3D cameraPos;
    QVector3D cameraUp;
    QVector3D cameraFront;
    float fov;
    QPoint lastPoint;

    void keyPressEvent(QKeyEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
};

#endif // ABXBOX_H
