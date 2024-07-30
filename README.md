# Polynomial Project
# Polynomial Class


## Overview
This project defines and implements a Polynomial class in C++ that provides various functionalities for polynomial arithmetic, including addition, subtraction, multiplication, division, evaluation, derivation, and integration. The class supports polynomials of any degree with floating-point coefficients.


## Features

### Construction and Destruction:
- Constructors to create polynomials with specified degrees and coefficients.
- Copy constructor and destructor to manage dynamic memory.

### Arithmetic Operations:
- Addition, subtraction, and multiplication of polynomials.
- Division of polynomials (both quotient and remainder).
- Derivation and integration of polynomials.

### Utility Functions:
- Evaluation of polynomials at a given value.
- Conversion of polynomial to a string representation.
- Reading and writing polynomials to and from streams.
- Comparison of polynomials for equality.


## Class Definition

### Constructors
- Polynomial(size_t degree): Creates a polynomial of the specified degree with all coefficients initialized to 0.0.
- Polynomial(size_t degree, const float coefficients): *Creates a polynomial of the specified degree with the given coefficients.
- Polynomial(const Polynomial& other):Copy constructor.
- Destructor ~Polynomial(): Destroys the polynomial and frees allocated memory.

### Arithmetic Methods
- const Polynomial Sum(const Polynomial& rhs) const: Returns the sum of the current polynomial and rhs.
- const Polynomial Subtract(const Polynomial& rhs) const: Returns the difference between the current polynomial and rhs.
- const Polynomial Minus() const: Returns the additive inverse of the current polynomial.
- const Polynomial Multiply(const Polynomial& rhs) const: Returns the product of the current polynomial and rhs.
- const Polynomial Divide(const Polynomial& rhs) const: Returns the quotient of the current polynomial divided by rhs (remainder is lost).
- const Polynomial Divide(const Polynomial& rhs, Polynomial& remainder) const: Returns the quotient and sets the remainder when dividing the current polynomial by rhs.
- const Polynomial Derive() const: Returns the derivative of the current polynomial.

### Evaluation Methods
- float Evaluate(float x) const: Evaluates the polynomial at the specified value x.
- float Integrate(float start, float end) const: Returns the value of the definite integral of the polynomial from start to end.

### Utility Methods
- const Polynomial& operator=(const Polynomial& rhs): Copy assignment operator.
- std::string ToString() const: Returns a string representation of the polynomial.
- bool Equals(const Polynomial& rhs) const: Returns true if the current polynomial is equal to rhs.
- std::ostream& Write(std::ostream& output) const: Writes the polynomial to an output stream.
- std::istream& Read(std::istream& input): Reads the polynomial from an input stream.

### Usage Example
An example main function is provided to test various functionalities of the Polynomial class. It includes tests for constructors, arithmetic operations, evaluation, and utility methods.

#### Example Test Cases
The example main function tests:
- Constructors and assignment operators.
- Reading from and writing to streams.
- Addition, subtraction, multiplication, and division of polynomials.
- Derivation and evaluation of polynomials.
- Integration and equality comparison.

### Compilation
To compile the code, use the following command:
g++ -o polynomial polynomial.cpp
