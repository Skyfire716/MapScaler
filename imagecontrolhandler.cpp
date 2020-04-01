#include "imagecontrolhandler.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QDebug>
#include <QString>
#include <qsizepolicy.h>
#include <QToolTip>

imagecontrolhandler::imagecontrolhandler(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("webImageHandler");
    master = new QGridLayout(this);

    scrollGrid = new QGridLayout(this);

    layout = new QHBoxLayout(this);

    imageView = new QLabel(this);

    scrollArea = new QScrollArea(this);

    counterClockWise = new QPushButton(this);
    clockWise = new QPushButton(this);
    minScale = new QLineEdit(this);
    maxScale = new QLineEdit(this);
    scaler = new QSlider(Qt::Horizontal, this);

    counterClockWise->setText("CCW");
    clockWise->setText("CW");

    minValidator = new QDoubleValidator(minValue, 0.9999, 4);
    maxValidator = new QDoubleValidator(1.1111, maxValue, 4);

    minScale->setValidator(minValidator);
    maxScale->setValidator(maxValidator);
    minScale->setText(QString::number(minStartValue));
    maxScale->setText(QString::number(maxStartValue));

    scaler->setMinimum(minScalerValue);
    scaler->setMaximum(maxScalerValue);
    scaler->setValue(map(1, minStartValue, maxStartValue, minScalerValue, maxScalerValue));

    layout->addWidget(counterClockWise);
    layout->addWidget(minScale);
    layout->addWidget(scaler);
    layout->addWidget(maxScale);
    layout->addWidget(clockWise);

    connect(counterClockWise, SIGNAL(clicked()), this, SLOT(rotateCounterClockWise()));
    connect(clockWise, SIGNAL(clicked()), this, SLOT(rotateClockWise()));
    connect(minScale, SIGNAL(editingFinished()), this, SLOT(scaleChanged()));
    connect(maxScale, SIGNAL(editingFinished()), this, SLOT(scaleChangedM()));
    connect(scaler, SIGNAL(sliderReleased()), this, SLOT(scalerChanged()));
    connect(scaler, SIGNAL(valueChanged()), this, SLOT(scalerChangedT()));

    scrollArea->setLayout(scrollGrid);
    scrollArea->setWidget(imageView);
    scrollArea->show();

    master->addLayout(layout, 0, 0);
    master->addWidget(scrollArea);
}

void imagecontrolhandler::setPixMap(QPixmap image)
{
    this->original = image;
    rotation = 0;
    imageChange();
}

void imagecontrolhandler::rotateCounterClockWise()
{
    rotation -= 90;
    imageChange();
}

void imagecontrolhandler::rotateClockWise()
{
    rotation += 90;
    imageChange();
}


void imagecontrolhandler::scaleChanged()
{
    qDebug() << "Value";
    scaleBoundsChanged();
}

void imagecontrolhandler::scaleChangedM()
{
    scaleBoundsChanged();
}

void imagecontrolhandler::scalerChanged()
{
    imageChange();
}

void imagecontrolhandler::scalerChangedT()
{
    QToolTip::showText(scaler->pos(), "x" + QString::number(map(scaler->value(), minScalerValue, maxScalerValue, minValue, maxValue)));
}


double imagecontrolhandler::map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void imagecontrolhandler::imageChange()
{
    this->image = this->original.scaledToWidth(original.width() * map(scaler->value(), minScalerValue, maxScalerValue, minValue, maxValue));
    QMatrix rm;
    rm.rotate(rotation);
    imageView->setPixmap(image.transformed(rm));
    image = *imageView->pixmap();
    imageView->resize(image.size());
}

void imagecontrolhandler::scaleBoundsChanged()
{
    double actualValue = map(scaler->value(), minScalerValue, maxScalerValue, minValue, maxValue);
    minValue = minScale->text().toDouble();
    maxValue = maxScale->text().toDouble();
    scaler->setValue(map(actualValue, minValue, maxValue, minScalerValue, maxScalerValue));
    qDebug() << "Min " << QString::number(minValue) << " max " << QString::number(maxValue);
}


