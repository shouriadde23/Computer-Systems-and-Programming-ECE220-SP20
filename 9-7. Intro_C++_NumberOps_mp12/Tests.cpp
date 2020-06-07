#include <stdlib.h>
#include <complex>
#include <iostream>
#include <fstream>
#include "RealNumber.h"
#include "ImaginaryNumber.h"
#include "ComplexNumber.h"
#include "helper.h"

// Generates a double from -10000 to 9999, except 0
double get_random_double() {
	double num = (double)(rand() % 20000 - 10000);
    return  num == 0.0 ? num + 1 : num;
}

bool equals (ComplexNumber &result, std::complex<double> &std_result) {
	return (std::abs(result.get_real_component() - std_result.real()) < 0.001) && (std::abs(result.get_imaginary_component() - std_result.imag() < 0.001));
}

bool verify_real(RealNumber num, double rval){
	bool verify_component = num.get_real_component() == rval;
	bool verify_phase = (rval == 0.0 ? num.get_phase() == 0.0 : num.get_phase() == calculate_phase(rval, 0.0));
	bool verify_magnitude = (rval == 0.0 ? num.get_magnitude() == 0.0 : num.get_magnitude() == abs(rval));
	return verify_component && verify_phase && verify_magnitude;
}

bool verify_imaginary(ImaginaryNumber num, double rval){
	bool verify_component = num.get_imaginary_component() == rval;
	bool verify_phase = (rval == 0.0 ? num.get_phase() == 0.0 : num.get_phase() == calculate_phase(0.0, rval));
	bool verify_magnitude = (rval == 0.0 ? num.get_magnitude() == 0.0 : num.get_magnitude() == abs(rval));
	return verify_component && verify_phase && verify_magnitude;
}

bool verify_complex(ComplexNumber num, double rval1, double rval2){
	bool verify_component = (num.get_real_component() == rval1) && (num.get_imaginary_component() == rval2);
	bool verify_phase = num.get_phase() == calculate_phase(rval1, rval2);
	bool verify_magnitude = num.get_magnitude() == sqrt(rval1 * rval1 + rval2 * rval2);
	return verify_component && verify_phase && verify_magnitude;
}

int test_real_constructor(double rval, ofstream& grade_report){
	RealNumber empty = RealNumber();
	RealNumber num = RealNumber(rval);
	RealNumber copy = num;
	if (verify_real(empty, 0.0) && verify_real(num, rval) && verify_real(copy, rval)) {
		grade_report << "+4pts\n";
		return 4;
	}
	else {
		grade_report << "+0pts\n";
		return 0;
	}
	return 0;
}

int test_imaginary_constructor(double rval, ofstream& grade_report){
	ImaginaryNumber empty = ImaginaryNumber();
	ImaginaryNumber num = ImaginaryNumber(rval);
	ImaginaryNumber copy = num;
	if (verify_imaginary(empty, 0.0) && verify_imaginary(num, rval) && verify_imaginary(copy, rval)) {
		grade_report << "+5pts\n";
		return 5;
	}
	else {
		grade_report << "+0pts\n";
		return 0;
	}
	return 0;
}

int test_complex_constructor(double rval1, double rval2, ofstream& grade_report){
	ComplexNumber empty = ComplexNumber();
	ComplexNumber num = ComplexNumber(rval1, rval2);
	ComplexNumber copy = num;
	if (verify_complex(empty, 0.0, 0.0) && verify_complex(num, rval1, rval2) && verify_complex(copy, rval1, rval2)) {
		grade_report << "+5pts\n";
		return 5;
	}
	else {
		grade_report << "+0pts\n";
		return 0;
	}
	return 0;
}

int test_real_getter_setter(double rval, ofstream& grade_report){
	RealNumber num;
	num.set_real_component(rval);
	if (verify_real(num, rval)) {
		grade_report << "+4pts\n";
		return 4;
	}
	else {
		grade_report << "+0pts\n";
		return 0;
	}
	return 0;
}

int test_imaginary_getter_setter(double rval, ofstream& grade_report){
	ImaginaryNumber num;
	num.set_imaginary_component(rval);
	if (verify_imaginary(num, rval)) {
		grade_report << "+5pts\n";
		return 5;
	}
	else {
		grade_report << "+0pts\n";
		return 0;
	}
	return 0;
}

int test_complex_getter_setter(double rval1, double rval2, ofstream& grade_report){
	ComplexNumber num;
	num.set_real_component(rval1);
	num.set_imaginary_component(rval2);
	if (verify_complex(num, rval1, rval2)) {
		grade_report << "+5pts\n";
		return 5;
	}
	else {
		grade_report << "+0pts\n";
		return 0;
	}
	return 0;
}

int test_real_real_calculation(double lval, double rval, ofstream& grade_report) {
	int total = 0;
	RealNumber add_result = RealNumber(lval) + RealNumber(rval);
	std::complex<double> std_add_result = std::complex<double>(lval, 0) + std::complex<double>(rval, 0);
	bool verify_addition = add_result.get_real_component() == std_add_result.real();
	if (!verify_addition) 
		grade_report << "\nTest 7: Error in + operator";
	else
		total += 2;

	RealNumber subtract_result = RealNumber(lval) - RealNumber(rval);
	std::complex<double> std_subtract_result = std::complex<double>(lval, 0) - std::complex<double>(rval, 0);
	bool verify_subtraction = subtract_result.get_real_component() == std_subtract_result.real();
	if (!verify_subtraction)
		grade_report << "\nTest 7: Error in - operator";
	else
		total += 2;

	RealNumber multiply_result = RealNumber(lval) * RealNumber(rval);
	std::complex<double> std_multiply_result = std::complex<double>(lval, 0) * std::complex<double>(rval, 0);
	bool verify_multiplication = multiply_result.get_real_component() == std_multiply_result.real();
	if (!verify_multiplication)
		grade_report << "\nTest 7: Error in * operator";
	else
		total += 2;

	RealNumber divide_result = RealNumber(lval) / RealNumber(rval);
	std::complex<double> std_divide_result = std::complex<double>(lval, 0) / std::complex<double>(rval, 0);
	bool verify_division = divide_result.get_real_component() == std_divide_result.real();
	if (!verify_division) 
		grade_report << "\nTest 7: Error in / operator";
	else
		total += 2;

	return total;
}

int test_real_imaginary_calculation(double lval, double rval, ofstream& grade_report) {
	int total = 0;
	ComplexNumber add_result = RealNumber(lval) + ImaginaryNumber(rval);
	std::complex<double> std_add_result = std::complex<double>(lval, 0) + std::complex<double>(0, rval);
	bool verify_addition = equals(add_result, std_add_result);
	if (!verify_addition) 
		grade_report << "\nTest 8: Error in + operator";
	else
		total += 2;

	ComplexNumber subtract_result = RealNumber(lval) - ImaginaryNumber(rval);
	std::complex<double> std_subtract_result = std::complex<double>(lval, 0) - std::complex<double>(0, rval);
	bool verify_subtraction = equals(subtract_result, std_subtract_result);
	if (!verify_subtraction)
		grade_report << "\nTest 8: Error in - operator";
	else
		total += 2;

	ImaginaryNumber multiply_result = RealNumber(lval) * ImaginaryNumber(rval);
	std::complex<double> std_multiply_result = std::complex<double>(lval, 0) * std::complex<double>(0, rval);
	bool verify_multiplication = multiply_result.get_imaginary_component() == std_multiply_result.imag();
	if (!verify_multiplication)
		grade_report << "\nTest 8: Error in * operator";
	else
		total += 2;

	ImaginaryNumber divide_result = RealNumber(lval) / ImaginaryNumber(rval);
	std::complex<double> std_divide_result = std::complex<double>(lval, 0) / std::complex<double>(0, rval);
	bool verify_division = divide_result.get_imaginary_component() == std_divide_result.imag();
	if (!verify_division) 
		grade_report << "\nTest 8: Error in / operator";
	else
		total += 2;

	return total;
}

int test_real_complex_calculation(double lval, double rval1, double rval2, ofstream& grade_report) {
	int total = 0;
	ComplexNumber add_result = RealNumber(lval) + ComplexNumber(rval1, rval2);
	std::complex<double> std_add_result = std::complex<double>(lval, 0) + std::complex<double>(rval1, rval2);
	bool verify_addition = equals(add_result, std_add_result);
	if (!verify_addition) 
		grade_report << "\nTest 9: Error in + operator";
	else
		total += 2;

	ComplexNumber subtract_result = RealNumber(lval) - ComplexNumber(rval1, rval2);
	std::complex<double> std_subtract_result = std::complex<double>(lval, 0) - std::complex<double>(rval1, rval2);
	bool verify_subtraction = equals(subtract_result, std_subtract_result);
	if (!verify_subtraction)
		grade_report << "\nTest 9: Error in - operator";
	else
		total += 2;

	ComplexNumber multiply_result = RealNumber(lval) * ComplexNumber(rval1, rval2);
	std::complex<double> std_multiply_result = std::complex<double>(lval, 0) * std::complex<double>(rval1, rval2);
	bool verify_multiplication = equals(multiply_result, std_multiply_result);
	if (!verify_multiplication)
		grade_report << "\nTest 9: Error in * operator";
	else
		total += 2;

	ComplexNumber divide_result = RealNumber(lval) / ComplexNumber(rval1, rval2);
	std::complex<double> std_divide_result = std::complex<double>(lval, 0) / std::complex<double>(rval1, rval2);
	bool verify_division = equals(divide_result, std_divide_result);
	if (!verify_division) 
		grade_report << "\nTest 9: Error in / operator";
	else
		total += 2;

	return total;
}

int test_imaginary_real_calculation(double lval, double rval, ofstream& grade_report) {
	int total = 0;
	ComplexNumber add_result = ImaginaryNumber(lval) + RealNumber(rval);
	std::complex<double> std_add_result = std::complex<double>(0, lval) + std::complex<double>(rval, 0);
	bool verify_addition = equals(add_result, std_add_result);
	if (!verify_addition) 
		grade_report << "\nTest 10: Error in + operator";
	else
		total += 2;

	ComplexNumber subtract_result = ImaginaryNumber(lval) - RealNumber(rval);
	std::complex<double> std_subtract_result = std::complex<double>(0, lval) - std::complex<double>(rval, 0);
	bool verify_subtraction = equals(subtract_result, std_subtract_result);
	if (!verify_subtraction)
		grade_report << "\nTest 10: Error in - operator";
	else
		total += 2;

	ImaginaryNumber multiply_result = ImaginaryNumber(lval) * RealNumber(rval);
	std::complex<double> std_multiply_result = std::complex<double>(0, lval) * std::complex<double>(rval, 0);
	bool verify_multiplication = multiply_result.get_imaginary_component() == std_multiply_result.imag();
	if (!verify_multiplication)
		grade_report << "\nTest 10: Error in * operator";
	else
		total += 2;

	ImaginaryNumber divide_result = ImaginaryNumber(lval) / RealNumber(rval);
	std::complex<double> std_divide_result = std::complex<double>(0, lval) / std::complex<double>(rval, 0);
	bool verify_division = divide_result.get_imaginary_component() == std_divide_result.imag();
	if (!verify_division) 
		grade_report << "\nTest 10: Error in / operator";
	else
		total += 2;

	return total;
}

int test_imaginary_imaginary_calculation(double lval, double rval, ofstream& grade_report) {
	int total = 0;
	ImaginaryNumber add_result = ImaginaryNumber(lval) + ImaginaryNumber(rval);
	std::complex<double> std_add_result = std::complex<double>(0, lval) + std::complex<double>(0, rval);
	bool verify_addition = add_result.get_imaginary_component() == std_add_result.imag();
	if (!verify_addition) 
		grade_report << "\nTest 11: Error in + operator";
	else
		total += 2;

	ImaginaryNumber subtract_result = ImaginaryNumber(lval) - ImaginaryNumber(rval);
	std::complex<double> std_subtract_result = std::complex<double>(0, lval) - std::complex<double>(0, rval);
	bool verify_subtraction = subtract_result.get_imaginary_component() == std_subtract_result.imag();
	if (!verify_subtraction)
		grade_report << "\nTest 11: Error in - operator";
	else
		total += 2;

	RealNumber multiply_result = ImaginaryNumber(lval) * ImaginaryNumber(rval);
	std::complex<double> std_multiply_result = std::complex<double>(0, lval) * std::complex<double>(0, rval);
	bool verify_multiplication = multiply_result.get_real_component() == std_multiply_result.real();
	if (!verify_multiplication)
		grade_report << "\nTest 11: Error in * operator";
	else
		total += 2;

	RealNumber divide_result = ImaginaryNumber(lval) / ImaginaryNumber(rval);
	std::complex<double> std_divide_result = std::complex<double>(0, lval) / std::complex<double>(0, rval);
	bool verify_division = divide_result.get_real_component() == std_divide_result.real();
	if (!verify_division) 
		grade_report << "\nTest 11: Error in / operator";
	else
		total += 2;

	return total;
}

int test_imaginary_complex_calculation(double lval, double rval1, double rval2, ofstream& grade_report) {
	int total = 0;
	ComplexNumber add_result = ImaginaryNumber(lval) + ComplexNumber(rval1, rval2);
	std::complex<double> std_add_result = std::complex<double>(0, lval) + std::complex<double>(rval1, rval2);
	bool verify_addition = equals(add_result, std_add_result);
	if (!verify_addition) 
		grade_report << "\nTest 12: Error in + operator";
	else
		total += 2;

	ComplexNumber subtract_result = ImaginaryNumber(lval) - ComplexNumber(rval1, rval2);
	std::complex<double> std_subtract_result = std::complex<double>(0, lval) - std::complex<double>(rval1, rval2);
	bool verify_subtraction = equals(subtract_result, std_subtract_result);
	if (!verify_subtraction)
		grade_report << "\nTest 12: Error in - operator";
	else
		total += 2;

	ComplexNumber multiply_result = ImaginaryNumber(lval) * ComplexNumber(rval1, rval2);
	std::complex<double> std_multiply_result = std::complex<double>(0, lval) * std::complex<double>(rval1, rval2);
	bool verify_multiplication = equals(multiply_result, std_multiply_result);
	if (!verify_multiplication)
		grade_report << "\nTest 12: Error in * operator";
	else
		total += 2;

	ComplexNumber divide_result = ImaginaryNumber(lval) / ComplexNumber(rval1, rval2);
	std::complex<double> std_divide_result = std::complex<double>(0, lval) / std::complex<double>(rval1, rval2);
	bool verify_division = equals(divide_result, std_divide_result);
	if (!verify_division) 
		grade_report << "\nTest 12: Error in / operator";
	else
		total += 2;

	return total;
}

int test_complex_real_calculation(double lval1, double lval2, double rval, ofstream& grade_report) {
	int total = 0;
	ComplexNumber add_result = ComplexNumber(lval1, lval2) + RealNumber(rval);
	std::complex<double> std_add_result = std::complex<double>(lval1, lval2) + std::complex<double>(rval, 0);
	bool verify_addition = equals(add_result, std_add_result);
	if (!verify_addition) 
		grade_report << "\nTest 13: Error in + operator";
	else
		total += 2;

	ComplexNumber subtract_result = ComplexNumber(lval1, lval2) - RealNumber(rval);
	std::complex<double> std_subtract_result = std::complex<double>(lval1, lval2) - std::complex<double>(rval, 0);
	bool verify_subtraction = equals(subtract_result, std_subtract_result);
	if (!verify_subtraction)
		grade_report << "\nTest 13: Error in - operator";
	else
		total += 2;

	ComplexNumber multiply_result = ComplexNumber(lval1, lval2) * RealNumber(rval);
	std::complex<double> std_multiply_result = std::complex<double>(lval1, lval2) * std::complex<double>(rval, 0);
	bool verify_multiplication = equals(multiply_result, std_multiply_result);
	if (!verify_multiplication)
		grade_report << "\nTest 13: Error in * operator";
	else
		total += 2;

	ComplexNumber divide_result = ComplexNumber(lval1, lval2) / RealNumber(rval);
	std::complex<double> std_divide_result = std::complex<double>(lval1, lval2) / std::complex<double>(rval, 0);
	bool verify_division = equals(divide_result, std_divide_result);
	if (!verify_division) 
		grade_report << "\nTest 13: Error in / operator";
	else
		total += 2;

	return total;
}

int test_complex_imaginary_calculation(double lval1, double lval2, double rval, ofstream& grade_report) {
	int total = 0;
	ComplexNumber add_result = ComplexNumber(lval1, lval2) + ImaginaryNumber(rval);
	std::complex<double> std_add_result = std::complex<double>(lval1, lval2) + std::complex<double>(0, rval);
	bool verify_addition = equals(add_result, std_add_result);
	if (!verify_addition) 
		grade_report << "\nTest14 : Error in + operator";
	else
		total += 2;

	ComplexNumber subtract_result = ComplexNumber(lval1, lval2) - ImaginaryNumber(rval);
	std::complex<double> std_subtract_result = std::complex<double>(lval1, lval2) - std::complex<double>(0, rval);
	bool verify_subtraction = equals(subtract_result, std_subtract_result);
	if (!verify_subtraction)
		grade_report << "\nTest14 : Error in - operator";
	else
		total += 2;

	ComplexNumber multiply_result = ComplexNumber(lval1, lval2) * ImaginaryNumber(rval);
	std::complex<double> std_multiply_result = std::complex<double>(lval1, lval2) * std::complex<double>(0, rval);
	bool verify_multiplication = equals(multiply_result, std_multiply_result);
	if (!verify_multiplication)
		grade_report << "\nTest14 : Error in * operator";
	else
		total += 2;

	ComplexNumber divide_result = ComplexNumber(lval1, lval2) / ImaginaryNumber(rval);
	std::complex<double> std_divide_result = std::complex<double>(lval1, lval2) / std::complex<double>(0, rval);
	bool verify_division = equals(divide_result, std_divide_result);
	if (!verify_division) 
		grade_report << "\nTest14 : Error in / operator";
	else
		total += 2;

	return total;
}

int test_complex_complex_calculation(double lval1, double lval2, double rval1, double rval2, ofstream& grade_report) {
	int total = 0;
	ComplexNumber add_result = ComplexNumber(lval1, lval2) + ComplexNumber(rval1, rval2);
	std::complex<double> std_add_result = std::complex<double>(lval1, lval2) + std::complex<double>(rval1, rval2);
	bool verify_addition = equals(add_result, std_add_result);
	if (!verify_addition) 
		grade_report << "\nTest15: Error in + operator";
	else
		total += 2;

	ComplexNumber subtract_result = ComplexNumber(lval1, lval2) - ComplexNumber(rval1, rval2);
	std::complex<double> std_subtract_result = std::complex<double>(lval1, lval2) - std::complex<double>(rval1, rval2);
	bool verify_subtraction = equals(subtract_result, std_subtract_result);
	if (!verify_subtraction)
		grade_report << "\nTest15: Error in - operator";
	else
		total += 2;

	ComplexNumber multiply_result = ComplexNumber(lval1, lval2) * ComplexNumber(rval1, rval2);
	std::complex<double> std_multiply_result = std::complex<double>(lval1, lval2) * std::complex<double>(rval1, rval2);
	bool verify_multiplication = equals(multiply_result, std_multiply_result);
	if (!verify_multiplication)
		grade_report << "\nTest15: Error in * operator";
	else
		total += 2;

	ComplexNumber divide_result = ComplexNumber(lval1, lval2) / ComplexNumber(rval1, rval2);
	std::complex<double> std_divide_result = std::complex<double>(lval1, lval2) / std::complex<double>(rval1, rval2);
	bool verify_division = equals(divide_result, std_divide_result);
	if (!verify_division) 
		grade_report << "\nTest15: Error in / operator";
	else
		total += 2;

	return total;
}

void run_all_tests() {
	ofstream grade_report;
	int total = 100;
	int pass = 0;
	int current = 0;

	grade_report.open("grade_report.txt");
	grade_report << "Starting Autograder...\n\n";

	/* Construtor Tests */
	grade_report << "============Construtor/Magnitude/Phase Tests============\n";
	grade_report << "1. RealNumber Construtor/Magnitude/Phase ";
	pass += test_real_constructor(get_random_double(), grade_report);

	grade_report << "\n2. ImaginaryNumber Construtor/Magnitude/Phase ";
	pass += test_imaginary_constructor(get_random_double(), grade_report);

	grade_report << "\n3. ComplexNumber Construtor/Magnitude/Phase ";
	pass += test_complex_constructor(get_random_double(), get_random_double(), grade_report);

	grade_report << "\n\n";
	

	/* Getter and Setter Tests */
	grade_report << "============Getter and Setter Tests============\n";
	grade_report << "4. RealNumber Getter/Setter ";
	pass += test_real_getter_setter(get_random_double(), grade_report);

	grade_report << "\n5. ImaginaryNumber Getter/Setter " ;
	pass += test_imaginary_getter_setter(get_random_double(), grade_report);

	grade_report << "\n6. ComplexNumber Getter/Setter ";
	pass += test_complex_getter_setter(get_random_double(), get_random_double(), grade_report);

	grade_report << "\n\n";
  
	/* Real Number Calculation Tests */
	grade_report << "============Real Number Calculation Tests============\n";
	grade_report << "7. RealNumber (op) RealNumber ";
	current = test_real_real_calculation(get_random_double(), get_random_double(), grade_report);
	grade_report << "\n+"<< current << "pts" << endl;
	pass += current;

	grade_report << "\n8. RealNumber (op) ImaginaryNumber ";
	current = test_real_imaginary_calculation(get_random_double(), get_random_double(), grade_report);
	grade_report << "\n+"<< current << "pts" << endl;
	pass += current;

	grade_report << "\n9. RealNumber (op) ComplexNumber ";
	current = test_real_complex_calculation(get_random_double(), get_random_double(), get_random_double(), grade_report);
	grade_report << "\n+"<< current << "pts" << endl;
	pass += current;

	grade_report << "\n\n";
	/* ImaginaryNumber Number Calculation Tests */
	grade_report << "============Imaginary Number Calculation Tests============\n";
	grade_report << "10. ImaginaryNumber (op) RealNumber ";
	current = test_imaginary_real_calculation(get_random_double(), get_random_double(), grade_report);
	grade_report << "\n+"<< current << "pts" << endl;
	pass += current;

	grade_report << "\n11. ImaginaryNumber (op) ImaginaryNumber ";
	current = test_imaginary_imaginary_calculation(get_random_double(), get_random_double(), grade_report);
	grade_report << "\n+"<< current << "pts" << endl;
	pass += current;

	grade_report << "\n12. ImaginaryNumber (op) ComplexNumber ";
	current = test_imaginary_complex_calculation(get_random_double(), get_random_double(), get_random_double(), grade_report);
	grade_report << "\n+"<< current << "pts" << endl;
	pass += current;

	grade_report << "\n\n";
	/* ComplexNumber Number Calculation Tests */
	grade_report << "============Complex Number Calculation Tests============\n";
	grade_report << "13. ComplexNumber (op) RealNumber ";
	current = test_complex_real_calculation(get_random_double(), get_random_double(), get_random_double(), grade_report);
	grade_report << "\n+"<< current << "pts" << endl;
	pass += current;

	grade_report << "\n14. ComplexNumber (op) ImaginaryNumber ";
	current = test_complex_imaginary_calculation(get_random_double(), get_random_double(), get_random_double(), grade_report);
	grade_report << "\n+"<< current << "pts" << endl;
	pass += current;

	grade_report << "\n15. ComplexNumber (op) ComplexNumber ";
	current = test_complex_complex_calculation(get_random_double(), get_random_double(), get_random_double(), get_random_double(), grade_report);
	grade_report << "\n+"<< current << "pts" << endl;
	pass += current;

	grade_report << "\n\n";
	grade_report << "Grading Complete! Total score is " << pass << " out of " << total << " points.";
	grade_report.close();
}