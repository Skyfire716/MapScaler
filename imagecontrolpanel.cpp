#include "imagecontrolpanel.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>

ImageControlPanel::ImageControlPanel(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout(this);
    counterClockWise = new QPushButton(this);
    clockWise = new QPushButton(this);
    minScale = new QLineEdit(this);
    maxScale = new QLineEdit(this);
    scaler = new QSlider(this);
    minValidator = new QDoubleValidator(0.0000001, 0.9, 4);
    maxValidator = new QDoubleValidator(1.1, 3, 4);
    layout->addWidget(counterClockWise);
    layout->addWidget(minScale);
    layout->addWidget(scaler);
    layout->addWidget(maxScale);
    layout->addWidget(clockWise);

}
