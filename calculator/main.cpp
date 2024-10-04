#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 5 || argc > 7) {
        cout << "Справочный материал." << endl
             << "Для выполнения операции умножения напишите: -o multiply n1 n2 n3 n4 [n5] [n6]" << endl
             << "Для выполнения операции деления напишите: -o divide n1 n2 n3 n4 [n5] [n6]" << endl;
        return 1;
    }

    string operation;
    vector<double> operands;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                operation = argv[i + 1];
                i++;
            } else {
                cerr << "Ошибка: Не указана операция." << endl;
                return 1;
            }
        } else {
            char* endptr;
            double operand = strtod(argv[i], &endptr);
            if (*endptr != '\0') {
                cerr << "Ошибка: Входные данные должны быть числами." << endl;
                return 1;
            }
            operands.push_back(operand);
        }
    }

    if (operation.empty()) {
        cerr << "Ошибка: Не указана операция. Используйте '-o'." << endl;
        exit(1);
    }

    if (operands.size() < 4 || operands.size() > 6) {
        cerr << "Количество операндов должно быть от 4 до 6." << endl;
        return 1;
    }

    try {
        if (operation == "multiply") {
            double result = 1.0;
            for (double operand : operands) {
                result *= operand;
            }
            cout << "Результат умножения: " << result << endl;
        } else if (operation == "divide") {
            double result = operands[0];
            for (size_t i = 1; i < operands.size(); i++) {
                if (operands[i] == 0) {
                    throw runtime_error("Ошибка: Деление на ноль!");
                }
                result /= operands[i];
            }
            cout << "Результат деления: " << result << endl;
        } else {
            throw runtime_error("Неизвестная операция. Используйте 'multiply' или 'divide'.");
        }
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}
