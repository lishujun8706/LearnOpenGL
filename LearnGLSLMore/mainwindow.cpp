#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionDrawRect_triggered()
{
    ui->openGLWidget->drawShape(ABXOpenGLWidget::Rect);
}


void MainWindow::on_actionClear_triggered()
{
    ui->openGLWidget->drawShape(ABXOpenGLWidget::None);
}


void MainWindow::on_actionWireLine_triggered()
{
    ui->openGLWidget->wireDraw(ui->actionWireLine->isChecked());
}

