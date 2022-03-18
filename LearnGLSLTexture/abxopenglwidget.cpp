#include "abxopenglwidget.h"
#include <QDebug>
#include <math.h>
#include <QImage>

float vertices[]={
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

ABXOpenGLWidget::ABXOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    //timer.start(200);
    //connect(&timer, &QTimer::timeout, this, &ABXOpenGLWidget::onTimeout);
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

void ABXOpenGLWidget::onTimeout()
{
    qDebug() << "TTTTTTTTTTTTTTT";
    makeCurrent();
    int timeValue = QTime::currentTime().second();
    float greenValue = (sin(timeValue)/2.0f)+0.5f;
    shaderProgram.setUniformValue("ourColor", 0.0f, greenValue, 0.0f,1.0f);
    update();
    doneCurrent();
}

void ABXOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof (float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof (float)));
    glEnableVertexAttribArray(2);

    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shapes.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shapes.frag");
    int success;
    success = shaderProgram.link();
    if(!success)
    {
        qDebug() << "ERROR:" << shaderProgram.log();
    }
    textureBox = new QOpenGLTexture(QImage(":/images/container.jpg").mirrored());
    textureSmile = new QOpenGLTexture(QImage(":/images/awesomeface.png").mirrored());
    shaderProgram.bind();
    shaderProgram.setUniformValue("texture1", 0);
    shaderProgram.setUniformValue("texture2", 1);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ABXOpenGLWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}

void ABXOpenGLWidget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    switch (m_shape) {
    case Rect:
        shaderProgram.bind();
//        glActiveTexture(GL_TEXTURE0);
        textureBox->bind(0);
        textureSmile->bind(1);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        break;
    default:
        break;
    }
}
