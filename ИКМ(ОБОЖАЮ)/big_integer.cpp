#include "big_integer.h"
#include <iostream>
using namespace std;

// Подключаем заголовочный файл для функции setlocale
#include <clocale>

// Функция для инициализации большого числа нулями
void initialize(int num[]) {
    for (int i = 0; i < MAX; i++) {
        num[i] = 0;
    }
}

// Функция для копирования большого числа
void copy(int src[], int dest[]) {
    for (int i = 0; i < MAX; i++) {
        dest[i] = src[i];
    }
}

// Функция для сравнения двух больших чисел
int compare(int a[], int b[]) {
    for (int i = MAX - 1; i >= 0; i--) {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }
    return 0;
}

// Функция для сложения двух больших чисел: c = a + b
void big_integer_add(int a[], int b[], int c[]) {
    int carry = 0; // Перенос при сложении
    for (int i = 0; i < MAX; i++) {
        int sum = a[i] + b[i] + carry;
        c[i] = sum % 10; // Текущая цифра результата
        carry = sum / 10; // Обновление переноса
    }
}

// Функция для вычитания двух больших чисел: c = a - b (предполагается, что a >= b)
void big_integer_subtract(int a[], int b[], int c[]) {
    int borrow = 0; // Заём при вычитании
    for (int i = 0; i < MAX; i++) {
        int sub = a[i] - b[i] - borrow;
        if (sub < 0) {
            sub += 10;
            borrow = 1; // Обновление заёма
        }
        else {
            borrow = 0;
        }
        c[i] = sub; // Текущая цифра результата
    }
}

// Функция для умножения большого числа на маленькое число: c = a * b
void big_integer_multiply_small(int a[], int b, int c[]) {
    initialize(c); // Инициализация результата нулями
    int carry = 0; // Перенос при умножении
    for (int i = 0; i < MAX; i++) {
        int mul = a[i] * b + carry;
        c[i] = mul % 10; // Текущая цифра результата
        carry = mul / 10; // Обновление переноса
    }
}

// Функция для вычисления НОД двух больших чисел с помощью алгоритма Евклида
void big_integer_gcd(int a[], int b[], int result[]) {
    int zero[MAX], aa[MAX], bb[MAX], temp[MAX];
    initialize(zero); // Массив, представляющий ноль
    copy(a, aa);      // Копия числа a
    copy(b, bb);      // Копия числа b
    while (compare(bb, zero) != 0) {
        // Вычисляем остаток r = aa % bb
        int r[MAX];
        initialize(r);
        copy(aa, r);
        while (compare(r, bb) >= 0) {
            big_integer_subtract(r, bb, temp);
            copy(temp, r);
        }
        // Обновляем aa и bb
        copy(bb, aa);
        copy(r, bb);
    }
    copy(aa, result); // НОД находится в aa
}

// Функция для вывода большого числа на экран
void print_big_integer(int num[]) {
    int i = MAX - 1;
    // Пропускаем ведущие нули
    while (i > 0 && num[i] == 0) i--;
    if (i == -1) {
        cout << 0;
        return;
    }
    // Выводим число
    for (; i >= 0; i--) {
        cout << num[i];
    }
}