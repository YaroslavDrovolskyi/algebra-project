#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BigInt.h"
#include "BigModInt.h"
#include <QMessageBox>
#include "string"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    BigInt a(100000);
    BigInt b(100000);
    BigInt c = a + b;

//    sieve(); // run Sieve of Eratosthenes to init algo of prime factorization


    BigModInt m(BigInt{"32456789765432456787654324567843567"}, BigInt{"24356789876543234567890765432456789543245678976543245676"});
    std::cout << m.getNumber() << std::endl;

    ui->operator_select_1->addItems(this->numb_calc.operations_names);
    ui->operator_select_2->addItems(this->numb_calc.algorithms_names);
    ui->operator_select_3->addItems(this->pol_ring_calc.operations_names);
    ui->operator_select_4->addItems(this->pol_field_calc.algorithms_names);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_calculate_btn_1_clicked()
{
    std::string modulus_str = ui->modulus_input->text().toStdString();
    std::string left_number_str = ui->number1_input->text().toStdString();
    std::string right_number_str = ui->number2_input->text().toStdString();
    std::size_t op_index = ui->operator_select_1->currentIndex();

    try{ // try to catch invalid input
        BigInt modulus(modulus_str);
        BigModInt left_number{BigInt(left_number_str), BigInt(modulus_str)};
        BigModInt right_number{BigInt(right_number_str), BigInt(modulus_str)};

        QString result = numb_calc.calculate(op_index, left_number, right_number);

        ui->result_1->setText(result);
    }
    catch(std::exception& e){
        QMessageBox::warning(this, "Warning", e.what());
    }
}

void MainWindow::on_calculate_btn_9_clicked()
{
    std::string modulus_str = ui->modulus_input->text().toStdString();
    std::string number_str = ui->number3_input_4->text().toStdString();
    std::string base_str = ui->number3_input_3->text().toStdString();

    try{ // try to catch invalid input
        BigInt modulus(modulus_str);
        BigModInt number{BigInt(number_str), BigInt(modulus_str)};
        BigModInt base{BigInt(base_str), BigInt(modulus_str)};

        QString result = numb_calc.calcLog(number, base);

        ui->result_10->setText(result);
    }
    catch(std::exception& e){
        QMessageBox::warning(this, "Warning", e.what());
    }
}


void MainWindow::on_calculate_btn_2_clicked()
{
    std::string modulus_str = ui->modulus_input->text().toStdString();
    std::string number_str = ui->number3_input->text().toStdString();
    std::size_t algo_index = ui->operator_select_2->currentIndex();

    try{ // try to catch invalid input
        BigModInt number{BigInt{number_str}, BigInt{modulus_str}};

        QString result = numb_calc.calculate(algo_index, number); // calculate result

        ui->result_2->setText(result);
    }
    catch(const std::exception& e){
        QMessageBox::warning(this, "Warning", e.what());
    }
}


void MainWindow::on_calculate_btn_3_clicked()
{
    std::string modulus_str = ui->modulus_input->text().toStdString();
    std::string left_pol_str = ui->polynomial_1_input->text().toStdString();
    std::string right_pol_str = ui->polynomial_2_input->text().toStdString();
    std::size_t op_index = ui->operator_select_3->currentIndex();

    try{
        BigInt modulus(modulus_str);
        Polynomial left_pol(left_pol_str, modulus);
        Polynomial right_pol(right_pol_str, modulus);

        QString result = pol_ring_calc.calc(op_index, left_pol, right_pol);

        ui->result_3->setText(result);
    }
    catch(const std::exception& e){
        QMessageBox::warning(this, "Warning", e.what());
    }
}


void MainWindow::on_calculate_btn_4_clicked()
{
    std::string modulus_str = ui->modulus_input->text().toStdString();
    std::string pol_str = ui->polynomial_3_input->text().toStdString();

    try{
        BigInt modulus(modulus_str);
        Polynomial pol(pol_str, modulus);

        QString result = pol_ring_calc.calcDerivative(pol);

        ui->result_4->setText(result);
    }
    catch(const std::exception& e){
        QMessageBox::warning(this, "Warning", e.what());
    }
}


void MainWindow::on_calculate_btn_5_clicked()
{
    std::string modulus_str = ui->modulus_input->text().toStdString();
    std::string pol_str = ui->polynomial_4_input->text().toStdString();
    std::string point_str = ui->number4_input->text().toStdString();

    try{
        BigInt modulus(modulus_str);
        Polynomial pol(pol_str, modulus);
        BigModInt point(point_str, modulus_str);

        QString result = pol_ring_calc.calcValue(pol, point);

        ui->result_5->setText(result);
    }
    catch(const std::exception& e){
        QMessageBox::warning(this, "Warning", e.what());
    }
}


void MainWindow::on_calculate_btn_6_clicked()
{
    std::string modulus_str = ui->modulus_input->text().toStdString();
    std::string left_pol_str = ui->polynomial_5_input->text().toStdString();
    std::string right_pol_str = ui->polynomial_6_input->text().toStdString();

    try{
        BigInt modulus(modulus_str);
        Polynomial left_pol(left_pol_str, modulus);
        Polynomial right_pol(right_pol_str, modulus);

        std::pair<QString, QString> result = pol_ring_calc.calcFractionRemainer(left_pol, right_pol);

        if (result.second==""){
            result.second="0";
        }

        ui->result_6->setText(result.first); // print fraction
        ui->result_7->setText(result.second); // print remainder
    }
    catch(const std::exception& e){
        QMessageBox::warning(this, "Warning", e.what());
    }
}


void MainWindow::on_calculate_btn_7_clicked()
{
    std::string modulus_str = ui->modulus_input->text().toStdString();
    std::string order_str = ui->number5_input->text().toStdString();

    try{
        BigInt modulus(modulus_str);
        BigInt order(order_str);


        QString result = pol_ring_calc.calcCyclotomicPolynomial(modulus, order);

        ui->result_8->setText(result);
    }
    catch(const std::exception& e){
        QMessageBox::warning(this, "Warning", e.what());
    }
}


void MainWindow::on_calculate_btn_8_clicked()
{
    std::string modulus_str = ui->modulus_input->text().toStdString();
    std::string irreducible_pol_str = ui->irreducible_polynomial_input->text().toStdString();
    std::string pol_str = ui->polynomial_7_input->text().toStdString();
    std::size_t op_index = ui->operator_select_4->currentIndex();

    try{
        BigInt modulus(modulus_str);
        Polynomial irreducible_pol(irreducible_pol_str, modulus);
        Polynomial value_pol(pol_str, modulus);

        ModPolynomial pol(value_pol, irreducible_pol);

        QString result = pol_field_calc.calc(op_index, irreducible_pol, pol);

        ui->result_9->setText(result);
    }
    catch(const std::exception& e){
        QMessageBox::warning(this, "Warning", e.what());
    }
}




