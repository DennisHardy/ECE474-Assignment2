/******************************************************************************
Assignment 2   ECE 474
Team Members: Zachary Alvarez, Denniss Hardy, Zi Wang
Description: using command line arguments to accept an input & output file,
Program converts the given input file to Verilog and saves it in the output file
All empty lines should be ignored
● All lines beginning with "//" are considered comments and should be ignored
● The netlist file can be assumed to be fully space/tab delimited, i.e. one or more space or tab characters
should appear between each token that needs to be parsed, including colons.
● Circuit inputs and outputs can be declared on a line using the formats:

input dataType inputName1, inputName2
output dataType outputName1, outputName2

Valid data types include:
○ Signed Integers Types: Int1, Int2, Int8, Int16, Int32, and Int64
○ Unsigned Integer Types: UInt1, UInt2, UInt8, UInt16, UInt32, and UInt64
○ The number after Int and UInt specifies the width of the data input, output, register 
*******************************************************************************/

#include<iostream>
using namespace std; 

int main(int argc, char *argv[]){
   //std::cout << "Hello World!" << std::endl;
   for(i = 0; i < argc; i++){
      cout << "Argument " << i << " " << argv[i] << "\n";
   }
   return 0;
}
