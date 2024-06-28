/*
 * Title:		Polynomial Class
 * Purpose:		Definition of the methods of the Polynomial class
 * Author:		Kristen Lowe
 * Date:		June 24, 2024
 */

#include "polynomial.h"
#include <sstream>
#include <iomanip>
#include <cmath>
using std::stringstream;
using std::showpos;
using std::fixed;
using std::setprecision;


/**
Constructor for class Polynomial.
 Creates a polynomial of degree degree, dynamically allocates an array of size degree + 1 and sets the coefficients to 0.0
 @param degree: the value that the _degree data member will be initialized with
*/
Polynomial::Polynomial(size_t degree) {
    _degree = degree;
    _coefficients = new float[_degree + 1];
    for (size_t i = 0; i < _degree + 1; ++i) {
        _coefficients[i] = 0.0;
    }
}


/**
Constructor
 @param degree: the degree of the new Polynomial object
 @param coefficients: the coefficients that will be copied into the new Polynomial
*/
Polynomial::Polynomial(size_t degree, const float* coefficients) {
    _degree = degree;
    _coefficients = new float [_degree + 1];
    for (size_t i = 0; i < _degree + 1; ++i) {
        _coefficients[i] = coefficients[i];
    }
}

/**
Copy constructor for Polynomial object
 @param other: the object whose data members are being copied for the new object
*/
Polynomial::Polynomial(const Polynomial& other) {
    _degree = other._degree;
    _coefficients = new float[_degree + 1];
    for (size_t i = 0; i < _degree + 1; i++) {
        _coefficients[i] = other._coefficients[i];
    }
}

/**
Destructor for Polynomial object
 delete any memory that was dynamically allocated
*/
Polynomial::~Polynomial() {
    if (_coefficients != nullptr) {
        delete[] _coefficients;
        _coefficients = nullptr;
    }
}

/**
Returns a polynomial that will contain the sum of this with rhs
 @param rhs object to do sum operation with the current object
*/
const Polynomial Polynomial::Sum(const Polynomial& rhs)const {

    //sumCoefficientsSize will be equal to the degree of whichever object array is larger
    size_t sumCoefficientsSize;
    if (this->_degree > rhs._degree) {
        sumCoefficientsSize = this -> _degree;
    }
    else {
        sumCoefficientsSize = rhs._degree;
    }

    //the new array will be filled with summed values
    float* sumCoefficients = new float[sumCoefficientsSize];

    //if one array is shorter than the other, the resulting sum from the dangling indices of the longer array
    //should just be the number from the longer array
    for (size_t i = 0; i < sumCoefficientsSize; i++) {
        if (i > rhs._degree) {
            sumCoefficients[i] = this -> _coefficients[i];
        }
        else if (i > this -> _degree) {
            sumCoefficients[i] = rhs._coefficients[i];
        }
        else {
            sumCoefficients[i] = this->_coefficients[i] + rhs._coefficients[i];
        }
    }
    Polynomial sumValue = Polynomial(sumCoefficientsSize, sumCoefficients);
    delete[] sumCoefficients;
    //return the Polynomial that is being pointed to by dereferencing
    return sumValue;
}

/**
Returns a polynomial that will contain the subtraction of this with rhs
 @param rhs object to do minus operation with the current object
*/
const Polynomial Polynomial::Subtract(const Polynomial& rhs)const {
    //minuendCoefficientsSize will be equal to the degree of whichever object array is larger, + 1
    size_t minuendCoefficientsSize;
    if (this->_degree > rhs._degree) {
        minuendCoefficientsSize = this -> _degree;
    }
    else {
        minuendCoefficientsSize = rhs._degree;
    }
    float* minuendCoefficients = new float[minuendCoefficientsSize];        //array for subtracted values
    //if one array is shorter than the other, the resulting minuend from the dangling indices of the longer array
    //should just be the number from the longer array
    for (size_t i = 0; i < minuendCoefficientsSize; i++) {
        if (i > rhs._degree) {
            minuendCoefficients[i] = this -> _coefficients[i];
        }
        else if (i > this -> _degree) {
            minuendCoefficients[i] = rhs._coefficients[i];
        }
        else {
            minuendCoefficients[i] = this->_coefficients[i] - rhs._coefficients[i];
        }
    }
    Polynomial minuendValue = Polynomial(minuendCoefficientsSize, minuendCoefficients);
    delete[] minuendCoefficients;
    return minuendValue;
}

/**
Returns a polynomial that will contain the additive inverse of this. For instance if the polynomial is
 p=2x^2-2 then p.Minus() would return -2x^2+2
*/
const Polynomial Polynomial::Minus()const {
    //make a new array to fill with the inverse values, and the length stays the same this time
    float* minusCoefficients = new float[_degree];
    for (size_t i = 0; i < _degree + 1; i++) {
        minusCoefficients[i] = _coefficients[i] * -1.0;
    }
    Polynomial minusValue = Polynomial(_degree, minusCoefficients);
    delete[] minusCoefficients;
    return minusValue;
}


/**
Returns a polynomial that will contain the multiplication of this with rhs.
*/
const Polynomial Polynomial::Multiply(const Polynomial& rhs)const {
//sumCoefficientsSize will be equal to the degree of whichever object array is larger, + 1
    size_t productCoefficientsSize = this->_degree + rhs._degree + 1;
    //the new array will be filled with multiplied values
    float* productCoefficients = new float[productCoefficientsSize];

    //multiplication is different from adding or subtracting because each term in polynomials must be multiplied
    // against each of the terms in the other polynomials
    for (size_t i = 0; i < this->_degree + 1; ++i) {
        for (size_t j = 0; j < rhs._degree + 1; ++j) {
            //the index i + j will be the power/degree for the multiplied polynomial term.
            productCoefficients[i + j] += this->_coefficients[i] * rhs._coefficients[j];
        }
    }
    Polynomial productValue = Polynomial(productCoefficientsSize - 1, productCoefficients);
    delete[] productCoefficients;
    return productValue;
}


/**
Returns a polynomial that will contain the division of this with rhs. The remainder is lost if there was one.
 @param rhs: the object whose coefficients will perform the division operation with the current object coefficients
*/
const Polynomial Polynomial::Divide(const Polynomial& rhs)const{
    size_t quotientCoefficientsSize;
    int quotientWithoutRemainder;
    if (this->_degree > rhs._degree) {
        quotientCoefficientsSize = this -> _degree;
    }
    else {
        quotientCoefficientsSize = rhs._degree;
    }
    //the new array will be filled with multiplied values
    float* quotientCoefficients = new float[quotientCoefficientsSize];
    //if one array is shorter than the other, the resulting product from the dangling indices of the longer array
    //should just be the number from the longer array
    for (size_t i = 0; i < quotientCoefficientsSize; i++) {
        if (i > rhs._degree) {
            quotientCoefficients[i] = this -> _coefficients[i];
        }
        else if (i > this -> _degree) {
            quotientCoefficients[i] = rhs._coefficients[i];
        }
        else {
            if (rhs._coefficients[i] == 0) {
                std::cerr << "cannot divide by 0";
            }
            else {
                quotientWithoutRemainder = this->_coefficients[i] / rhs._coefficients[i];
                quotientCoefficients[i] = quotientWithoutRemainder;
            }
        }
    }
    Polynomial quotientValue = Polynomial(quotientCoefficientsSize, quotientCoefficients);
    delete[] quotientCoefficients;
    return quotientValue;
}

/**
Returns a polynomial that will contain the division of this with rhs.
 @param rhs: the object whose coefficients will perform the division operation with the current object coefficients
 @param remainder: The remainder will be placed in parameter by reference remainder.
*/
const Polynomial Polynomial::Divide(const Polynomial& rhs, Polynomial& remainder)const{
    remainder = Polynomial(0);
    return Polynomial(0);
}

/**
Returns a polynomial that will contain the derivative of this.
*/
const Polynomial Polynomial::Derive()const {
    if (_degree == 0) {
        // If the polynomial is raised to no power, the derivative is just the coefficient value
        //the polynomial created will just be the coefficient with no degree parameter
        return Polynomial(0);
    }
    if (_degree > 0) {
        //make a new array to fill with the derived values, the length stays the same
        float* derivedCoefficients = new float[_degree];
        for (size_t i = 1; i < _degree; ++i) {
            //example of how the math works
            // * a = -2.50x^3 +0.00x^2 +2.00x^1 -1.00
            //derivedCoefficients[0] = (_coefficients[2] * 1);
            derivedCoefficients[i - 1] = _coefficients[i] * i;
        }
        Polynomial derivedValue = Polynomial(_degree - 1, derivedCoefficients);
        delete[] derivedCoefficients;
        return derivedValue;
    }
}


/**
Returns the value of evaluating the polynomial with value x
 @param x the value to be plugged into the polynomial
*/
float Polynomial::Evaluate(float x)const {
//every coefficient in the polynomial will be raised to one power less from left to right
//the rightmost/final coefficient is not raised to a power
//the coefficient is multiplied by x, which is raised to the power
    float evaluatedTotal = 0.0;
    for (int i = _degree; i >= 0; i--) {
        evaluatedTotal += _coefficients[i] * pow(x, i);
    }
}

/**
Returns the value of the definite integral evaluated from a to b.
 @param
*/
float Polynomial::Integrate(float start, float end)const{
    return 0.0;
}

/**
Copy assignment operator, assigns the polynomial rhs to this
 @param rhs: the object which will be assigned to this
*/
const Polynomial& Polynomial::operator=(const Polynomial& rhs) {
    _degree = rhs._degree;
    delete[] _coefficients;
    _coefficients = new float [_degree + 1];
    for (size_t i = 0; i < _degree; i++) {
        _coefficients[i] = rhs._coefficients[i];
    }
}


string Polynomial::ToString()const{
    stringstream ss;
    for (size_t i = _degree; i > 0; i--) {
        ss << showpos << fixed << setprecision(2) << _coefficients[i] << "x^" << i << " ";
    }
    ss << showpos << fixed << setprecision(2) << _coefficients[0];
    return ss.str();
}

/**
Returns true if this is equal to rhs.
 @param rhs the object which will be compared against the current object
*/
bool Polynomial::Equals(const Polynomial& rhs)const {
    if (this->_degree != rhs._degree) {
        return false;
    }
    for (size_t i = 0; i < _degree; i++) {
        if (this->_coefficients[i] != rhs._coefficients[i]) {
            return false;
        }
    }
    return true;
}
//if (this != &_degree) {
//return false;
//}
//return true;

ostream& Polynomial::Write(ostream& output)const{
    output << _degree << " ";
    for (size_t i = 0; i < _degree + 1; i++) {
        output << _coefficients[i] << " ";
    }
    return output;
}

istream& Polynomial::Read(istream& input){
    size_t degree;
    input >> degree;
    if (input.fail()){
        return input;
    }
    float* coefficients = new float[degree + 1];
    for (size_t i = 0; i < degree + 1; i++) {
        input >> coefficients[i];
        if (input.fail()){
            delete[] coefficients;
            return input;
        }
    }

    if (degree != _degree){
        if (_coefficients){
            delete[] _coefficients;
        }
        _degree = degree;
        _coefficients = coefficients;
    }else{
        for (size_t i = 0; i < _degree + 1; i++) {
            _coefficients[i] = coefficients[i];
        }
        delete[] coefficients;
    }
    return input;
}


