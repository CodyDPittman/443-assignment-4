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
    socket->connectToHost("100.69.238.176", 80);
}

// Reading and loading user selected image
void MainWindow::on_pushButton_clicked()
{
    // Reading image
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr("Images (*.bmp)"));
    file1 = fileName;
    char ch;

    // Loading image
    QImage image(fileName);
    QPixmap p = QPixmap::fromImage(image);


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
    file2 = fileName;

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

// Transfer Orignal Button
void MainWindow::on_pushButton_3_clicked()
{

    // Create a QImage of the recently displayed bitmap
    QImage image(file1);

    // Creating a byte array from the QImage object
    QByteArray arr = QByteArray::fromRawData((const char*)image.bits(), image.byteCount());
    QBuffer buffer(&arr);

    // Creating a buffer from the byte array
    //image.save(&buffer, "BMP");
    //buffer.setBuffer(&arr);
    //buffer.open(QIODevice::ReadOnly);


    // Sending data to the server
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        qDebug() << "Connected!";
        socket->write(arr);
        //socket->waitForBytesWritten();
    }
    else
        qDebug() << "Not connected";


}

// Transfer Overlay Button
void MainWindow::on_pushButton_4_clicked()
{




}

