#include "calculatorwindow.h"
#include "./ui_calculatorwindow.h"

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;


CalculatorWindow::CalculatorWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CalculatorWindow)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));


    // find buttons and connnect to slots
    QPushButton *numButtons[10];

    for (int i = 0; i < 10; ++i) {
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = findChild<QPushButton *>(buttonName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
}

CalculatorWindow::~CalculatorWindow()
{
    delete ui;
}

void CalculatorWindow::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();
    QString displayValue = ui->Display->text();

    if(displayValue.toDouble() == 0 || displayValue.toDouble() == 0.0){
        ui->Display->setText(buttonValue);
    }else{
        double newValue = (displayValue + buttonValue).toDouble();
        ui->Display->setText(QString::number(newValue, 'g', 16));
    }
}

void CalculatorWindow::MathButtonPressed(){

}
void CalculatorWindow::EqualButton(){

}
void CalculatorWindow::ChangeNumberSign(){

}
