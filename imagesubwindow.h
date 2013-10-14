#ifndef IMAGESUBWINDOW_H
#define IMAGESUBWINDOW_H


#include <QMessageBox>
#include <QMdiSubWindow>
#include <QLabel>
#include <QScrollArea>
#include <QPixmap>
#include <QImage>
#include <iostream>

#include "imagesubwindow.h"

class ImageSubwindow : public QMdiSubWindow
{
    Q_OBJECT
public:

    ImageSubwindow();
    explicit ImageSubwindow(QWidget *parent);

    QScrollArea ScrollArea;
    QLabel Label;
    QPixmap Pixmap;
    QImage image;

    void newFile();
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    bool median();
    bool emboss();
    bool sobelEdgeDetect();
    bool gamma(double sigma);
    bool posterize(int levels);
    void negate();
    void adjustIntensity(int intChange);
    void smooth();
    QString userFriendlyCurrentFile();
    QString currentFile();

//protected:
//    void closeEvent(QCloseEvent *event);
    void fitToPixmap();
    void resizeFrame();
    void fitToMainWindow();
    void focusInEvent(QFocusEvent *focusInEvent);

//private:
    bool maybeSave();
    void setCurrentFile(QString fileName);
    QString strippedName(const QString &fullFileName);
    QWidget* parentMW;
    QString curFile;
    bool isUntitled;

signals:

public slots:

};

#endif // IMAGESUBWINDOW_H
