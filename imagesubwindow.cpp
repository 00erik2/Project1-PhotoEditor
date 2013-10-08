#include "imagesubwindow.h"

ImageSubwindow::ImageSubwindow() :
    QMdiSubWindow()
{
    setWidget(&ScrollArea);
    ScrollArea.setWidget(&Label);
}

ImageSubwindow::ImageSubwindow(QWidget *parent) :
    QMdiSubWindow(parent)
{
    setWidget(&ScrollArea);
    ScrollArea.setWidget(&Label);
}

void ImageSubwindow::fitToPixmap()
{
    this->resize(Pixmap.width(), Pixmap.height());
}

void ImageSubwindow::resizeFrame()
{
    ScrollArea.adjustSize();
    ScrollArea.resize(this->width(), this->height());

    Label.adjustSize();
    Label.resize(this->width(), this->height());

}

bool ImageSubwindow::loadFile(const QString &fileName)
{
    if (!Pixmap.load(fileName, 0, Qt::AutoColor)) {
            QMessageBox::warning(this, tr("MDI"),
                                 tr("Cannot read file %1.")
                                 .arg(fileName));
            return false;
        }

        fitToPixmap(); //fits the whole subwindow's size to be the size of the pixmap
        resizeFrame(); //fits the contents of the subwindow to match the subwindow's size

        //now, assign the pixmap to the label
        Label.setPixmap(Pixmap);

        Label.show();
        this->show();

        return true;
}

