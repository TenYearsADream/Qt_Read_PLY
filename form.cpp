#include "form.h"
#include "ui_form.h"
#include "myglwidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MyGLWidget *w2=0;

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}


void Form::on_openButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this);
    if(filename==""){
        qDebug()<<"invalid filename";
        return;
    }
    w2=new MyGLWidget(ui->frame,filename);
    w2->resize(681,431);
    w2->setFocusPolicy(Qt::ClickFocus);
    w2->show();
}

void Form::on_helpButton_clicked()
{
    QString text="-滑动鼠标滚轮改变图形大小\n-方向键旋转图形\n-L键开闭光源";
    QMessageBox::about(this,"帮助信息",text);
}

void Form::on_enlargeButton_clicked()
{
    if(!w2){
        QMessageBox::about(this,"警告","请先打开文件！");
    }
    w2->enlargePaint();
}

void Form::on_smallButton_clicked()
{
    if(!w2){
        QMessageBox::about(this,"警告","请先打开文件！");
    }
    w2->smallPaint();
}
