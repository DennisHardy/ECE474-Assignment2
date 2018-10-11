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

#include <iostream>
#include <fstream>
#include <string>
using namespace std; 

int main(int argc, char *argv[]){
   //Alert user if invalid usage
   if(argc != 3){
      cout << "Input and/or output files not specified" << endl;
      cout << "usage: dpgen netlistFile verilogFile" <<endl;
      return -1;
   }

   ifstream netlistFile;
   ofstream verilogFile;
   string line;
   verilogFile.open(argv[2]);
   netlistFile.open(argv[1]);

   if(!verilogFile.is_open()){
      cout << "Could not open " << argv[2] << endl;
      return -1;
   }
   if(!netlistFile.is_open()){
      cout << "Could not open " << argv[1] << endl;
      return -1;
   }
   
   while(!netlistFile.eof()){
      if(getline(netlistFile, line)){
         verilogFile << line << endl;
      }
   }

   netlistFile.close();
   verilogFile.close();
   
   return 0;
}
