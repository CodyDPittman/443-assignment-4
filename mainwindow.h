#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QStringList>
#include <QString>
#include <QImageReader>
#include <QByteArray>
#include <QBitmap>
#include <QImage>
#include <QFile>
#include <QFileInfo>
#include <QStringLiteral>
#include <QBuffer>
#include <QDataStream>
#include <QtNetwork/QTcpSocket>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    QTcpSocket *socket;

    void initSocket();

private slots:

    // Original photo
    void on_pushButton_clicked();

    // Overlay photo
    void on_pushButton_2_clicked();


private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H