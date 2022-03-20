#include "abxbox.h"
#include <math.h>
#include <QOpenGLTexture>
#include <QImage>
#include <math.h>

float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

QVector3D cubePositions[] = {
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

QVector3D pointLightPositions[] = {
    QVector3D( 0.7f,  0.2f,  2.0f),
    QVector3D( 2.3f, -3.3f, -4.0f),
    QVector3D(-4.0f,  2.0f, -12.0f),
    QVector3D( 0.0f,  0.0f, -3.0f)
};

// FACTORY
QVector3D pointLightColors1[] = {
    QVector3D(0.2f, 0.2f, 0.6f),
    QVector3D(0.3f, 0.3f, 0.7f),
    QVector3D(0.0f, 0.0f, 0.3f),
    QVector3D(0.4f, 0.4f, 0.4f)
};

//  DESERT
QVector3D pointLightColors0[] = {
    QVector3D(1.0f, 0.6f, 0.0f),
    QVector3D(1.0f, 0.0f, 0.0f),
    QVector3D(1.0f, 1.0, 0.0),
    QVector3D(0.2f, 0.2f, 1.0f)
};

// HORROR
QVector3D pointLightColors2[] = {
    QVector3D(0.1f, 0.1f, 0.1f),
    QVector3D(0.1f, 0.1f, 0.1f),
    QVector3D(0.1f, 0.1f, 0.1f),
    QVector3D(0.3f, 0.1f, 0.1f)
};

// BIOCHEMICAL LAB
QVector3D pointLightColors[] = {
    QVector3D(0.4f, 0.7f, 0.1f),
    QVector3D(0.4f, 0.7f, 0.1f),
    QVector3D(0.4f, 0.7f, 0.1f),
    QVector3D(0.4f, 0.7f, 0.1f)
};

#define TIMEOUTMSEC 100
float PI = 3.1415926;

ABXBox::ABXBox(QWidget *parent) : QOpenGLWidget(parent)
{
    xpos = 0;
    ypos = 0;
    fov = 45.0;
    setFocusPolicy(Qt::StrongFocus);
//    timer.start(300);
//    connect(&timer, &QTimer::timeout, this, &ABXBox::changeColor);
}

void ABXBox::changeColor()
{
    makeCurrent();
    QVector3D lightColor;
    int sec = time.currentTime().msec();
    lightColor.setX(sin(sec * 2.0f));
    lightColor.setY(sin(sec * 0.7f));
    lightColor.setZ(sin(sec * 1.3f));

    autodiffuseColor = QVector3D::crossProduct(lightColor, QVector3D(0.5f, 0.5f, 0.5f));
    autoambientColor = QVector3D::crossProduct(autodiffuseColor, QVector3D(0.2f,0.2f,0.2f)); // 很低的影响
    update();
    doneCurrent();
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
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

//    lightPos = QVector3D(0.3f, 2.0f, 0.0f);
    lightPos = QVector3D(0.0f, 2.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // she xiang ji
    cameraPos   = QVector3D(0.0f, 0.0f,  3.0f);
    cameraFront = QVector3D(0.0f, 0.0f, -1.0f);
    cameraUp    = QVector3D(0.0f, 1.0f,  0.0f);
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

    QMatrix4x4 view;
    QMatrix4x4 model;
    QMatrix4x4 perjection;
    model.setToIdentity();

    model.rotate(20.0f, 2.3f, 0.3f, 0.0f);

    view.translate(0.0, 0.0, -3.0f);
    view.lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    shaderProgram.setUniformValue("viewPos", cameraPos);


    perjection.perspective(45.0f, width()/height(), 0.1f, 100.0f);

    shaderProgram.setUniformValue("perject", perjection);
    shaderProgram.setUniformValue("view", view);
    shaderProgram.setUniformValue("model", model);

//    shaderProgram.setUniformValue("light.ambient", autoambientColor);
//    shaderProgram.setUniformValue("light.diffuse", autodiffuseColor);

    shaderProgram.setUniformValue("light.ambient",  0.2f, 0.2f, 0.2f);
    shaderProgram.setUniformValue("light.diffuse",  0.5f, 0.5f, 0.5f); // 将光照调暗了一些以搭配场景
    shaderProgram.setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);

    shaderProgram.setUniformValue("material.ambient",  1.0f, 0.5f, 0.31f);
    // 没有使用 镜面光贴图
//    shaderProgram.setUniformValue("material.specular", 0.5f, 0.5f, 0.5f);
    shaderProgram.setUniformValue("material.shininess", 32.0f);

    shaderProgram.setUniformValue("material.diffuse", 0);
    QOpenGLTexture diffuseMap(QImage(":/images/container2.png").mirrored());
    glActiveTexture(GL_TEXTURE0);
    diffuseMap.bind(0);

    // 使用 镜面光贴图
    shaderProgram.setUniformValue("material.specular", 1);
    QOpenGLTexture specularMap(QImage(":/images/container2_specular.png").mirrored());
    glActiveTexture(GL_TEXTURE1);
    specularMap.bind(1);

    glBindVertexArray(VAO);

//    shaderProgram.setUniformValue("light.direction", QVector3D(-0.2f, -1.0f, -0.3f));

    shaderProgram.setUniformValue("light.constant",  1.0f);
    shaderProgram.setUniformValue("light.linear",    0.09f);
    shaderProgram.setUniformValue("light.quadratic", 0.032f);

    shaderProgram.setUniformValue("light.position",  cameraPos);
    shaderProgram.setUniformValue("light.direction", cameraFront);
//    lightingShader.setFloat("light.cutOff",   glm::cos(glm::radians(12.5f)));
    shaderProgram.setUniformValue("light.cutOff", cos(12.5f*PI/180));
//    lightingShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
    shaderProgram.setUniformValue("light.outerCutOff", cos(17.5f*PI/180));

    // directional light
    shaderProgram.setUniformValue("dirLight.direction", -0.2f, -1.0f, -0.3f);
    shaderProgram.setUniformValue("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    shaderProgram.setUniformValue("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    shaderProgram.setUniformValue("dirLight.specular", 0.5f, 0.5f, 0.5f);

    // point light 1
    shaderProgram.setUniformValue("pointLights[0].position", pointLightPositions[0]);
    shaderProgram.setUniformValue("pointLights[0].ambient", QVector3D::crossProduct(pointLightColors[0], QVector3D(0.1, 0.1, 0.1)));
    shaderProgram.setUniformValue("pointLights[0].diffuse", pointLightColors[0]);
    shaderProgram.setUniformValue("pointLights[0].specular", pointLightColors[0]);
    shaderProgram.setUniformValue("pointLights[0].constant", 1.0f);
    shaderProgram.setUniformValue("pointLights[0].linear", 0.09f);
    shaderProgram.setUniformValue("pointLights[0].quadratic", 0.032f);
    // point light 2
    shaderProgram.setUniformValue("pointLights[1].position", pointLightPositions[1]);
    shaderProgram.setUniformValue("pointLights[1].ambient", QVector3D::crossProduct(pointLightColors[1], QVector3D(0.1, 0.1, 0.1)));
    shaderProgram.setUniformValue("pointLights[1].diffuse", pointLightColors[1]);
    shaderProgram.setUniformValue("pointLights[1].specular", pointLightColors[1]);
    shaderProgram.setUniformValue("pointLights[1].constant", 1.0f);
    shaderProgram.setUniformValue("pointLights[1].linear", 0.09f);
    shaderProgram.setUniformValue("pointLights[1].quadratic", 0.032f);
    // point light 3
    shaderProgram.setUniformValue("pointLights[2].position", pointLightPositions[2]);
    shaderProgram.setUniformValue("pointLights[2].ambient", QVector3D::crossProduct(pointLightColors[2], QVector3D(0.1, 0.1, 0.1)));
    shaderProgram.setUniformValue("pointLights[2].diffuse", pointLightColors[2]);
    shaderProgram.setUniformValue("pointLights[2].specular", pointLightColors[2]);
    shaderProgram.setUniformValue("pointLights[2].constant", 1.0f);
    shaderProgram.setUniformValue("pointLights[2].linear", 0.09f);
    shaderProgram.setUniformValue("pointLights[2].quadratic", 0.032f);
    // point light 4
    shaderProgram.setUniformValue("pointLights[3].position", pointLightPositions[3]);
    shaderProgram.setUniformValue("pointLights[3].ambient", QVector3D::crossProduct(pointLightColors[3], QVector3D(0.1, 0.1, 0.1)));
    shaderProgram.setUniformValue("pointLights[3].diffuse", pointLightColors[3]);
    shaderProgram.setUniformValue("pointLights[3].specular", pointLightColors[3]);
    shaderProgram.setUniformValue("pointLights[3].constant", 1.0f);
    shaderProgram.setUniformValue("pointLights[3].linear", 0.09f);
    shaderProgram.setUniformValue("pointLights[3].quadratic", 0.032f);

    // spotLight
    shaderProgram.setUniformValue("spotLight.position", cameraPos);
    shaderProgram.setUniformValue("spotLight.direction", cameraFront);
    shaderProgram.setUniformValue("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    shaderProgram.setUniformValue("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    shaderProgram.setUniformValue("spotLight.specular", 1.0f, 1.0f, 1.0f);
    shaderProgram.setUniformValue("spotLight.constant", 1.0f);
    shaderProgram.setUniformValue("spotLight.linear", 0.09f);
    shaderProgram.setUniformValue("spotLight.quadratic", 0.032f);
    shaderProgram.setUniformValue("spotLight.cutOff", cos(12.5f*PI/180));
    shaderProgram.setUniformValue("spotLight.outerCutOff", cos(15.0f*PI/180));

    for(unsigned int i = 0; i < 10; i++)
    {
      QMatrix4x4 model;
      model.translate(cubePositions[i]);
      float angle = 20.0f * i;
      model.rotate(angle, 1.0f, 0.3f, 0.5f);
      shaderProgram.setUniformValue("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // 下面的是灯
    shaderProgram2.bind();
    shaderProgram2.setUniformValue("view", view);
    shaderProgram2.setUniformValue("perject", perjection);
    glBindVertexArray(VAO2);

    for(unsigned int i = 0; i < 4; i++)
    {
        QMatrix4x4 model;
        model.setToIdentity();
        model.translate(pointLightPositions[i]);
        model.rotate(20.0f, 1.0f, 0.3f, 0.5f);
        model.scale(QVector3D(0.2f, 0.2f, 0.2f));
        shaderProgram2.setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
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
