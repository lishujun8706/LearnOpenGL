#include "abxbox.h"

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

ABXBox::ABXBox(QWidget *parent) : QOpenGLWidget(parent)
{

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
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
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

    lightPos = QVector3D(0.3f, 2.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
    shaderProgram.setUniformValue("lightPos", lightPos);

    QMatrix4x4 view;
    QMatrix4x4 model;
    QMatrix4x4 perjection;
    model.setToIdentity();

//  ??????view lookat?????????, ????????????????????????????????????(0, 0, 2)??????????????????????????????
//  ???????????????(0, 0.5, 2)

//  ????????? 1 ?????????:
    model.rotate(20.0f, 2.3f, 0.3f, 0.0f);
    view.translate(0.0f, 0.0f, -3.0f);
    QVector3D Position(1.0f, 2.0f,  3.0f);
    QVector3D Front(0.0f, 0.0f, -1.0f);
    QVector3D Up(0.0f, 1.0f,  0.0f);
    view.lookAt(Position, Position + Front, Up);
    shaderProgram.setUniformValue("viewPos", Position);

//    ????????? 2 ?????????:
//    view.translate(0.0f, 0.0f, -3.0f); // option, lookat can support that
//    QVector3D Position(0.0f, 0.0f,  3.0f);
//    QVector3D Up(0.0f, 1.0f,  0.0f);
//    view.lookAt(Position, QVector3D(0.0f, 0.0f, 0.0f), Up);

//    ????????? 3 ?????????:
//    model.setToIdentity();
//    view.translate(0.0f, 0.0f, -3.0f);
//    QVector3D Position(0.0f, 1.0f,  3.0f);
//    QVector3D Up(0.0f, 1.0f,  0.0f);
//    view.lookAt(Position, QVector3D(0.0f, 0.0f, 0.0f), Up);

//    ????????? 4 ?????????:
//    model.setToIdentity();
//    QVector3D Position(0.0f, 1.0f,  6.0f);
//    QVector3D Up(0.0f, 1.0f,  0.0f);
//    view.lookAt(Position, QVector3D(0.0f, 0.0f, 0.0f), Up);

    perjection.perspective(45.0f, width()/height(), 0.1f, 100.0f);

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
