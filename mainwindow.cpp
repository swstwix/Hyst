#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->labeledImage = NULL;
    this->scrollArea = NULL;
    this->currentImage = NULL;
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

bool MainWindow::IsGrayScalled(){
    if (currentImage == NULL)
        return false;
    for (int i = 0; i < currentImage->width(); i++)
        for (int j = 0; j < currentImage->height(); j++)
        {
            QColor color(currentImage->pixel(i, j));
            int r = color.red();
            int g = color.green();
            int b = color.blue();
            if ((r != g) || (r != b))
                return false;
        }
    return true;
}

void MainWindow::on_BuildHystoramAction_triggered()
{
    if (currentImage != NULL && IsGrayScalled())
    {
        int *a = new int[256];
        for (int i = 0; i < 256; i++)
            a[i] = 0;
        for (int i = 0; i < currentImage->width(); i++)
            for (int j = 0; j < currentImage->height(); j++)
            {
                QColor color(currentImage->pixel(i, j));
                a[color.green()]++;
            }
        HystogramView* view = new HystogramView(a, this);
        view->show();
    }
    else
    {
        QMessageBox messageBox(this);
        messageBox.setText("Not grayed .. !");
        messageBox.exec();
    }
}

int get_random(int a, int b) {
    return qrand() % ((b + 1) - a) + a;
}

void MainWindow::on_NormalizeHystAction_triggered()
{
    int *h = new int[256];
    double h_avg = 0;
    for (int i = 0; i < 256; i++)
        h[i] = 0;
    for (int i = 0; i < currentImage->width(); i++)
        for (int j = 0; j < currentImage->height(); j++)
        {
            QColor color(currentImage->pixel(i, j));
            h[color.green()]++;
            h_avg += color.green();
        }

    int z = 0, h_int = 0;
    h_avg /= currentImage->width()*currentImage->height();
    int *left = new int[255], *right = new int[255], *new_h = new int[255];
    for (int j = 0; j < 255; j++) {
        left[j] = z;
        h_int += h[j];
        while(h_int > h_avg){
            h_int -= h_avg;
            z++;
        }
        right[j] = z;
        new_h[j] = (right[j] + left[j])/2;
    }

    for (int i = 0; i < currentImage->width(); i++)
        for(int j = 0; j < currentImage->height(); j++){
            QColor color(currentImage->pixel(i,j));
            int c = color.green();
            {
                int r = get_random(0, new_h[j]);
                int new_br = new_h[c];
                currentImage->setPixel(i, j, qRgb(new_br,new_br,new_br));
            }
        }
//    for (int i = 0; i < currentImage->width(); i++)
//        for(int j = 0; j < currentImage->height(); j++){
//            QColor color(currentImage->pixel(i,j));
//            int c = color.green();
//            if (left[c] == right[c])
//                currentImage->setPixel(i, j, qRgb(left[c],left[c],left[c]));
//            else
//            {
//                int r = get_random(0, new_h[j]);
//                int new_br = left[c] + r;
//                currentImage->setPixel(i, j, qRgb(new_br,new_br,new_br));
//            }
//        }
//    for (int i = 0; i < currentImage->width(); i++)
//        for(int j = 0; j < currentImage->height(); j++){
//            QColor color(currentImage->pixel(i,j));
//            int c = color.green();
//            {
//                int r = get_random(0, new_h[j]);
//                int new_br = left[c]+r;
//                currentImage->setPixel(i, j, qRgb(new_br,new_br,new_br));
//            }
//        }
    labeledImage = new QLabel(scrollArea);
    labeledImage->setPixmap(QPixmap::fromImage(*currentImage));
    labeledImage->setScaledContents(true);
    scrollArea->setWidget(labeledImage);
}
