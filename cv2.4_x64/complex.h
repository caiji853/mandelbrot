#pragma once

#include<iostream>
#include<cmath>
using namespace std;


class Complex
{
private:

	void show();
	long double real;
	long double image;
public:

	Complex(){real=0;image=0;}
	~Complex(){}
	Complex(double a,double b){real=a;image=b;}
	long double& getReal(){return real;}
	long double& getImage(){return image;}
	void setReal(double real){this->real = real;}
	void setImage(double image){this->image = image;}
	long double modulus(){return sqrt(real*real+image*image);}
	Complex operator +(Complex &other);
	Complex operator +(const double &other);
	Complex operator +(const int &other);

	Complex operator -(Complex &other);
	Complex operator -(const double &other);
	Complex operator -(const int &other);

	Complex operator *(Complex &other);
	Complex operator *(const double &other);
	Complex operator *(const int &other);

	Complex operator /(Complex &other);
	Complex operator /(const double &other);
	Complex operator /(const int &other);

	void operator +=(Complex &other);
	void operator +=(const double &other);
	void operator +=(const int &other);

	void operator -=(Complex &other);
	void operator -=(const double &other);
	void operator -=(const int &other);

	void operator *=(Complex &other);
	void operator *=(const double &other);
	void operator *=(const int &other);

	void operator /=(Complex &other);
	void operator /=(const double &other);
	void operator /=(const int &other);

	Complex operator =(Complex &other);
	Complex operator =(const double &other);
	Complex operator =(const int &other);

	bool operator ==(Complex &other);
	bool operator ==(const double &other);
	bool operator ==(const int &other);

	friend ostream& operator<<(ostream &os,Complex &other);
	friend istream& operator>>(istream &is,Complex &other);
};

