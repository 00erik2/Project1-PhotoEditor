#ifndef IMAGESUBWINDOW_H
#define IMAGESUBWINDOW_H
#include <QMessageBox>
#include <QMdiSubWindow>
#include <QLabel>
#include <QScrollArea>
#include <QPixmap>
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

    void newFile();
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    QString userFriendlyCurrentFile();
    QString currentFile() { return curFile; }

protected:
//    void closeEvent(QCloseEvent *event);
    void fitToPixmap();
    void resizeFrame();

private:
    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    QString curFile;
    bool isUntitled;

signals:

public slots:

};

#endif // IMAGESUBWINDOW_H
