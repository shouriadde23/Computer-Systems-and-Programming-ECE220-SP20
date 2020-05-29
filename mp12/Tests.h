#ifndef TESTS_H
#define TESTS_H

double get_random_double();

int test_real_constructor(double rval, ofstream& grade_report);
int test_imaginary_constructor(double rval, ofstream& grade_report);
int test_complex_constructor(double rval1, double rval2, ofstream& grade_report);

int test_real_getter_setter(double rval, ofstream& grade_report);
int test_imaginary_getter_setter(double rval, ofstream& grade_report);
int test_complex_getter_setter(double rval1, double rval2, ofstream& grade_report);

int test_real_real_calculation(double lval, double rval, ofstream& grade_report);
int test_real_imaginary_calculation(double lval, double rval, ofstream& grade_report);
int test_real_complex_calculation(double lval, double rval1, double rval2, ofstream& grade_report);

int test_imaginary_real_calculation(double lval, double rval, ofstream& grade_report);
int test_imaginary_imaginary_calculation(double lval, double rval, ofstream& grade_report);
int test_imaginary_complex_calculation(double lval, double rval1, double rval2, ofstream& grade_report);

int test_complex_real_calculation(double lval1, double lval2, double rval, ofstream& grade_report);
int test_complex_imaginary_calculation(double lval1, double lval2, double rval, ofstream& grade_report);
int test_complex_complex_calculation(double lval1, double lval2, double rval1, double rval2, ofstream& grade_report);

void run_all_tests();

#endif