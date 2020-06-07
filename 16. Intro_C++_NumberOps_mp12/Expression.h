#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include "Number.h"
#include "RealNumber.h"
#include "ImaginaryNumber.h"
#include "ComplexNumber.h"
#include <iostream>
#include <vector>
#include <complex>
#include <sstream>
#include <boost/algorithm/string.hpp>

//This class is used for parsing input as read from file and generating output
//Do not modify

class Expression{
	private:
		char my_operator;
		RealNumber real1, real2, real3;
		ImaginaryNumber imaginary1, imaginary2, imaginary3;
		ComplexNumber complex1, complex2, complex3;
		Number* left_Number;
		Number* right_Number;
		Number* result;
	public:
		Expression();
		Expression(string expression_string);
		bool input_expression(string expression_string);
		void evaluate_expression();
		string print_result();
};

#endif