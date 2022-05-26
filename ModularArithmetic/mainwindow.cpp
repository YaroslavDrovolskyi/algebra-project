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

    BigModInt m(BigInt{"32456789765432456787654324567843567"}, BigInt{"24356789876543234567890765432456789543245678976543245676"});
    std::cout << m.getNumber() << std::endl;

    ui->operator_select_1->addItems(this->calculator.operations_names);
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

        BigModInt result = calculator.calculate(op_index, left_number, right_number);

        ui->result_1->setText(result.getNumber().GetString().c_str());
    }
    catch(std::invalid_argument& msg){
        QMessageBox::warning(this, "Warning", msg.what());
    }
}

