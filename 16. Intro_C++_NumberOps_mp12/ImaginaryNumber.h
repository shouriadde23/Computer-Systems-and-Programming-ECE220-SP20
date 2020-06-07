#ifndef IMAGINARY_NUMBER_H
#define IMAGINARY_NUMBER_H

#include "Number.h"
class ImaginaryNumber;  //This is a forward declaration, needed only to remove circular dependencies
#include "RealNumber.h"
#include "ComplexNumber.h"
#include <stdlib.h>

class ImaginaryNumber:public Number{
	private:
		//Class variables
		double imaginary_component;
	public:
		//Empty Constructor		
		ImaginaryNumber();
		//Complete Constructor
		ImaginaryNumber(double rval);
		//Copy Constructor
		ImaginaryNumber(const ImaginaryNumber&);

		//Setter and getter functions
		void set_imaginary_component(double rval);
		double get_imaginary_component() const;	
		double get_magnitude() const;	
		double get_phase() const;

		//Operation overload for ImaginaryNumber (op) ImaginaryNumber
		ImaginaryNumber operator + (const ImaginaryNumber& arg);
		ImaginaryNumber operator - (const ImaginaryNumber& arg);
		RealNumber operator * (const ImaginaryNumber& arg);
		RealNumber operator / (const ImaginaryNumber& arg);

		//Operation overload for ImaginaryNumber (op) RealNumber
		ComplexNumber operator + (const RealNumber& arg);
		ComplexNumber operator - (const RealNumber& arg);
		ImaginaryNumber operator * (const RealNumber& arg);
		ImaginaryNumber operator / (const RealNumber& arg);

		//Operation overload for ImaginaryNumber (op) ComplexNumber
		ComplexNumber operator + (const ComplexNumber& arg);
		ComplexNumber operator - (const ComplexNumber& arg);
		ComplexNumber operator * (const ComplexNumber& arg);
		ComplexNumber operator / (const ComplexNumber& arg);

		//Output class variables as string (provided)
		string to_String();
};

#endif
