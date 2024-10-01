#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 5 || argc > 7) {
        cout << "Справочный материал." << endl
             << "Для выполнения операции умножения напишите: -o multiply n1 n2 n3 n4 [n5] [n6]" << endl
             << "Для выполнения операции деления напишите: -o divide n1 n2 n3 n4 [n5] [n6]" << endl;
        exit(0);
    }

    int opt;
    string operation;

    while((opt = getopt(argc, argv, "o:")) != -1) {
        operation = optarg;
    }

    vector<double> operands;
    for(int i = optind; i < argc; i++) {
        operands.push_back(atof(argv[i]));
    }

    if(operands.size() < 4 || operands.size() > 6) {
        cout << "Количество операндов должно быть от 4 до 6." << endl;
        exit(1);
    }

    if(operation == "multiply") {
        double result = 1.0;
        for(double operand : operands) {
            result *= operand;
        }
        cout << "Результат умножения: " << result << endl;
    } else if(operation == "divide") {
        double result = operands[0];
        for(size_t i = 1; i < operands.size(); i++) {
            if(operands[i] == 0) {
                cout << "Ошибка: Деление на ноль!" << endl;
                exit(1);
            }
            result /= operands[i];
        }
        cout << "Результат деления: " << result << endl;
    } else {
        cout << "Неизвестная операция. Используйте 'multiply' или 'divide'." << endl;
        exit(1);
    }

    return 0;
}
