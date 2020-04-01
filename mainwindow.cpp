#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QUrl>
#include <QWebEngineView>
#include <QtMath>
#include <QFileDialog>
#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout *glayout = new QGridLayout();
    glayout->setObjectName("GridLayyout");
    ui->webViewTab->setLayout(glayout);
    webView = new QWebEngineView();
    webView->load(QUrl("https://opentopomap.org/"));
    webView->show();
    webView->resize(3200, 2400);
    glayout->addWidget(webView);
    webViewTabs = ui->tabWidget;
    imageBtn = ui->loadMap;
    lineEdit = ui->lineEdit;
    webHandler = ui->webImageHandler;
    loadHandler = ui->loadimagehandler;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_shotBtn_clicked()
{
    QImage img = webView->grab().toImage().convertToFormat(QImage::Format_ARGB32);
    grayScale(&img);
    QImage harrisCorners = getCorners(&img);
    //QImage gaussianImg = gaussian(&img);
    webHandler->setPixMap(QPixmap::fromImage(harrisCorners));
    webViewTabs->setCurrentIndex(1);
}

void MainWindow::grayScale(QImage *image)
{
    for (int y = 0; y < image->height(); y++) {
        for (int x = 0; x < image->width(); x++) {
            image->setPixelColor(x, y, grayScaleV(image->pixel(x, y)));
        }
    }
}

QColor MainWindow::grayScaleV(QColor color)
{
    int c = color.red() * wRed + color.green() * wGreen + color.blue() * wBlue;
    color.setRgb(c, c, c);
    return color;
}

QImage MainWindow::getI(double kernel[3][3], QImage *image)
{
    QImage derivative(image->width(), image->height(), image->format());
    for (int y = 1; y < image->height() - 1; y++) {
        for (int x = 1; x < image->width() - 1; x++) {
            double diff = getIV(x, y, kernel, image);
            QColor diffColor;
            diffColor.setRgb(diff, diff, diff);
            derivative.setPixelColor(x, y, diffColor);
        }
    }
    return derivative;
}

double MainWindow::getIV(int x, int y, double kernel[3][3], QImage *image)
{
    double diff = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            diff += image->pixelColor(x + i, y + j).green() * kernel[i + 1][j + 1];
        }
    }
    if (diff < 0) {
        diff = 0;
    }else if (diff > 255) {
        diff = 255;
    }
    return diff;
}

QImage MainWindow::getCorners(QImage *image)
{
    bool circle = false;
    uint width = image->width(), height = image->height();
    double i_x, i_y;
    int px,py,pval;
    QImage corners(width, height, image->format());
    for (uint j = 1; j < height - 1; j++) {
        for (uint i = 1; i < width - 1; i++) {
            i_x = getIV(i, j, x_kernel, image);
            i_y = getIV(i, j, y_kernel, image);
            double val = CornerResponseFunktion(i_x * i_x, i_y * i_y, i_x * i_y, alpha);
            val = qAbs(val);
            if (val > schwellwert_unten) {
                qDebug() << "Val " << QString::number(val);
                corners.setPixel(i, j, val);
                if (!circle) {
                    if (i > 500 && i < 600) {
                        if (j > 500 && j < 600) {
                            circle = true;
                            px = i;
                            py = j;
                            pval = val / 100000;
                        }
                    }
                }
            }
        }
    }
    QPainter p;
    p.begin(&corners);

    p.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    p.setRenderHints(QPainter::HighQualityAntialiasing);

    p.setBrush(Qt::red);
    p.setPen(QPen(Qt::red,10.0));
    p.drawEllipse(px, py, pval, pval);
    p.end();
    return corners;
}

QImage MainWindow::gaussian(QImage *image)
{
    double sigma = 1.2;
    uint width = image->width(), height = image->height();
    QImage gauss(width, height, image->format());
    for (uint i = 1; i < width - 1; i++) {
        for (uint j = 1; j < height - 1; j++) {
            gauss.setPixel(i, j, image->pixel(i, j) * ((1 / 2 * M_PI * qPow(sigma, 2)) * qExp(- (qPow(i, 2) + qPow(j, 2)) / (2 * qPow(sigma, 2)))));
        }
    }
    return gauss;
}

double MainWindow::CornerResponseFunktion(double a, double b, double c, double alpha)
{
    return (a * b - qPow(c, 2)) - alpha * qPow((a + b), 2);
}


void MainWindow::on_loadMap_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Load Map"), "", tr("Map (*.png *.jpg *.bmp);;All Files (*)"));
    QImage map(QPixmap(file).toImage().convertToFormat(QImage::Format_ARGB32));
    grayScale(&map);
    QImage mapCorners = getCorners(&map);
    loadHandler->setPixMap(QPixmap::fromImage(mapCorners));
}

void MainWindow::on_lineEdit_editingFinished()
{
    schwellwert_unten = lineEdit->text().toUInt();
}
