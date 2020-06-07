#ifndef REAL_NUMBER_H
#define REAL_NUMBER_H

#include "Number.h"
class RealNumber;  //This is a forward declaration, needed only to remove circular dependencies
#include "ImaginaryNumber.h"
#include "ComplexNumber.h"
#include <stdlib.h>


class RealNumber:public Number{
	private:
		//Class variables
		double real_component;
	public:
		//Empty Constructor		
		RealNumber();
		//Complete Constructor
		RealNumber(double rval);
		//Copy Constructor
		RealNumber(const RealNumber&);

		//Setter and getter functions
		void set_real_component(double rval);
		double get_real_component() const;	
		double get_magnitude() const;	
		double get_phase() const;

		//Operation overload for RealNumber (op) RealNumber
		RealNumber operator + (const RealNumber& arg);
		RealNumber operator - (const RealNumber& arg);
		RealNumber operator * (const RealNumber& arg);
		RealNumber operator / (const RealNumber& arg);

		//Operation overload for RealNumber (op) ImaginaryNumber
		ComplexNumber operator + (const ImaginaryNumber& arg);
		ComplexNumber operator - (const ImaginaryNumber& arg);
		ImaginaryNumber operator * (const ImaginaryNumber& arg);
		ImaginaryNumber operator / (const ImaginaryNumber& arg);

		//Operation overload for RealNumber (op) ComplexNumber
		ComplexNumber operator + (const ComplexNumber& arg);
		ComplexNumber operator - (const ComplexNumber& arg);
		ComplexNumber operator * (const ComplexNumber& arg);
		ComplexNumber operator / (const ComplexNumber& arg);

		//Output class variables as string (provided)
		string to_String();
};

#endif
