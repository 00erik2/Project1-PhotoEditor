#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QtWidgets>
#include "imagesubwindow.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
protected:
    ImageSubwindow* createChild();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
