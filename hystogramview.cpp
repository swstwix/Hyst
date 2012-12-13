#include "hystogramview.h"
#include "ui_hystogramview.h"

HystogramView::HystogramView(int *a, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HystogramView)
{
    this->a = a;
    ui->setupUi(this);
}

void HystogramView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(0,0,this->width(),this->height(),QBrush(Qt::white));
    painter.setPen(QPen(Qt::black));
    int left[256], right[256],z[256], neww[256];
    int max = a[0];
    double hAvg=0;
    double hInt=0;

    for (int i = 0; i< 256; i++){
        hAvg += a[i];
        left[i] = 0;
        right[i] = 0;
        z[i] = 0;
    }
    hAvg = hAvg / 256;
    painter.drawText(10,10,"hAvg = " + QString::number(hAvg));

    for (int i = 0; i < 255; i++){
        left[i] = z[i];
        hInt += a[i];
        while (hInt > hAvg){
            hInt -= hAvg;
            z[i]++;
        }
        right[i] = z[i];
        neww[i] = (left[i] + right[i]) / 2;
    }

    painter.setPen(QPen(Qt::gray));
    for (int i = 0; i < 256; i++)
        if (a[i] > max)
            max = a[i];
    for (int i = 0; i < 256; i++)
        painter.drawLine(i+20,this->height()-20,i+20,this->height() - 0.8*a[i]*this->height()/max - 20);

    int max2 = neww[0];
    for (int i = 0; i < 256; i++)
        max2 = max2 > neww[i] ? max2 : neww[i];

    painter.setPen(QPen(Qt::black));
    for (int i = 0; i < 255; i++)
        painter.drawLine(i+20,this->height() - 0.8*neww[i]*this->height()/max2 - 20, i+1+20,this->height() - 0.8*neww[i+1]*this->height()/max - 20);
    painter.end();
}

HystogramView::~HystogramView()
{
    delete ui;
}
