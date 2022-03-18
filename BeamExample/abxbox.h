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

class ABXBox : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit ABXBox(QWidget *parent = nullptr);
    unsigned int VBO, VAO, VBO2, VAO2;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLShaderProgram shaderProgram2;
    QVector3D lightPos;

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

signals:

};

#endif // ABXBOX_H
