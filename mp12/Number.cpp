#include "Number.h"

//Empty constructor sets number_type as undefined value
Number::Number(){
	number_type = -1;
	magnitude = 0.0;
	phase = 0.0;
}

//Complete constructor sets number_type according to input value
Number::Number(int my_number_type, double my_magnitude, double my_phase){
	number_type = my_number_type;
	magnitude = my_magnitude;
	phase = my_phase;
}

//toString function prints warning if to string function not overloaded
string Number::to_String(void){
	stringstream my_output;
	string Number_type_string = "";
	switch (number_type){
		case REAL:
			Number_type_string = "REAL";
			break;
		case IMAGINARY:
			Number_type_string = "IMAGINARY";
			break;
		case COMPLEX:
			Number_type_string = "COMPLEX";
			break;
		default:
			Number_type_string = "UNDEFINED";
			break;
	}
	my_output << "Error: Number type ";
	my_output << Number_type_string;
	my_output << " does not have a valid to_String() method!!\n";
	string output_string = my_output.str();
	return output_string;
}

//Getter function for number_type variable
int Number::get_number_type() const{
	return number_type;
}

//Setter function for number_type variable
void Number::set_number_type(int my_Number_type){
	number_type = my_Number_type;
}

//Getter function for magnitude variable
double Number::get_magnitude() const{
	return magnitude;
}

//Getter function for phase variable
double Number::get_phase() const{
	return phase;
}

//Operator for + Will never execute (should be overwritten by derived class)
Number Number::operator + (const Number& arg)
{
    Number result;
    return result;
}

//Operator for - Will never execute (should be overwritten by derived class)
Number Number::operator - (const Number& arg)
{
    Number result;
    return result;
}

//Operator for * Will never execute (should be overwritten by derived class)
Number Number::operator * (const Number& arg)
{
    Number result;
    return result;
}

//Operator for / Will never execute (should be overwritten by derived class)
Number Number::operator / (const Number& arg)
{
    Number result;
    return result;
}