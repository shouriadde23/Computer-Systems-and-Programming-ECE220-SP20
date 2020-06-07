#include "Expression.h"

//Instantiates Empty Expression
Expression::Expression(){
	my_operator = '0';
	left_Number = NULL;
	right_Number = NULL;
	result = NULL;
}

//Instantiates Expression and parses input string
Expression::Expression(string expression_string){
	my_operator = '0';
	left_Number = NULL;
	right_Number = NULL;
	result = NULL;
	input_expression(expression_string);
}

//Function used to input string
bool Expression::input_expression(string expression_string){
	size_t operator_index;
	if (expression_string.find(" + ") != std::string::npos)
		operator_index = expression_string.find(" + ");
	else if (expression_string.find(" - ") != std::string::npos)
		operator_index = expression_string.find(" - ");
	else if (expression_string.find(" * ") != std::string::npos)
		operator_index = expression_string.find(" * ");
	else if (expression_string.find(" / ") != std::string::npos)
		operator_index = expression_string.find(" / ");
	else 
		return false;

	my_operator = expression_string[operator_index + 1];

	string left = expression_string.substr(0, operator_index);
	string right = expression_string.substr(operator_index+3, expression_string.size() - 1);
	
	if (left.find('i') != std::string::npos){
		string s = left;
		s.pop_back();
		imaginary1 = ImaginaryNumber(std::stod(s));
		left_Number = &imaginary1;
	}
	else if (left.find(',') == std::string::npos){
		string s = left;
		real1 = RealNumber(std::stod(s));
		left_Number = &real1;
	}
	else {
		string s = left;
		s.pop_back();
		s.erase(0, 1);
		std::vector<std::string> pair;
		boost::split(pair, s, boost::is_any_of(","));
		complex1 = ComplexNumber(std::stod(pair[0]), std::stod(pair[1]));
		left_Number = &complex1;
	}

	if (right.find('i') != std::string::npos){
		string s = right;
		s.pop_back();
		imaginary2 = ImaginaryNumber(std::stod(s));
		right_Number = &imaginary2;
	}
	else if (right.find(',') == std::string::npos){
		string s = right;
		real2 = RealNumber(std::stod(s));
		right_Number = &real2;
	}
	else {
		string s = right;
		s.pop_back();
		s.erase(0, 1);
		std::vector<std::string> pair;
		boost::split(pair, s, boost::is_any_of(","));
		complex2 = ComplexNumber(std::stod(pair[0]), std::stod(pair[1]));
		right_Number = &complex2;
	}

	return true;
}

//Function used to evaluate expression
//Expressions will be evaluated based on data types of left and right operands
void Expression::evaluate_expression(){
	int left_type = left_Number->get_number_type();
	int right_type = right_Number->get_number_type();
	switch(my_operator){
		case '+':
			switch(left_type){
				case REAL:
					if(right_type == REAL){
						real3 = *(dynamic_cast<RealNumber*>(left_Number)) + *(dynamic_cast<RealNumber*>(right_Number));
						result = &real3;
					}
					else if(right_type == IMAGINARY){
						complex3 = *(dynamic_cast<RealNumber*>(left_Number)) + *(dynamic_cast<ImaginaryNumber*>(right_Number));
						result = &complex3;
					}
					else if(right_type == COMPLEX){
						complex3 = *(dynamic_cast<RealNumber*>(left_Number)) + *(dynamic_cast<ComplexNumber*>(right_Number));
						result = &complex3;
					}
					break;
				case IMAGINARY:
					if(right_type == REAL){
						complex3 = *(dynamic_cast<ImaginaryNumber*>(left_Number)) + *(dynamic_cast<RealNumber*>(right_Number));
						result = &complex3;
					}
					if(right_type == IMAGINARY){
						imaginary3 = *(dynamic_cast<ImaginaryNumber*>(left_Number)) + *(dynamic_cast<ImaginaryNumber*>(right_Number));
						result = &imaginary3;
					}
					if(right_type == COMPLEX){
						complex3 = *(dynamic_cast<ImaginaryNumber*>(left_Number)) + *(dynamic_cast<ComplexNumber*>(right_Number));
						result = &complex3;
					}
					break;
				case COMPLEX:
					if(right_type == REAL){
						complex3 = *(dynamic_cast<ComplexNumber*>(left_Number)) + *(dynamic_cast<RealNumber*>(right_Number));
						result = &complex3;
					}
					if(right_type == IMAGINARY){
						complex3 = *(dynamic_cast<ComplexNumber*>(left_Number)) + *(dynamic_cast<ImaginaryNumber*>(right_Number));
						result = &complex3;
					}
					if(right_type == COMPLEX){
						complex3 = *(dynamic_cast<ComplexNumber*>(left_Number)) + *(dynamic_cast<ComplexNumber*>(right_Number));
						result = &complex3;
					}
					break;
				default:
					*result = *left_Number + *right_Number;
					break;
			}
			break;
		case '-':
			switch(left_type){
				case REAL:
					if(right_type == REAL){
						real3 = *(dynamic_cast<RealNumber*>(left_Number)) - *(dynamic_cast<RealNumber*>(right_Number));
						result = &real3;
					}
					else if(right_type == IMAGINARY){
						complex3 = *(dynamic_cast<RealNumber*>(left_Number)) - *(dynamic_cast<ImaginaryNumber*>(right_Number));
						result = &complex3;
					}
					else if(right_type == COMPLEX){
						complex3 = *(dynamic_cast<RealNumber*>(left_Number)) - *(dynamic_cast<ComplexNumber*>(right_Number));
						result = &complex3;
					}
					break;
				case IMAGINARY:
					if(right_type == REAL){
						complex3 = *(dynamic_cast<ImaginaryNumber*>(left_Number)) - *(dynamic_cast<RealNumber*>(right_Number));
						result = &complex3;
					}
					if(right_type == IMAGINARY){
						imaginary3 = *(dynamic_cast<ImaginaryNumber*>(left_Number)) - *(dynamic_cast<ImaginaryNumber*>(right_Number));
						result = &imaginary3;
					}
					if(right_type == COMPLEX){
						complex3 = *(dynamic_cast<ImaginaryNumber*>(left_Number)) - *(dynamic_cast<ComplexNumber*>(right_Number));
						result = &complex3;
					}
					break;
				case COMPLEX:
					if(right_type == REAL){
						complex3 = *(dynamic_cast<ComplexNumber*>(left_Number)) - *(dynamic_cast<RealNumber*>(right_Number));
						result = &complex3;
					}
					if(right_type == IMAGINARY){
						complex3 = *(dynamic_cast<ComplexNumber*>(left_Number)) - *(dynamic_cast<ImaginaryNumber*>(right_Number));
						result = &complex3;
					}
					if(right_type == COMPLEX){
						complex3 = *(dynamic_cast<ComplexNumber*>(left_Number)) - *(dynamic_cast<ComplexNumber*>(right_Number));
						result = &complex3;
					}
					break;
				default:
					*result = *left_Number - *right_Number;
					break;
			}
			break;
		case '/':
			switch(left_type){
				case REAL:
					if(right_type == REAL){
						real3 = *(dynamic_cast<RealNumber*>(left_Number)) / *(dynamic_cast<RealNumber*>(right_Number));
						result = &real3;
					}
					else if(right_type == IMAGINARY){
						imaginary3 = *(dynamic_cast<RealNumber*>(left_Number)) / *(dynamic_cast<ImaginaryNumber*>(right_Number));
						result = &imaginary3;
					}
					else if(right_type == COMPLEX){
						complex3 = *(dynamic_cast<RealNumber*>(left_Number)) / *(dynamic_cast<ComplexNumber*>(right_Number));
						result = &complex3;
					}
					break;
				case IMAGINARY:
					if(right_type == REAL){
						imaginary3 = *(dynamic_cast<ImaginaryNumber*>(left_Number)) / *(dynamic_cast<RealNumber*>(right_Number));
						result = &imaginary3;
					}
					if(right_type == IMAGINARY){
						real3 = *(dynamic_cast<ImaginaryNumber*>(left_Number)) / *(dynamic_cast<ImaginaryNumber*>(right_Number));
						result = &real3;
					}
					if(right_type == COMPLEX){
						complex3 = *(dynamic_cast<ImaginaryNumber*>(left_Number)) / *(dynamic_cast<ComplexNumber*>(right_Number));
						result = &complex3;
					}
					break;
				case COMPLEX:
					if(right_type == REAL){
						complex3 = *(dynamic_cast<ComplexNumber*>(left_Number)) / *(dynamic_cast<RealNumber*>(right_Number));
						result = &complex3;
					}
					if(right_type == IMAGINARY){
						complex3 = *(dynamic_cast<ComplexNumber*>(left_Number)) / *(dynamic_cast<ImaginaryNumber*>(right_Number));
						result = &complex3;
					}
					if(right_type == COMPLEX){
						complex3 = *(dynamic_cast<ComplexNumber*>(left_Number)) / *(dynamic_cast<ComplexNumber*>(right_Number));
						result = &complex3;
					}
					break;
				default:
					*result = *left_Number / *right_Number;
					break;
			}
			break;
		case '*':
			switch(left_type){
				case REAL:
					if(right_type == REAL){
						real3 = *(dynamic_cast<RealNumber*>(left_Number)) * *(dynamic_cast<RealNumber*>(right_Number));
						result = &real3;
					}
					else if(right_type == IMAGINARY){
						imaginary3 = *(dynamic_cast<RealNumber*>(left_Number)) * *(dynamic_cast<ImaginaryNumber*>(right_Number));
						result = &imaginary3;
					}
					else if(right_type == COMPLEX){
						complex3 = *(dynamic_cast<RealNumber*>(left_Number)) * *(dynamic_cast<ComplexNumber*>(right_Number));
						result = &complex3;
					}
					break;
				case IMAGINARY:
					if(right_type == REAL){
						imaginary3 = *(dynamic_cast<ImaginaryNumber*>(left_Number)) * *(dynamic_cast<RealNumber*>(right_Number));
						result = &imaginary3;
					}
					if(right_type == IMAGINARY){
						real3 = *(dynamic_cast<ImaginaryNumber*>(left_Number)) * *(dynamic_cast<ImaginaryNumber*>(right_Number));
						result = &real3;
					}
					if(right_type == COMPLEX){
						complex3 = *(dynamic_cast<ImaginaryNumber*>(left_Number)) * *(dynamic_cast<ComplexNumber*>(right_Number));
						result = &complex3;
					}
					break;
				case COMPLEX:
					if(right_type == REAL){
						complex3 = *(dynamic_cast<ComplexNumber*>(left_Number)) * *(dynamic_cast<RealNumber*>(right_Number));
						result = &complex3;
					}
					if(right_type == IMAGINARY){
						complex3 = *(dynamic_cast<ComplexNumber*>(left_Number)) * *(dynamic_cast<ImaginaryNumber*>(right_Number));
						result = &complex3;
					}
					if(right_type == COMPLEX){
						complex3 = *(dynamic_cast<ComplexNumber*>(left_Number)) * *(dynamic_cast<ComplexNumber*>(right_Number));
						result = &complex3;
					}
					break;
				default:
					*result = *left_Number * *right_Number;
					break;
			}
			break;
		default:
			cout << "Warning: Operation '" << my_operator << "' is not supported!!\n";
			break; 
	}
}

//Print output results
string Expression::print_result(){
	result->get_number_type();
	string output_string;
	switch(result->get_number_type()){
		case REAL:
			output_string = (dynamic_cast<RealNumber*>(result))->to_String();
			break;
		case IMAGINARY:
			output_string = (dynamic_cast<ImaginaryNumber*>(result))->to_String();
			break;
		case COMPLEX:
			output_string = (dynamic_cast<ComplexNumber*>(result))->to_String();
			break;
		default:
			output_string = "Error: result NumberType is undefined!\n";
			break;
	}
	return output_string;
}
