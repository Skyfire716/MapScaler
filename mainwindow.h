#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QWebEngineView>
#include <QAbstractButton>
#include <QLineEdit>
#include "imagecontrolhandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_shotBtn_clicked();

    void on_loadMap_clicked();

    void on_lineEdit_editingFinished();

private:
    Ui::MainWindow *ui;
    QWebEngineView *webView;
    QLineEdit *lineEdit;
    QAbstractButton *imageBtn;
    QTabWidget *webViewTabs;
    void grayScale(QImage *image);
    QColor grayScaleV(QColor color);
    QImage getI(double kernel[3][3], QImage *image);
    double getIV(int x, int y, double kernel[3][3], QImage *image);
    QImage getCorners(QImage *image);
    QImage gaussian(QImage *image);
    imagecontrolhandler *webHandler;
    imagecontrolhandler *loadHandler;
    double CornerResponseFunktion(double a, double b, double c, double alpha);
    double alpha = 0.25;
    double schwellwert_unten = 100000;
    double wRed = 0.299, wGreen = 0.587;
    double wBlue = 1 - (wRed + wGreen);
    double y_kernel[3][3] = {{-1, -2, -1},{0, 0, 0},{1, 2, 1}};
    double x_kernel[3][3] = {{-1, 0, 1},{-2, 0, 2},{-1, 0, 1}};
};
#endif // MAINWINDOW_H
