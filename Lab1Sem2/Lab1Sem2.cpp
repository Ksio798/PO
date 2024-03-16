#include <iostream>

class Complex {
	double real, im;

public:
	void setReal(double num) {
		real = num;
	}
	double getReal() {
		return real;
	}
	void setIm(double num) {
		im = num;
	}
	double getIm() {
		return im;
	}

	Complex operator + (const Complex& c) const
	{
		Complex temp;

		temp.real = real + c.real;
		temp.im = im + c.im;

		return temp;
	}
	Complex operator - (const Complex& c) const
	{
		Complex temp;

		temp.real = real - c.real;
		temp.im = im - c.im;

		return temp;
	}

	Complex operator * (const Complex& c) const
	{
		Complex temp;

		temp.real = real * c.real - im * c.im;
		temp.im = real * c.im + im * c.real;

		return temp;
	}

	Complex operator / (const Complex& c) const
	{
		Complex temp;

		temp.real = (real * c.real + im * c.im) / (c.real * c.real + c.im * c.im);
		temp.im = (im * c.real - real * c.im) / (c.real * c.real + c.im * c.im);

		return temp;
	}

	bool operator == (const Complex& c) const { return real == c.real && im == c.im; }

	bool operator!=(const Complex& c) const { return !(*this == c); }

	bool operator==(int num) const { return (real == static_cast<double>(num) && im == 0); }

	bool operator!=(int num) const { return !(*this == num); }

	bool operator==(float num) const { return (real == static_cast<double>(num) && im == 0); }

	bool operator!=(float num) const { return !(*this == num); }

	double abs() const {
		return std::sqrt(real * real + im * im);
	}

	Complex Power(int n) const {
		Complex c;
		c.real = std::pow(abs(), n) * std::cos(n * std::atan2(im, real));
		c.im = std::pow(abs(), n) * std::sin(n * std::atan2(im, real));
		return c;
	}

	friend std::ostream& operator<<(std::ostream&, const Complex&);
};

std::ostream& operator << (std::ostream& out, const Complex& c)
{
	out << c.real;
	if (c.im > 0)
		out << "+";
	out << c.im << "i" << "\n";

	return out;
}

int main()
{
	Complex v1;
	Complex v2;
	v1.setReal(3);
	v1.setIm(4);
	v2.setReal(1);
	v2.setIm(2);
	//Вывод значений
	std::cout << v1;
	std::cout << v2;
	//тест арифметических операций
	std::cout << v1 + v2;
	std::cout << v1 - v2;
	std::cout << v1 * v2;
	std::cout << v1 / v2;
	//тест сравнения с комплексными, целыми и дробными числами 
	std::cout << (v1 == v2) << "\n";
	std::cout << (v1 != v2) << "\n";
	std::cout << (v1 == 3) << "\n";
	std::cout << (v1 == 2.5f) << "\n";
	//тест получения модуля и возведения в степень
	std::cout << v1.abs() << "\n";
	std::cout << v1.Power(2) << "\n";

}