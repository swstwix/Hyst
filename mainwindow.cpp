#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenAction_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                         tr("Open File"), QDir::currentPath());

    if (!fileName.isEmpty()) {
            currentImage = new QImage(fileName);
            scrollArea = new QScrollArea(this);
            labeledImage = new QLabel(scrollArea);
            labeledImage->setPixmap(QPixmap::fromImage(*currentImage));
            labeledImage->setScaledContents(true);
            scrollArea->setWidget(labeledImage);
            this->setCentralWidget(scrollArea);
        }

}

void MainWindow::on_ZoomInAction_triggered()
{
    if (labeledImage)
        labeledImage->resize(labeledImage->size() * 1.25);
}

void MainWindow::on_ZoomOutAction_triggered()
{
    if (labeledImage)
        labeledImage->resize(labeledImage->size() / 1.25);
}
