#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtWidgets"
#include <QImage>
#include <iostream>
#include <cmath>
#include <QMainWindow>
#include <QLabel>
#include "imagesubwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//   mdiArea = new QMdiArea;
//   setCentralWidget(mdiArea);
//   connect(mdiArea, SIGNAL(subWindowActivated(QMdiArea*)),
//   this, SLOT(updateActions()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    // Initiate Open file dialog

    // if file was valid
        // create mdi child widget with file displayed as pixmap
    cout << "New was clicked!" << endl;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
//        QMdiSubWindow *existing = findMdiChild(fileName);
//        if (existing) {
//            mdiArea->setActiveSubWindow(existing);
//            return;
//        }

        ImageSubwindow *child = createChild();
        if (child->loadFile(fileName)) {
            statusBar()->showMessage(tr("File loaded"), 2000);
            child->show();
        } else {
            child->close();
        }
    }
}

ImageSubwindow* MainWindow::createChild()
{
    ImageSubwindow *child = new ImageSubwindow();
    ui->mdiArea->addSubWindow(child);

    return child;
}


