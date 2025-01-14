#include "big_integer.h"
#include <iostream>
using namespace std;

// ���������� ������������ ���� ��� ������� setlocale
#include <clocale>

// ������� ��� ������������� �������� ����� ������
void initialize(int num[]) {
    for (int i = 0; i < MAX; i++) {
        num[i] = 0;
    }
}

// ������� ��� ����������� �������� �����
void copy(int src[], int dest[]) {
    for (int i = 0; i < MAX; i++) {
        dest[i] = src[i];
    }
}

// ������� ��� ��������� ���� ������� �����
int compare(int a[], int b[]) {
    for (int i = MAX - 1; i >= 0; i--) {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }
    return 0;
}

// ������� ��� �������� ���� ������� �����: c = a + b
void big_integer_add(int a[], int b[], int c[]) {
    int carry = 0; // ������� ��� ��������
    for (int i = 0; i < MAX; i++) {
        int sum = a[i] + b[i] + carry;
        c[i] = sum % 10; // ������� ����� ����������
        carry = sum / 10; // ���������� ��������
    }
}

// ������� ��� ��������� ���� ������� �����: c = a - b (��������������, ��� a >= b)
void big_integer_subtract(int a[], int b[], int c[]) {
    int borrow = 0; // ��� ��� ���������
    for (int i = 0; i < MAX; i++) {
        int sub = a[i] - b[i] - borrow;
        if (sub < 0) {
            sub += 10;
            borrow = 1; // ���������� ����
        }
        else {
            borrow = 0;
        }
        c[i] = sub; // ������� ����� ����������
    }
}

// ������� ��� ��������� �������� ����� �� ��������� �����: c = a * b
void big_integer_multiply_small(int a[], int b, int c[]) {
    initialize(c); // ������������� ���������� ������
    int carry = 0; // ������� ��� ���������
    for (int i = 0; i < MAX; i++) {
        int mul = a[i] * b + carry;
        c[i] = mul % 10; // ������� ����� ����������
        carry = mul / 10; // ���������� ��������
    }
}

// ������� ��� ���������� ��� ���� ������� ����� � ������� ��������� �������
void big_integer_gcd(int a[], int b[], int result[]) {
    int zero[MAX], aa[MAX], bb[MAX], temp[MAX];
    initialize(zero); // ������, �������������� ����
    copy(a, aa);      // ����� ����� a
    copy(b, bb);      // ����� ����� b
    while (compare(bb, zero) != 0) {
        // ��������� ������� r = aa % bb
        int r[MAX];
        initialize(r);
        copy(aa, r);
        while (compare(r, bb) >= 0) {
            big_integer_subtract(r, bb, temp);
            copy(temp, r);
        }
        // ��������� aa � bb
        copy(bb, aa);
        copy(r, bb);
    }
    copy(aa, result); // ��� ��������� � aa
}

// ������� ��� ������ �������� ����� �� �����
void print_big_integer(int num[]) {
    int i = MAX - 1;
    // ���������� ������� ����
    while (i > 0 && num[i] == 0) i--;
    if (i == -1) {
        cout << 0;
        return;
    }
    // ������� �����
    for (; i >= 0; i--) {
        cout << num[i];
    }
}