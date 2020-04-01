#ifndef IMAGECONTROLPANEL_H
#define IMAGECONTROLPANEL_H

#include <QDoubleValidator>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QWidget>

class ImageControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ImageControlPanel(QWidget *parent = nullptr);

signals:

private:
    QHBoxLayout *layout;
    QPushButton *counterClockWise;
    QPushButton *clockWise;
    QLineEdit *minScale;
    QLineEdit *maxScale;
    QSlider *scaler;
    QDoubleValidator *minValidator;
    QDoubleValidator *maxValidator;

};

#endif // IMAGECONTROLPANEL_H
