#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QUrl>
#include <QWebEngineView>

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
    glayout->addWidget(webView);
    webViewImageLabel = ui->webViewImageLabel;
    webViewTabs = ui->tabWidget;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_shotBtn_clicked()
{
    webViewImageLabel->setPixmap(webView->grab());
    webViewTabs->setCurrentIndex(1);
}

