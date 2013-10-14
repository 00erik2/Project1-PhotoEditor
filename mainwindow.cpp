#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtWidgets"
#include <QImage>
#include <iostream>
#include <cmath>
#include <QMainWindow>
#include <QLabel>
#include "imagesubwindow.h"
#include "imageProcessing.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    currentChild = NULL;
    ui->setupUi(this);
//   mdiArea = new QMdiArea;
//   setCentralWidget(mdiArea);
//   connect(mdiArea, SIGNAL(subWindowActivated(QMdiArea*)),
//   this, SLOT(updateActions()));
}

MainWindow::~MainWindow()
{
    delete currentChild;
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    // Initiate Open file dialog

    // if file was valid
        // create mdi child widget with file displayed as pixmap
    cout << "New was clicked!" << endl;
}

void MainWindow::on_actionSave_triggered()
{
    cout << "Save was clicked!" << endl;
    currentChild->save();
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
    ImageSubwindow *child = new ImageSubwindow(this);
    ui->mdiArea->addSubWindow(child);

    return child;
}



void MainWindow::on_actionDespeckle_triggered()
{
   currentChild->median();
}

void MainWindow::on_actionEmboss_triggered()
{
    currentChild->emboss();
}

void MainWindow::on_actionEdge_triggered()
{
    currentChild->sobelEdgeDetect();
}

void MainWindow::on_actionPosterize_triggered()
{
    currentChild->posterize(0);
}

void MainWindow::on_actionNegative_triggered()
{
    currentChild->negate();
}

void MainWindow::on_actionSharpen_triggered()
{
    currentChild->adjustIntensity(50);
}

void MainWindow::on_actionSoften_triggered()
{
    currentChild->smooth();
}
