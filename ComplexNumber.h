#pragma once

#include <iostream>
#include <math.h>

class ComplexNumber
{
public:

    double real;
    double imaginary;

    ComplexNumber(double in_real = 0.0, double in_imaginary = 0.0)
    {
        real = in_real;
        imaginary = in_imaginary;
    }

    double magnitude()
    {
        return std::sqrt(real * real + imaginary * imaginary);
    }

    void print()
    {
        std::cout << real << " + " << imaginary << "i" << std::endl;
    }
};

ComplexNumber exp(ComplexNumber number)
{
    ComplexNumber out_number;

    double real_part = std::exp(number.real);

    out_number.real = real_part * std::cos(number.imaginary);
    out_number.imaginary = real_part * std::sin(number.imaginary);

    return out_number;
}

ComplexNumber operator+(ComplexNumber number1, ComplexNumber number2)
{
    ComplexNumber out_number;

    out_number.real = number1.real + number2.real;
    out_number.imaginary = number1.imaginary + number2.imaginary;

    return out_number;
}

ComplexNumber operator+(ComplexNumber number1, double number2)
{
    ComplexNumber out_number;

    out_number.real = number1.real + number2;
    out_number.imaginary = number1.imaginary;

    return out_number;
}

ComplexNumber operator+(double number1, ComplexNumber number2)
{
    ComplexNumber out_number;

    out_number.real = number1 + number2.real;
    out_number.imaginary = number2.imaginary;

    return out_number;
}

ComplexNumber operator-(ComplexNumber number1, ComplexNumber number2)
{
    ComplexNumber out_number;

    out_number.real = number1.real - number2.real;
    out_number.imaginary = number1.imaginary - number2.imaginary;

    return out_number;
}

ComplexNumber operator-(ComplexNumber number1, double number2)
{
    ComplexNumber out_number;

    out_number.real = number1.real - number2;
    out_number.imaginary = number1.imaginary;

    return out_number;
}

ComplexNumber operator-(double number1, ComplexNumber number2)
{
    ComplexNumber out_number;

    out_number.real = number1 - number2.real;
    out_number.imaginary = - number2.imaginary;

    return out_number;
}

ComplexNumber operator*(ComplexNumber number1, ComplexNumber number2)
{
    ComplexNumber out_number;

    out_number.real = number1.real * number2.real - number1.imaginary * number2.imaginary;
    out_number.imaginary = number1.real * number2.imaginary + number1.imaginary * number2.real;

    return out_number;
}

ComplexNumber operator*(ComplexNumber number1, double number2)
{
    ComplexNumber out_number;

    out_number.real = number1.real * number2;
    out_number.imaginary = number1.imaginary * number2;

    return out_number;
}

ComplexNumber operator*(double number1, ComplexNumber number2)
{
    ComplexNumber out_number;

    out_number.real = number1 * number2.real;
    out_number.imaginary = number1 * number2.imaginary;

    return out_number;
}

ComplexNumber operator/(ComplexNumber number1, ComplexNumber number2)
{
    ComplexNumber out_number;

    double denominator = number2.real * number2.real + number2.imaginary * number2.imaginary; 

    out_number.real = (number1.real * number2.real + number1.imaginary * number2.imaginary) / denominator;
    out_number.imaginary = (number1.imaginary * number2.real - number1.real * number2.imaginary) / denominator;

    return out_number;
}

ComplexNumber operator/(ComplexNumber number1, double number2)
{
    ComplexNumber out_number;

    out_number.real = number1.real / number2;
    out_number.imaginary = number1.imaginary / number2;

    return out_number;
}

ComplexNumber operator/(double number1, ComplexNumber number2)
{
    ComplexNumber out_number;

    double denominator = number2.real * number2.real + number2.imaginary * number2.imaginary; 

    out_number.real = (number1 * number2.real) / denominator;
    out_number.imaginary = -(number1 * number2.imaginary) / denominator;

    return out_number;
}

ComplexNumber& operator+=(ComplexNumber& number1, ComplexNumber number2)
{
    number1.real = number1.real + number2.real;
    number1.imaginary = number1.imaginary + number2.imaginary;

    return number1;
}

ComplexNumber& operator+=(ComplexNumber& number1, double number2)
{
    number1.real = number1.real + number2;
    number1.imaginary = number1.imaginary;

    return number1;
}

/*ComplexNumber& operator+=(double& number1, ComplexNumber number2)
{
    number1.real = number1 + number2.real;
    number1.imaginary = number2.imaginary;

    return number1;
}*/

ComplexNumber& operator-=(ComplexNumber& number1, ComplexNumber number2)
{
    number1.real = number1.real - number2.real;
    number1.imaginary = number1.imaginary - number2.imaginary;

    return number1;
}

ComplexNumber& operator-=(ComplexNumber& number1, double number2)
{
    number1.real = number1.real - number2;
    number1.imaginary = number1.imaginary;

    return number1;
}

/*ComplexNumber& operator-=(double& number1, ComplexNumber number2)
{
    number1.real = number1 - number2.real;
    number1.imaginary = - number2.imaginary;

    return number1;
}*/

ComplexNumber& operator*=(ComplexNumber& number1, ComplexNumber number2)
{
    double real_temp = number1.real;

    number1.real = real_temp * number2.real - number1.imaginary * number2.imaginary;
    number1.imaginary = real_temp * number2.imaginary + number1.imaginary * number2.real;

    return number1;
}

ComplexNumber& operator*=(ComplexNumber& number1, double number2)
{
    number1.real = number1.real * number2;
    number1.imaginary = number1.imaginary * number2;

    return number1;
}

/*ComplexNumber& operator*=(double& number1, ComplexNumber number2)
{
    number1.real = number1 * number2.real;
    number1.imaginary = number1 * number2.imaginary;

    return number1;
}*/

ComplexNumber& operator/=(ComplexNumber& number1, ComplexNumber number2)
{
    double real_temp = number1.real;

    double denominator = number2.real * number2.real + number2.imaginary * number2.imaginary; 

    number1.real = (real_temp * number2.real + number1.imaginary * number2.imaginary) / denominator;
    number1.imaginary = (number1.imaginary * number2.real - real_temp * number2.imaginary) / denominator;

    return number1;
}

ComplexNumber& operator/=(ComplexNumber& number1, double number2)
{
    number1.real = number1.real / number2;
    number1.imaginary = number1.imaginary / number2;

    return number1;
}

/*ComplexNumber& operator/=(double& number1, ComplexNumber number2)
{
    double denominator = number2.real * number2.real + number2.imaginary * number2.imaginary; 

    number1.real = (number1 * number2.real) / denominator;
    number1.imaginary = -(number1 * number2.imaginary) / denominator;

    return number1;
}*/