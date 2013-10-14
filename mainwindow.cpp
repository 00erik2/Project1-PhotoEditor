#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtWidgets"


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
