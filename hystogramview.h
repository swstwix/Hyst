#ifndef HYSTOGRAMVIEW_H
#define HYSTOGRAMVIEW_H

#include <QDialog>
#include <QPen>
#include <QPainter>
#include <QPaintEvent>

namespace Ui {
class HystogramView;
}

class HystogramView : public QDialog
{
    Q_OBJECT
    
public:
    explicit HystogramView(int* a, QWidget *parent = 0);
    ~HystogramView();
    
private:
    Ui::HystogramView *ui;
    int* a;

protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // HYSTOGRAMVIEW_H
