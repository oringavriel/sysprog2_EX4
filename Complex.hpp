#ifndef COMPLEX_HPP
#define COMPLEX_HPP
#include <iostream>
using namespace std;
#include <cmath>

namespace ariel
{
    class Complex
    {
    private:
        double real;
        double imag;

    public:
        Complex(double real = 0.0, double imag = 0.0) : real(real), imag(imag) {}
        double getReal() const { return this->real; }
        double getImag() const { return this->imag; }

        Complex operator+(const Complex &other) const
        {
            return Complex(this->real + other.getReal(), this->imag + other.getImag());
        }

        bool operator==(const Complex &other) const
        {
            return ((this->real == other.getReal()) && (this->imag == other.getImag()));
        }

        bool operator!=(const Complex &other) const
        {
            return !(*this == other);
        }

        bool operator>(const Complex &other) const
        {
            if (*this == other)
            {
                return false;
            }
            else
            {
                return (sqrt((this->real * this->real) + (this->imag * this->imag)) >
                        sqrt((other.getReal() * other.getReal()) + (other.getImag() * other.getImag())));
            }
        }

        friend ostream &operator<<(ostream &out, const Complex &c)
        {
            out << c.real << " + " << c.imag << "i";
            return out;
        }
    };
};
#endif