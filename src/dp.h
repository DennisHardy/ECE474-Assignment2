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
   public:
      Component(vector<string> inputs, vector<string> outputs, operation op, Wires* available, bool* error);
      operation getOp();
      string getOpS();
      int getWidth();
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