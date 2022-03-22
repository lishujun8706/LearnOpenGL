#include "abxbox.h"
#include <math.h>
#include <QOpenGLTexture>
#include <QImage>
#include <math.h>

#define TIMEOUTMSEC 100
float PI = 3.1415926;

ABXBox::ABXBox(QWidget* parent): QOpenGLWidget(parent)
{
    xpos = 0;
    ypos = 0;
    fov = 45.0;
    setFocusPolicy(Qt::StrongFocus);
}

void ABXBox::repaintGL(bool ck)
{
    makeCurrent();
    if(ck)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    update();
    doneCurrent();
}

void ABXBox::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shader/shaders.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shader/shaders.frag");
    shaderProgram.link();

    model=Model::createModel("/home/shujun/Downloads/backpacksrc/backpack.obj", context(),&shaderProgram);
    model=Model::createModel("/home/shujun/Downloads/nanosuitsrc/nanosuit.obj", context(),&shaderProgram);

    glEnable(GL_DEPTH_TEST);

    // camera
    cameraPos   = QVector3D(0.0f, 0.0f,  3.0f);
    cameraFront = QVector3D(0.0f, 0.0f, -1.0f);
    cameraUp    = QVector3D(0.0f, 1.0f,  0.0f);
}

void ABXBox::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void ABXBox::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    QMatrix4x4 projection;

    QMatrix4x4 view;
    view.translate(0.0, 0.0, -3.0f);
    view.lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    projection.perspective(45.0f,width()/(float)height(),0.1f,500.0f);
    shaderProgram.setUniformValue("projection",projection);
    shaderProgram.setUniformValue("view", view);
    model->draw();
}

void ABXBox::mouseMoveEvent(QMouseEvent *e)
{
    static float yaw = -90.0f;
    static float pitch = 0.0f;

    qDebug() << "Move: " << "x=" << lastPoint.x() << "y=" << lastPoint.y();
    if(lastPoint.x() == 0 && lastPoint.y() == 0)
    {
        QPoint currentPos = e->pos();
        lastPoint = currentPos;
    }
    else
    {
        QPoint currentPos = e->pos();
        QPoint delPos = lastPoint - currentPos;
        lastPoint = currentPos;
        float sensitivity = 0.1f;
        delPos *= sensitivity;
        yaw -= delPos.x();
        pitch += delPos.y();

        if(pitch > 89.0f) pitch = 89.0f;
        if(pitch < -89.0f) pitch = -89.0f;

        cameraFront.setX(cos(yaw*PI/180) * cos(pitch*PI/180));
        cameraFront.setY(sin(pitch*PI/180));
        cameraFront.setZ(sin(yaw*PI/180) * cos(pitch*PI/180));
        cameraFront.normalize();
        update();
    }
}

void ABXBox::mouseReleaseEvent(QMouseEvent *e)
{
    lastPoint = QPoint(0, 0);
    qDebug() << "Release: " << "x=" << lastPoint.x() << "y=" << lastPoint.y();
}

void ABXBox::keyPressEvent(QKeyEvent *e)
{
    qDebug() << "KKKKKKKKKKKKKKKKKKKKKKKKKK";
    makeCurrent();
    float cameraSpeed = 0.025 * TIMEOUTMSEC;
    if(e->key() == Qt::Key_W)
    {
        qDebug() << "WWWWWWWW";
        cameraPos += cameraSpeed * cameraFront;
    }
    if(e->key() == Qt::Key_S)
    {
        qDebug() << "SSSSSSSS";
        cameraPos -= cameraSpeed * cameraFront;
    }
    if(e->key() == Qt::Key_A)
    {
        qDebug() << "AAAAAAAA";
        QVector3D temp = QVector3D::crossProduct(cameraFront, cameraUp);
        temp.normalize();
        cameraPos -= temp * cameraSpeed;
    }
    if(e->key() == Qt::Key_D)
    {
        qDebug() << "DDDDDD";
        QVector3D temp = QVector3D::crossProduct(cameraFront, cameraUp);
        temp.normalize();
        cameraPos += temp * cameraSpeed;
    }
    update();
    doneCurrent();
}
