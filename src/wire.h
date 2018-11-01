#ifndef WIRE_H
#define WIRE_H


#include <string>
#include <vector>
#include <sstream>
using namespace std;
enum type {INPUT, OUTPUT, WIRE, REGISTER, ERROR=-1};

class wire //this class implements not only wires, but also inputs, outputs, and registers
{
   private:
      string name;
      int width;
      bool sign; //true = signed false=unsigned
      type myType;
   public:
      wire(string name, int width, bool sign, type myType);
      wire();
      string getName();
      int getWidth();
      char getSign();
      type getType();
      string getTypeS();
      string printToFile();
};
 
class Wires
{
   private:
      vector<wire*> wires;
   public:
      Wires();
      bool add(wire* addMe); //returns true if success
      int size();
      wire* at(int i);
      bool addByLine(const vector<string> &words, int lineNumber);
};



int typeToWidth(string dataType);
bool typeToSign(string dataType);
type typeParser(string type);
#endif