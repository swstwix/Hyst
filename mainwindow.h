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

private slots:
    void on_OpenAction_triggered();
    void on_ZoomInAction_triggered();
    void on_ZoomOutAction_triggered();
};

#endif // MAINWINDOW_H
