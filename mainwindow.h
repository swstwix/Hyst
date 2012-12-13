#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QGraphicsView>
#include <QImage>
#include <QLabel>
#include <QScrollBar>
#include <QVector>
#include <QRgb>
#include <QColor>
#include "hystogramview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QImage* currentImage;
    bool imageIsNormalized;
    QScrollArea* scrollArea;
    QLabel* labeledImage;
    
private:
    Ui::MainWindow *ui;
    bool IsGrayScalled();

private slots:
    void on_OpenAction_triggered();
    void on_ZoomInAction_triggered();
    void on_ZoomOutAction_triggered();
    void on_BuildHystoramAction_triggered();
    void on_NormalizeHystAction_triggered();
};

#endif // MAINWINDOW_H
