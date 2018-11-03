#include <stdio.h>
#include "wire.h"
#include <string>
#include <iostream>

using namespace std;

wire::wire(string name, int width, bool sign, type myType){
   this->name = name;
   this->width = width;
   this->sign = sign;
   this->myType = myType;
}
wire::wire(){
   this->name = "";
   this->width = 0;
   this->sign = false;
   this->myType = WIRE;
}
string wire::getName(){
   return this->name;
}
int wire::getWidth(){
   return this->width;
}
char wire::getSign(){
   if(this->sign){
      return 's';
   }
   else{
      return 'u';
   }
}
type wire::getType(){
   return myType;
}
string wire::getTypeS(){
   switch (this->myType) {
      case INPUT: return "input";
      case OUTPUT: return "output";
      case WIRE: return "wire";
      case REGISTER: return "register";
      default: return "error:";
   }
}
string wire::printToFile(){
   stringstream out;
   out << this->getTypeS();
   if(this->getType() == OUTPUT){
      out << " reg";
   }
   if(this->getSign() == 's'){
      out << " signed";
   }
   if( this->getWidth() == 1){
      out <<" " << this->getName() << ";" << endl;
   }
   else{
      out <<" [" << this->getWidth()-1 << ":0] " << this->getName() << ";" << endl;
   }
   return out.str();
}


int typeToWidth(string dataType){
   if(dataType.compare("Int1") == 0 || dataType.compare("UInt1") == 0 ){
      return 1;
   }
   else if(dataType.compare("Int2") == 0 || dataType.compare("UInt2") == 0 ){
      return 2;
   }
   else if(dataType.compare("Int8") == 0 || dataType.compare("UInt8") == 0 ){
      return 8;
   }
   else if(dataType.compare("Int16") == 0 || dataType.compare("UInt16") == 0 ){
      return 16;
   }
   else if(dataType.compare("Int32") == 0 || dataType.compare("UInt32") == 0 ){
      return 32;
   }
   else if(dataType.compare("Int64") == 0 || dataType.compare("UInt64") == 0 ){
      return 64;
   }
   else{
      return -1;
   }
}

bool Wires::add(wire* addMe){//returns success=true, fail=false
   for(int i=0; i<wires.size(); i++){ //loop through existing 'wires' and checks if already declared
      if (wires.at(i)->getName().compare(addMe->getName())==0){
         cout << "Error: Redeclaration of Wire, Input, Output, or Register:" << addMe->getName() <<endl;
         return false;
      }
   }
   wires.push_back(addMe);
   return true;
}
bool Wires::addByLine(const vector<string> &words, int lineNumber){
   bool error = false;
   type dataType = typeParser(words.at(0));
   if(dataType == ERROR){
      error = true;
      cout << "Error" <<endl;
   }
   int width = typeToWidth(words.at(1));
   if(width == -1){
      cout << "Invalid data type:" << words.at(1) << " at line " << lineNumber << "." << endl;
      return false;
   }
   bool sign = typeToSign(words.at(1));
   for(int i = 2; i <words.size(); i++){ //from the third word on, add a 'wire' for each word until out of words or a comment
      if(words.at(i).compare(0,2,"//")==0){//ignore anything after '//'
         break;
      }
      wire *tempWire = new wire(words.at(i), width, sign, dataType);
      error = !this->add(tempWire);
   }
   return !error;
}
int Wires::size(){
   return wires.size();
}
wire* Wires::at(int i){
   return wires.at(i);
}

Wires::Wires(){
   wire *aWire = new wire();
   this->add(aWire);
   return;
}

bool typeToSign(string dataType){
   if(dataType.compare("Int1")==0  || dataType.compare("Int2")==0 || dataType.compare("Int8") ==0 ||
      dataType.compare("Int16")==0 || dataType.compare("Int32") ==0){
      return true;
   }
   else if(dataType.compare("UInt1")==0  || dataType.compare("UInt2")==0 || dataType.compare("UInt8") ==0 ||
           dataType.compare("UInt16")==0 || dataType.compare("UInt32") ==0){
      return false;
   }
   else{
      return false;
   }
}
type typeParser(string dataType){
   if(dataType.compare("input") == 0){
      return INPUT;
   }
   else if(dataType.compare("output") == 0){
      return OUTPUT;
   }
   else if(dataType.compare("wire") ==0){
      return WIRE;
   }
   else if(dataType.compare("register") ==0){
      return REGISTER;
   }
   else{
      return ERROR;
   }
}
