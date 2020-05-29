#ifndef Number_H
#define Number_H

#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;

enum Number_Types { REAL, IMAGINARY, COMPLEX };

class Number {
	protected:
		//Superclass variables (inherited by all derived classes)
		int number_type;
		double magnitude;
		double phase;
	public:	
		//Superclass constructors
		Number();
		Number(int my_number_type, double my_magnitude, double my_phase);

		//Getter functions
		void set_number_type(int my_Number_type);
		int get_number_type() const;	
		double get_magnitude() const;	
		double get_phase() const;

		//operator overload
		virtual Number operator + (const Number& arg);
		virtual Number operator - (const Number& arg);
		virtual Number operator * (const Number& arg);
		virtual Number operator / (const Number& arg);

		//Converts class data to string (provides warning if derived class not used)
		string to_String();
};

#endif
