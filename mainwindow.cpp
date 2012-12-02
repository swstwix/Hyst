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
        QImage image(fileName);
        if (!image.isNull()){
            QScrollArea* area = new QScrollArea(ui->tabWidget);
            QLabel* label = new QLabel(area);
            label->setPixmap(QPixmap::fromImage(image));
            area->setWidget(label);
            ui->tabWidget->addTab(area, fileName);
        }
    }

}
