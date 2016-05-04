#include "myglwidget.h"
#include <GL/glu.h>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QKeyEvent>
#include <QWheelEvent>

GLfloat lightAmbient[4]={0.5,0.5,0.5,1.0};
GLfloat lightDiffuse[4]={1.0,1.0,1.0,1.0};
GLfloat lightPosition[4]={0.0,1.0,2.0,1.0};

MyGLWidget::MyGLWidget(QWidget *parent,QString fn) :
    QGLWidget(parent)
{
    n_node=0;
    filename=fn;
    xRot=yRot=zRot=0;
    lightFlag=false;
    translate=-3.0;
    fillArray();
}

void MyGLWidget::fillArray()
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_4_0);
    stream.setByteOrder(QDataStream::LittleEndian);
    char *str1;
    char *str2;
    char *str;
    str1=new char[1];
    str2=new char[122];
    str=new char[7];
    stream.readRawData(str2,51);
    stream.readRawData(str1,1);
    for(int i=0;str1[0]!='\n';i++){
        str[i]=str1[0];
        stream.readRawData(str1,1);
    }
    QString temp(str);
    n_node=temp.toInt();
    vertext=new ver[n_node];
    col=new color[n_node];
    stream.readRawData(str2,122);
    for (int i = 0; i < n_node; i++)
    {
        stream>>vertext[i].x;
        stream>>vertext[i].y;
        stream>>vertext[i].z;
        stream>>col[i].a;
        stream>>col[i].b;
        stream>>col[i].c;
    }
    file.close();
}

void MyGLWidget::initializeGL()
{
    glClearColor(1.0f,1.0f,1.0f,0.0f);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glLightfv(GL_LIGHT1,GL_AMBIENT,lightAmbient);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,lightDiffuse);
    glLightfv(GL_LIGHT1,GL_POSITION,lightPosition);

    glEnable(GL_LIGHT1);
}

void MyGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,(GLint)w,(GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,(GLfloat)w/(GLfloat)h,0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //paint the quads
    glTranslatef(0.0,0.0,translate);
    glRotatef(xRot,1.0,0.0,0.0);
    glRotatef(yRot,0.0,1.0,0.0);
    glRotatef(zRot,0.0,0.0,1.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < n_node; i++)
    {
        glColor3b(col[i].a,col[i].b,col[i].c);
        glVertex3f(vertext[i].x, vertext[i].y, vertext[i].z);
    }
    glEnd();
    glLoadIdentity();
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up:
        xRot-=10;
        break;
    case Qt::Key_Left:
        yRot-=10;
        break;
    case Qt::Key_Right:
        yRot+=10;
        break;
    case Qt::Key_Down:
        xRot+=10;
        break;
    case Qt::Key_L:
        lightFlag=!lightFlag;
        if(lightFlag)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);
        break;
    default:break;
    }
    updateGL();
    QGLWidget::keyPressEvent(event);
}

void MyGLWidget::wheelEvent(QWheelEvent *event)
{
    translate+=event->delta()/100;
    updateGL();
}

void MyGLWidget::enlargePaint()
{
    translate+=0.1;
    updateGL();
}

void MyGLWidget::smallPaint()
{
    translate-=0.1;
    updateGL();
}
