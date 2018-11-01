#ifndef DP_H
#define DP_H

#include <vector>
#include <string>
#include <iostream>
#include "wire.h"
using namespace std;

enum operation {REG, ADD, SUB, MUL, COMP, MUX, SHR, SHL, ERROR_OP=-1};

class Component
{
   private:
      operation op;
      vector<wire*> inputs;
      vector<wire*> outputs;
      int width;
      int id;
   public:
      Component(vector<string> inputs, vector<string> outputs, operation op, Wires* available, int id, bool* error);
      operation getOp();
      string getOpS();
      int getWidth();
      int getId();
      string getInput(int i);
      string getOutputS(int i);
      wire* getOutput(int i);
      void setOutput(int i, wire* output);
      string print();
};

class Datapath
{
   private:
      vector<Component*> components;
   public:
      Datapath();
      bool addByLine(vector<string> words, Wires* wires, int currentLine);
      bool add(Component* addMe);
      int size();
      Component* at(int i);
};

operation parseOp(string in);
#endif