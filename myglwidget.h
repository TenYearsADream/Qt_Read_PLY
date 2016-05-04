#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>

struct ver{
    float x,y,z;
};
struct color{
    uchar a,b,c;
};

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0,QString fn="");

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void fillArray();
    void keyPressEvent(QKeyEvent *);
    void wheelEvent(QWheelEvent *);

public:
    void enlargePaint();
    void smallPaint();

signals:

public slots:

private:
    ver *vertext;
    color *col;
    int n_node;
    QString filename;
    GLfloat xRot,yRot,zRot;
    double translate;
    bool lightFlag;

};

#endif // MYGLWIDGET_H
