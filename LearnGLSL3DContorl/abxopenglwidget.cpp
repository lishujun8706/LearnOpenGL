#include "abxopenglwidget.h"
#include <QDebug>
#include <math.h>
#include <QTime>

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

QVector<QVector3D> cubePositions = {
        QVector3D( 0.0f,  0.0f,  0.0f),
        QVector3D( 2.0f,  5.0f, -15.0f),
        QVector3D(-1.5f, -2.2f, -2.5f),
        QVector3D(-3.8f, -2.0f, -12.3f),
        QVector3D( 2.4f, -0.4f, -3.5f),
        QVector3D(-1.7f,  3.0f, -7.5f),
        QVector3D( 1.3f, -2.0f, -2.5f),
        QVector3D( 1.5f,  2.0f, -2.5f),
        QVector3D( 1.5f,  0.2f, -1.5f),
        QVector3D(-1.3f,  1.0f, -1.5f)
    };

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

ABXOpenGLWidget::ABXOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    xpos = 0;
    ypos = 0;
    setFocusPolicy(Qt::StrongFocus);
    timer.start(100);
    m_time.start();
    connect(&timer, &QTimer::timeout, this, [=](){
        update();
    });
}

ABXOpenGLWidget::~ABXOpenGLWidget()
{
    makeCurrent();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    doneCurrent();
}

void ABXOpenGLWidget::drawShape(Shape shape)
{
    m_shape = shape;
    update();
}

void ABXOpenGLWidget::wireDraw(bool wireshape)
{
    makeCurrent();
    if(wireshape)
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

void ABXOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    bool success;
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shapes.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shapes.frag");
    success = shaderProgram.link();
    if(!success)
    {
        qDebug() << "ERROR:" << shaderProgram.log();
    }

    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    texture1 = new QOpenGLTexture(QImage(":/images/container.jpg").mirrored());
    texture2 = new QOpenGLTexture(QImage(":/images/awesomeface.png").mirrored());
    shaderProgram.bind();
    shaderProgram.setUniformValue("texture1", 0);
    shaderProgram.setUniformValue("texture2", 1);

    texture2->bind(1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    projection.perspective(45.0f, (float)width()/height(), 0.1f, 100.0f);
    shaderProgram.setUniformValue("projection", projection);

    glBindVertexArray(0);

    // she xiang ji
    cameraPos = QVector3D(0.0f, 0.0f, 3.0f);
    cameraTarget = QVector3D(0.0f, 0.0f, 0.0f);
    cameraDirection = QVector3D(cameraPos - cameraTarget);
    cameraDirection.normalize();

    up = QVector3D(0.0f, 1.0f, 0.0f);
    cameraRight = QVector3D::crossProduct(up, cameraDirection);
    cameraRight.normalize();
    cameraUp = QVector3D::crossProduct(cameraDirection, cameraRight);
}

void ABXOpenGLWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}

void ABXOpenGLWidget::paintGL()
{
    QMatrix4x4 view;
    QMatrix4x4 model;
    view.translate(0.0, 0.0, -3.0f);

    float radius;
    float camX;
    float camZ;

    radius = 10.0f;
    float time2 = m_time.elapsed()/1000.0;
    camX = sin(time2) * radius;
    camZ = cos(time2) * radius;
    view.lookAt(QVector3D(camX, 0.0, camZ), cameraTarget, up);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(VAO);
    switch (m_shape) {
    case Rect:
        shaderProgram.bind();
        glActiveTexture(GL_TEXTURE0);
        texture1->bind(0);
        glActiveTexture(GL_TEXTURE1);
        texture2->bind(1);
        shaderProgram.setUniformValue("view", view);

        foreach(auto item, cubePositions)
        {
            model.setToIdentity();
            model.translate(item);
            model.rotate(20.0f * cubePositions.indexOf(item), 1.0f, 0.3f, 0.5f);
            shaderProgram.setUniformValue("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        break;
    default:
        break;
    }
}
