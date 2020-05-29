#ifndef COMPLEX_NUMBER_H
#define COMPLEX_NUMBER_H

#include "Number.h"
class ComplexNumber;  //This is a forward declaration, needed only to remove circular dependencies
#include "RealNumber.h"
#include "ImaginaryNumber.h"
#include <stdlib.h>

class ComplexNumber:public Number{
	private:
		//Class variables
		double real_component;
		double imaginary_component;
	public:
		//Empty Constructor		
		ComplexNumber();
		//Complete Constructor
		ComplexNumber(double rval_real_component, double rval_imaginary_component);
		//Copy Constructor
		ComplexNumber(const ComplexNumber&);

		//Setter and getter functions
		void set_real_component(double rval);
		double get_real_component() const;
		void set_imaginary_component(double rval);
		double get_imaginary_component() const;	
		double get_magnitude() const;	
		double get_phase() const;

		//Operation overload for ComplexNumber (op) ComplexNumber
		ComplexNumber operator + (const ComplexNumber& arg);
		ComplexNumber operator - (const ComplexNumber& arg);
		ComplexNumber operator * (const ComplexNumber& arg);
		ComplexNumber operator / (const ComplexNumber& arg);

		//Operation overload for ComplexNumber (op) RealNumber
		ComplexNumber operator + (const RealNumber& arg);
		ComplexNumber operator - (const RealNumber& arg);
		ComplexNumber operator * (const RealNumber& arg);
		ComplexNumber operator / (const RealNumber& arg);

		//Operation overload for ComplexNumber (op) ImaginaryNumber
		ComplexNumber operator + (const ImaginaryNumber& arg);
		ComplexNumber operator - (const ImaginaryNumber& arg);
		ComplexNumber operator * (const ImaginaryNumber& arg);
		ComplexNumber operator / (const ImaginaryNumber& arg);

		//Output class variables as string (provided)
		string to_String();
};

#endif
