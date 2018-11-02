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
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "wire.h"
#include "io.h"
#include "dp.h"

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
   
   Wires wires; 
   Datapath datapath;
   int currentLine = 0;
   bool error = false;

   while(!netlistFile.eof()){ 
      if(getline(netlistFile, line) && !error){ //Build data structures while parsing input file
         currentLine ++;
         vector<string> words = splitLine(line);
         if(words.size() < 3){ //Blank Line
            //cout << "blank line" <<endl;
         }
         else if(words.at(0).compare(0, 2, "//") == 0){ //Comment Line
            //cout << "comment line" <<endl;
         }
         else if(words.size()>2 && (words.at(0).compare("input")==0 || words.at(0).compare("output")==0 || 
                                    words.at(0).compare("wire")==0 || words.at(0).compare("register")==0)){ //Line Defining Inputs
            //cout << "declaration line" <<endl;
            error = !wires.addByLine(words, currentLine);
         }
         else if(words.at(1).compare("=")==0){ //operation line
            //cout << "op line: ";
            error = !datapath.addByLine(words, &wires, currentLine);
         }
         verilogFile << "//" <<line << endl;
      }
   }
   verilogFile << endl;
   netlistFile.close();
   if(1){
      cout << endl;
      verilogFile << "module Circuit (";
      cout << "module Circuit (";
      for(int i = 1; i < wires.size(); i++){
          if(wires.at(i)->getType() == WIRE){}
          else {
              verilogFile << wires.at(i)->getName() << ", ";
              cout << wires.at(i)->getName() << ", ";
          }
      }
      verilogFile << "Clk, Rst);" << endl;
      cout << "Clk, Rst);" << endl;
      verilogFile << "input Clk, Rst;" << endl;
      cout << "input Clk, Rst;" << endl;

      for(int i = 1; i< wires.size(); i++){ //Debugging Print all inputs, outputs, wires, registres //start at 1 because zero is the 'empty wire'
         //cout << wires.at(i)->getTypeS()<<": "<<wires.at(i)->getName() << ": " << wires.at(i)->getSign() << wires.at(i)->getWidth() << endl;
         verilogFile << wires.at(i)->printToFile();
         cout << wires.at(i)->printToFile();
      }
      verilogFile << endl;
      cout << endl;
      for(int i = 0; i< datapath.size(); i++){ //Debugging print all data path components
         //cout << datapath.at(i)->getOpS()<< datapath.at(i)->getWidth() << endl;
         verilogFile << datapath.at(i)->print();
         cout << datapath.at(i)->print();
      }
      verilogFile << "endmodule" << endl;
      cout << "endmodule" << endl;
      verilogFile.close();
      
      return 0;
   }
   else{
      verilogFile.close();
      return -1;
   }
}
