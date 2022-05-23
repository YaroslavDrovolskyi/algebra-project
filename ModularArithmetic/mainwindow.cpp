#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BigInt.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    BigInt b(100000);
    b.Print();
}

MainWindow::~MainWindow()
{
    delete ui;
}

