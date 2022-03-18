#include "abxbox.h"

float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

ABXBox::ABXBox(QWidget *parent) : QOpenGLWidget(parent)
{

}

void ABXBox::initializeGL()
{
    initializeOpenGLFunctions();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/shaders.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/shaders.frag");
    shaderProgram.link();

    shaderProgram2.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/light.vert");
    shaderProgram2.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/light.frag");
    shaderProgram2.link();
    int success;
    success = shaderProgram.link();
    if(!success)
    {
        qDebug() << "ERROR111:" << shaderProgram.log();
    }

    success = shaderProgram2.link();
    if(!success)
    {
        qDebug() << "ERROR:" << shaderProgram2.log();
    }

    lightPos = QVector3D(1.2f, 1.0f, 2.0f);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ABXBox::resizeGL(int w, int h)
{

}

void ABXBox::paintGL()
{
    glLineWidth(true);
    qDebug() << "paintGLLLLL";
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.bind();
    shaderProgram.setUniformValue("objectColor", 1.0f, 0.5f, 0.31f);
    shaderProgram.setUniformValue("lightColor",  1.0f, 1.0f, 1.0f);

    QMatrix4x4 view;
    QMatrix4x4 model;
    QMatrix4x4 perjection;
    view.translate(0.0f, 0.0f, -6.0f);
    model.setToIdentity();
    model.rotate(-10, -2.0f, 2.5f, 0.0f);
    perjection.perspective(45.0f, width()/height(), 0.1f, 100.0f);

    QVector3D Position(0.0f, 0.0f,  3.0f);
    QVector3D Front(0.0f, 0.0f, -1.0f);
    QVector3D Up(0.0f, 1.0f,  0.0f);
    view.lookAt(Position, Position + Front, Up);

    shaderProgram.setUniformValue("perject", perjection);
    shaderProgram.setUniformValue("view", view);
    shaderProgram.setUniformValue("model", model);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    shaderProgram2.bind();
    model.setToIdentity();
    model.translate(lightPos);
    model.scale(QVector3D(0.2f, 0.2f, 0.2f));
    shaderProgram2.setUniformValue("model", model);
    shaderProgram2.setUniformValue("view", view);
    shaderProgram2.setUniformValue("perject", perjection);
    glBindVertexArray(VAO2);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
