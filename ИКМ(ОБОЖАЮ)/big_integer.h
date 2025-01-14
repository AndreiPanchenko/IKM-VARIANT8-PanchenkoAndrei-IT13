#pragma once
#include <string>
using namespace std;

// ����������� ������������� ����� ��� ������� setlocale
#include <clocale>

// ��������� ��� ����������� ������������� ���������� ���� � �����
const int MAX = 10000; // ������������ ���������� ���� � �����

// ���������� ������� ��� ������ � �������� �������

// ������� ��� ������������� �������� ����� ������
void initialize(int num[]);

// ������� ��� ����������� �������� �����
void copy(int src[], int dest[]);

// ������� ��� ��������� ���� ������� �����
int compare(int a[], int b[]);

// ������� ��� �������� ���� ������� �����: c = a + b
void big_integer_add(int a[], int b[], int c[]);

// ������� ��� ��������� ���� ������� �����: c = a - b (��������������, ��� a >= b)
void big_integer_subtract(int a[], int b[], int c[]);

// ������� ��� ��������� �������� ����� �� ��������� �����: c = a * b
void big_integer_multiply_small(int a[], int b, int c[]);

// ������� ��� ���������� ��� ���� ������� ����� � ������� ��������� �������
void big_integer_gcd(int a[], int b[], int result[]);

// ������� ��� ������ �������� ����� �� �����
void print_big_integer(int num[]);