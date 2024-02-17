#include <stdio.h>

// Определение структуры
struct Data {
    int fd_in;
    // Другие члены структуры могут быть здесь
};

int main() {
    // Создание экземпляра структуры
    struct Data data_instance;

    // Присваивание значения члену структуры с помощью точечной нотации
    data_instance.fd_in = 10;

    // Обращение к значению члена структуры с использованием точечной нотации
    printf("Value of fd_in using dot notation: %d\n", data_instance.fd_in);

    // Создание указателя на структуру
    struct Data *data_pointer = &data_instance;

    // Присваивание значения члену структуры с помощью оператора стрелки
    data_pointer->fd_in = 20;

    // Обращение к значению члена структуры с использованием оператора стрелки
    printf("Value of fd_in using arrow notation: %d\n", data_pointer->fd_in);

    return 0;
}
