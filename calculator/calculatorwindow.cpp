#include "calculatorwindow.h"
#include "./ui_calculatorwindow.h"
#include "operation.h"

double calcVal = 0.0;
Operation lastOperation = Operation::NONE;


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

    connect(ui->Decimal, SIGNAL(released()), this, SLOT(DecimalButtonPressed()));

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Module, SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));

    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));

    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearButtonPressed()));

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
    lastOperation = Operation::NONE;

    QString displayValue = ui->Display->text();
    calcVal = displayValue.toDouble();

    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();

    lastOperation = stringToOperationEnum(buttonValue);

    ui->Display->setText("");
}

void CalculatorWindow::EqualButtonPressed(){
    if(lastOperation == Operation::NONE){
        return;
    }
    double solution = 0.0;
    double displayValue = ui->Display->text().toDouble();
    solution = performOperation(lastOperation, calcVal, displayValue);

    ui->Display->setText(QString::number(solution));
    calcVal = solution;

}

void CalculatorWindow::ChangeNumberSign(){
    QString displayValue = ui->Display->text();
    QRegularExpression reg("[-]?[0-9.]*");
    QRegularExpressionMatch match = reg.match(displayValue);

    if(match.hasMatch()) {
        double dblDisplayVal = displayValue.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;

        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}

void CalculatorWindow::ClearButtonPressed(){
    calcVal = 0.0;
    ui->Display->setText(QString::number(calcVal));

    lastOperation = Operation::NONE;
}


void CalculatorWindow::DecimalButtonPressed(){
    QString currentValue = ui->Display->text();
    if(!currentValue.contains(".")){
        ui->Display->setText( currentValue + ".");
    }
}
