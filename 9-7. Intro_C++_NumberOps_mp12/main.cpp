#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Number.h"
#include "RealNumber.h"
#include "ImaginaryNumber.h"
#include "ComplexNumber.h"
#include "Tests.h"
#include "Expression.h"


using namespace std;

//Main function: do not modify
int main(int argc,char *argv[])
{
	if (argc == 3){
		   	ifstream inFile (argv[1]);
	   	ofstream outFile (argv[2]);
	   	string current_line = "";

		while (inFile)
		{
			if (!inFile.eof()){
				getline(inFile, current_line);
				Expression my_expression = Expression();
				if(my_expression.input_expression(current_line)){
					my_expression.evaluate_expression();
					outFile << my_expression.print_result() << endl;
				}
			}
			else
				break;
		}
		inFile.close();
		outFile.close();
	} else if (argc == 1) {
		run_all_tests();
	} else {
		fprintf(stderr,"Wrong number of arguments.\nCorrect usage: %s tests.txt output_file.txt\n",
					argv[0]);
		return -1;
	}

   	return 0;
}