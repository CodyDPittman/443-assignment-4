#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Initializing the socket
void MainWindow::initSocket()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("100.99.99.111", 80);
}

// Reading and loading user selected image
void MainWindow::on_pushButton_clicked()
{
    // Reading image
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr("Images (*.bmp)"));
    char ch;


    // Loading image
    QImage image(fileName);

    QPixmap p = QPixmap::fromImage(image);

    // Storing the image into the byte array
    QByteArray arr = QByteArray::fromRawData((const char*)image.bits(), image.byteCount());

    /*
    for(int i = 0; i < arr.length(); i++)
    {
        //qDebug() << arr.at(i);
    }*/

    // Sending data to the server
    socket->write(arr);

    // Creating a buffer from the byte array
    //buffer.setBuffer(&arr);
    //buffer.open(QIODevice::ReadOnly);
    QBuffer buffer(&arr);
    image.save(&buffer, "BMP");

    socket->flush();
    socket->write(arr);
    socket->waitForBytesWritten();


    // Obtaing images dimensions
    int w = ui->ogPic->width();
    int h = ui->ogPic->height();

    // Placing image onto the UI
    ui->ogPic->setPixmap(p.scaled(w, h, Qt::KeepAspectRatio));
    ui->label_3->setPixmap(p.scaled(w,h, Qt::KeepAspectRatio));
}

// Reading and loading user selected overlay image
void MainWindow::on_pushButton_2_clicked()
{
    // Reading image
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr("Images (*.bmp)"));

    // Loading image
    QImage image(fileName);
    QPixmap p = QPixmap::fromImage(image);

    // Obtaining images dimensions
    int w = ui->overPic->width();
    int h = ui->overPic->height();

    // Placing image onto the UI
    ui->overPic->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_4->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));

}

