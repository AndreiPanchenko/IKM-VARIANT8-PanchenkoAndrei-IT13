#include <iostream>
#include <string>
#include "big_integer.h"
using namespace std;

// Подключаем заголовочный файл для функции setlocale
#include <clocale>

// Главная функция программы
int main() {
    // Устанавливаем русскую локаль для корректного отображения сообщений на русском языке
    setlocale(LC_ALL, "Russian");

    double n;
    cout << "Привет, перед тобой программа для вычисления точного значения суммы дробей: 1/1! + 1/2! + 1/3! + ... + 1/n! " << endl;
    cout << "Введи целое число n (n > 10): ";
    cin >> n;
    // Проверка корректности ввода
    if (cin.fail() || n <= 10 || n != static_cast<int>(n)) {
        cout << "Некорректный ввод. Пожалуйста, введи целое число больше 10" << endl;
        return 0;
    }

    // Инициализация факториала n!
    int factorial[MAX];
    initialize(factorial);
    factorial[0] = 1; // n! = 1

    // Вычисляем n! = 1 * 2 * 3 * ... * n
    for (int i = 2; i <= n; i++) {
        int temp[MAX];
        big_integer_multiply_small(factorial, i, temp);
        copy(temp, factorial);
    }

    // Инициализация суммы числителей
    int sum_numerators[MAX];
    initialize(sum_numerators);

    // Инициализация факториала k!
    int k_factorial[MAX];
    initialize(k_factorial);
    k_factorial[0] = 1;

    int term[MAX];
    initialize(term);

    // Вычисление суммы числителей
    for (int k = 1; k <= n; k++) {
        if (k > 1) {
            // Вычисляем k! (k_factorial *= k)
            int temp_k_fact[MAX];
            big_integer_multiply_small(k_factorial, k, temp_k_fact);
            copy(temp_k_fact, k_factorial);
        }

        // Вычисляем n! / k! без прямого деления, умножая числа от k+1 до n
        initialize(term);
        term[0] = 1;
        for (int i = k + 1; i <= n; i++) {
            int temp_term[MAX];
            big_integer_multiply_small(term, i, temp_term);
            copy(temp_term, term);
        }

        // Суммируем числители
        int temp_sum[MAX];
        big_integer_add(sum_numerators, term, temp_sum);
        copy(temp_sum, sum_numerators);
    }

    // Знаменатель равен n!
    int denominator[MAX];
    copy(factorial, denominator);

    // Вычисляем НОД числителя и знаменателя
    int gcd[MAX];
    big_integer_gcd(sum_numerators, denominator, gcd);

    // Преобразуем большие числа в строки для вывода
    auto big_integer_to_string = [](int num[]) -> string {
        string result = "";
        int i = MAX - 1;
        while (i > 0 && num[i] == 0) i--;
        if (i == -1) return "0";
        for (; i >= 0; i--) {
            result += to_string(num[i]);
        }
        return result;
        };

    // Проверяем, умещается ли НОД в тип int для упрощения деления
    int gcd_int = 0;
    int num_digits_gcd = 0;
    for (int i = MAX - 1; i >= 0; i--) {
        if (gcd[i] != 0) {
            num_digits_gcd = i + 1;
            break;
        }
    }

    if (num_digits_gcd <= 9) { // Если НОД умещается в int
        for (int i = num_digits_gcd - 1; i >= 0; i--) {
            gcd_int = gcd_int * 10 + gcd[i];
        }

        int reduced_numerator[MAX], reduced_denominator[MAX];

        // Функция для деления большого числа на маленькое
        auto big_integer_divide_small = [](int dividend[], int divisor, int quotient[]) {
            initialize(quotient);
            long long remainder = 0;
            for (int i = MAX - 1; i >= 0; i--) {
                long long current = remainder * 10 + dividend[i];
                quotient[i] = current / divisor;
                remainder = current % divisor;
            }
            };

        // Делим числитель и знаменатель на НОД
        big_integer_divide_small(sum_numerators, gcd_int, reduced_numerator);
        big_integer_divide_small(denominator, gcd_int, reduced_denominator);

        // Выводим результат
        cout << "Сумма S = ";
        cout << big_integer_to_string(reduced_numerator) << " / " << big_integer_to_string(reduced_denominator) << endl;
    }
    else {
        // Если НОД слишком большой, выводим несокращенную дробь
        cout << "Сумма S = ";
        cout << big_integer_to_string(sum_numerators) << " / " << big_integer_to_string(denominator) << endl;
        cout << "Не удалось сократить дробь из-за большого НОД." << endl;
    }

    return 0;
}