#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "abxopenglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionDrawRect_triggered();

    void on_actionClear_triggered();

    void on_actionWireLine_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
