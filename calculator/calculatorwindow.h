#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QMainWindow>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui {
class CalculatorWindow;
}
QT_END_NAMESPACE

class CalculatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    CalculatorWindow(QWidget *parent = nullptr);
    ~CalculatorWindow();

private:
    Ui::CalculatorWindow *ui;

private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();
};
#endif // CALCULATORWINDOW_H
