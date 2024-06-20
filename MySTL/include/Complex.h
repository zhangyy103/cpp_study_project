#pragma once
#include<iostream>
#include<windows.h>
using namespace std;
class Complex {
private:
	double real, imag;
public:
	Complex(double real, double imag) {
		this->real = real;
		this->imag = imag;
	}
	Complex operator+(Complex& other) {
		return(Complex(real + other.real, imag + other.imag));
	}
	Complex operator-(Complex& other) {
		return(Complex(real - other.real, imag - other.imag));
	}
	Complex operator*(Complex& other) {
		double r = real * other.real - imag * other.imag;
		double i = real * other.imag + imag * other.real;
		return(Complex(r, i));
	}
	Complex operator/(Complex& other) {
		double denominator = other.real * other.real + other.imag * other.imag;
		if (denominator == 0) {
			cout << "分母不为零" << endl;
			exit(0);
		}
		else {
			double r = (real * other.real + imag * other.imag) / denominator;
			double i = (imag * other.real - real * other.imag) / denominator;
			return Complex(r, i);
		}
	}
	void print_complex(Complex comp) {
		cout << comp.real << "+" << comp.imag << "i";
	}
};
void Copmlex(){
	float r1, i1, r2, i2;
	cin >> r1 >> i1;
	cin >> r2 >> i2;
	Complex m(r1, i1);
	Complex n(r2, i2);
	Complex result = m + n;
	result.print_complex(m);
}