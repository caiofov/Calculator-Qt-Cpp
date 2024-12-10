#ifndef OPERATION_H
#define OPERATION_H

#include <QString>

enum class Operation {
    NONE,
    ADD,
    SUB,
    MULT,
    DIV,
    MOD
};

Operation stringToOperationEnum(const QString& str);
double performOperation(Operation operation, double val1, double val2);

#endif // OPERATION_H
