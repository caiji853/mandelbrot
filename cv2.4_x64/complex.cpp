#include "complex.h"


void Complex::show()
{

	if(real>0&&image<0)
		printf("%g%gi",real,image);
	else if(real>0&&image>0)
		printf("%g+%gi",real,image);
	else if(real<0&&image>0)
		printf("%g+%gi",real,image);
	else if(real<0&&image<0)
		printf("%g%gi",real,image);
	else if(real==0&&image!=0)
		printf("%gi",image);
	else if(real!=0&&image==0)
		printf("%g",real);
	else 
		printf("0");
}

Complex Complex::operator+(Complex &other)
{
	Complex temp;
	temp.real=real+other.real;
	temp.image=image+other.image;
	return temp;
}

Complex Complex::operator +(const double &other)
{

	Complex temp;
	temp.real=real+other;
	temp.image=image;
	return temp;
}

Complex Complex::operator +(const int &other)
{
	Complex temp;
	temp.real=real+(double)other;
	temp.image=image;
	return temp;
}


Complex Complex::operator-(Complex &other)
{

	Complex temp;
	temp.real=real-other.real;
	temp.image=image-other.image;
	return temp;
}

Complex Complex::operator -(const double &other)
{

	Complex temp;
	temp.real=real-(double)other;
	temp.image=image;
	return temp;
}

Complex Complex::operator -(const int &other)
{

	Complex temp;
	temp.real=real-(double)other;
	temp.image=image;
	return temp;
}
Complex Complex::operator*(Complex &other)
{
	Complex temp;
	temp.real=(real*other.real-image*other.image);
	temp.image=(image*other.real+real*other.image);
	return temp;


}

Complex Complex::operator *(const double &other)
{
	Complex temp;
	temp.real=real*other;
	temp.image=image*other;
	return temp;
}

Complex Complex::operator *(const int &other)
{
	Complex temp;
	temp.real=real*(double)other;
	temp.image=image*(double)other;
	return temp;
}

Complex Complex::operator/(Complex &other)
{

	Complex temp;
	temp.real=((real*other.real)+(image*other.image))/(other.real*other.real+other.image*other.image);
	temp.image=((image*other.real)-(real*other.image))/(other.real*other.real+other.image*other.image);
	return temp;

}

Complex Complex::operator /(const double &other)
{
	Complex temp;
	temp.real=real/other;
	temp.image=image/other;
	return temp;

}

Complex Complex::operator /(const int &other)
{
	Complex temp;
	temp.real=real/(double)other;
	temp.image=image/(double)other;
	return temp;
}




void Complex::operator+=(Complex &other)
{
	this->real+=other.real;
	this->image+=other.image;
}

void Complex::operator +=(const double &other)
{

	this->real+=other;
}

void Complex::operator +=(const int&other)
{
	this->real+=(double)other;
}





void Complex::operator-=(Complex &other)
{
	this->real-=other.real;
	this->image-=other.image;
}

void Complex::operator -=(const double &other)
{

	this->real-=other;
}

void Complex::operator -=(const int &other)
{
	this->real-=(double)other;
}



void Complex::operator*=(Complex &other)
{
	this->real=(real*other.real-image*other.image);
	this->image=(image*other.real+real*other.image);;
}

void Complex::operator *=(const double &other)
{

	this->real=real*other;
	this->image=image*other;
}

void Complex::operator *=(const int &other)
{
	this->real=real*(double)other;
	this->image=image*(double)other;
}


void Complex::operator/=(Complex &other)
{
	this->real=((real*other.real)+(image*other.image))/(other.real*other.real+other.image*other.image);
	this->image=((image*other.real)-(real*other.image))/(other.real*other.real+other.image*other.image);
}

void Complex::operator /=(const double &other)
{

	this->real=real/other;
	this->image=image/other;
}

void Complex::operator /=(const int &other)
{
	this->real=real/(double)other;
	this->image=image/(double)other;
}

Complex Complex::operator= (Complex &other)
{

	this->real=other.real;
	this->image=other.image;
	return *this;

}
Complex Complex::operator =(const double &other)
{
	this->real=other;
	this->image=image;
	return *this;


}
Complex Complex::operator =(const int &other)
{
	this->real=(double)other;
	this->image=image;
	return *this;
}


bool Complex::operator ==(Complex &other)
{

	if(this->real=other.real&&this->image==other.image)
		return true;
	else return false;
}
bool Complex::operator ==(const double &other)
{

	if(this->real==other&&this->image==0)
		return true;
	else 
		return false;
}
bool Complex::operator ==(const int &other)
{
	if(this->real==(double)other&&this->image==0)
		return true;
	else 
		return false;
}

ostream& operator<<(ostream &os,Complex &other)
{
	other.show();
	return cout;
}

istream& operator>>(istream &is,Complex &other)
{
	is>>other.real;
	is>>other.image;
	return cin;
}
/**//**//**//////////////////////////////END_TEMPLATE_CLASS_COMPLEX///////////////////////////////




