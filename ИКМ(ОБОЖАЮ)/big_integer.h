#pragma once
#include <string>
using namespace std;

// Подключение заголовочного файла для функции setlocale
#include <clocale>

// Константа для определения максимального количества цифр в числе
const int MAX = 10000; // Максимальное количество цифр в числе

// Объявления функций для работы с большими числами

// Функция для инициализации большого числа нулями
void initialize(int num[]);

// Функция для копирования большого числа
void copy(int src[], int dest[]);

// Функция для сравнения двух больших чисел
int compare(int a[], int b[]);

// Функция для сложения двух больших чисел: c = a + b
void big_integer_add(int a[], int b[], int c[]);

// Функция для вычитания двух больших чисел: c = a - b (предполагается, что a >= b)
void big_integer_subtract(int a[], int b[], int c[]);

// Функция для умножения большого числа на маленькое число: c = a * b
void big_integer_multiply_small(int a[], int b, int c[]);

// Функция для вычисления НОД двух больших чисел с помощью алгоритма Евклида
void big_integer_gcd(int a[], int b[], int result[]);

// Функция для вывода большого числа на экран
void print_big_integer(int num[]);