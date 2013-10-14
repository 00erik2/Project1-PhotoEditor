#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QtWidgets>
#include "mainwindow.h"
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

    ImageSubwindow* currentChild;
    
protected:
    ImageSubwindow* createChild();

private slots:
    void on_actionNew_triggered();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionDespeckle_triggered();

    void on_actionEmboss_triggered();

    void on_actionEdge_triggered();

    void on_actionPosterize_triggered();

    void on_actionNegative_triggered();

    void on_actionSharpen_triggered();

    void on_actionSoften_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
