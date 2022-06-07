#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "calculator.h"

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
    void on_calculate_btn_1_clicked();

    void on_calculate_btn_2_clicked();

    void on_calculate_btn_3_clicked();

    void on_calculate_btn_4_clicked();

    void on_calculate_btn_5_clicked();

    void on_calculate_btn_6_clicked();

    void on_calculate_btn_7_clicked();

    void on_calculate_btn_8_clicked();

    void on_calculate_btn_9_clicked();

    void on_calculate_btn_10_clicked();

    void on_calculate_btn_11_clicked();

    void on_calculate_btn_12_clicked();

private:
    Ui::MainWindow *ui;

    NumberCalculator numb_calc;
    PolynomialRingCalculator pol_ring_calc;
    PolynomialFieldCalculator pol_field_calc;
};
#endif // MAINWINDOW_H
