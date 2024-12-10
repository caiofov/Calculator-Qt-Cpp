#include "Operation.h"
#include <unordered_map>
#include <stdexcept>

Operation stringToOperationEnum(const QString& str) {
    if (str.isEmpty()){
        return Operation::NONE;
    }

    static const std::unordered_map<std::string, Operation> operationMap = {
        {"+", Operation::ADD},
        {"-", Operation::SUB},
        {"*", Operation::MULT},
        {"/", Operation::DIV},
        {"%", Operation::MOD}
    };

    auto it = operationMap.find(str.toStdString());
    if (it != operationMap.end()) {
        return it->second;
    }

    throw std::invalid_argument("Invalid operation string: " + str.toStdString());
}

double performOperation(Operation operation, double val1, double val2) {
    switch (operation) {
        case Operation::ADD:  return val1 + val2;
        case Operation::SUB:  return val1 - val2;
        case Operation::MULT: return val1 * val2;
        case Operation::DIV:  return val1 / val2;
        case Operation::MOD:  return fmod(val1, val2);
        default: throw std::invalid_argument("Invalid operation");
    }
}
