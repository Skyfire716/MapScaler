#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QWebEngineView>

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

private:
    Ui::MainWindow *ui;
    QWebEngineView *webView;
    QLabel *webViewImageLabel;
    QTabWidget *webViewTabs;
};
#endif // MAINWINDOW_H
