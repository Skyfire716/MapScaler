#ifndef IMAGECONTROLHANDLER_H
#define IMAGECONTROLHANDLER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QDoubleValidator>
#include <QLabel>
#include <QScrollArea>

class imagecontrolhandler : public QWidget
{
    Q_OBJECT
public:
    explicit imagecontrolhandler(QWidget *parent = nullptr);
    void setPixMap(QPixmap image);

signals:

private slots:
    void rotateCounterClockWise();
    void rotateClockWise();
    void scaleChanged();
    void scaleChangedM();
    void scalerChanged();
    void scalerChangedT();

private:
    QPixmap image;
    QPixmap original;
    QLabel *imageView;
    QHBoxLayout *layout;
    QGridLayout *master;
    QGridLayout *scrollGrid;
    QPushButton *counterClockWise;
    QPushButton *clockWise;
    QLineEdit *minScale;
    QLineEdit *maxScale;
    QSlider *scaler;
    QScrollArea *scrollArea;
    QDoubleValidator *minValidator;
    QDoubleValidator *maxValidator;
    double minValue = 0.0001, maxValue = 30, minStartValue = 0.8, maxStartValue = 3, startValue = 1.0, minScalerValue = 0, maxScalerValue = 100000;
    double map(double x, double in_min, double in_max, double out_min, double out_max);
    int rotation = 0;
    void imageChange();
    void scaleBoundsChanged();


};

#endif // IMAGECONTROLHANDLER_H
