#include "calculatorwindow.h"
#include "./ui_calculatorwindow.h"
#include <iostream>

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool modTrigger = false;



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

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Module, SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));

    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
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
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    modTrigger = false;

    QString displayValue = ui->Display->text();
    calcVal = displayValue.toDouble();

    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();

    if(QString::compare(buttonValue, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    }
    else if(QString::compare(buttonValue, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    }
    else if(QString::compare(buttonValue, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    }
    else if(QString::compare(buttonValue, "-", Qt::CaseInsensitive) == 0){
        subTrigger = true;
    }
    else if(QString::compare(buttonValue, "%", Qt::CaseInsensitive) == 0){
        modTrigger = true;
    }

    ui->Display->setText("");
}

void CalculatorWindow::EqualButtonPressed(){
    double solution = 0.0;
    double displayValue = ui->Display->text().toDouble();

    if(addTrigger || divTrigger || multTrigger || subTrigger || modTrigger){
        if(addTrigger){
            solution = calcVal + displayValue;
        }
        else if(subTrigger){
            solution = calcVal - displayValue;
        }
        else if(multTrigger){
            solution = calcVal * displayValue;
        }
        else if(divTrigger){
            solution = calcVal / displayValue;
        }
        else if(modTrigger){
            solution = fmod(calcVal , displayValue);
        }
    }

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
