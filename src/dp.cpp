#include "dp.h"

Datapath::Datapath(){
   return;
}

bool Datapath::addByLine(vector<string> words, Wires* available, int currentLine){
   bool error = false;
   vector<string> inputs;
   vector<string> outputs;
   operation op;

   if(words.size() == 3){
      op = REG;
   }
   else{
      op = parseOp(words.at(3));
      if(op == ERROR_OP){
         cout << "Invalid oporator: " << words.at(3) << " at line:"<<currentLine <<endl;
         error =true;
      }
      else if(op == MUX){
         if(words.at(5).compare(":") != 0){
            cout << "Invalid oporator: " << words.at(5) << " at line:"<<currentLine <<endl;
            op = ERROR_OP;
            error = true;
         }
      }
   }
   switch(op){
      case REG:
         outputs.push_back(words.at(0));
         inputs.push_back(words.at(2));
         break;

      case ADD:
      case SUB:
      case MUL:
      case COMP:
      case SHR:
      case SHL:
         outputs.push_back(words.at(0));
         inputs.push_back(words.at(2));
         inputs.push_back(words.at(4));
         break;

      case MUX:
         outputs.push_back(words.at(0));
         inputs.push_back(words.at(2));
         inputs.push_back(words.at(4));
         inputs.push_back(words.at(6));
         break;

      default:
         error = true;
         break;
   }
   if(!error){
      Component *tempComponent = new Component(inputs, outputs, op, available, &error);
      this->add(tempComponent);
   }
   return !error;
}

int Datapath::size(){
      return this->components.size();
}
Component* Datapath::at(int i){
      return this->components.at(i);
}
bool Datapath::add(Component* addMe){
      this->components.push_back(addMe);
      return true;
}

Component::Component( vector<string> inputs, vector<string> outputs, operation op, Wires *available, bool* error){
   
   bool found;
   for(int i = 0; i<inputs.size(); i++){//check that inputs provided exist
      found = false;
      for(int j = 0; j<available->size(); j++){
         if (inputs.at(i).compare(available->at(j)->getName())==0){
            found = true;
            if(available->at(j)->getType() == OUTPUT){ //can't use output as input
               cout << "Output: " << available->at(j)->getName() << " used as input."<< endl;
               *error = true;
               found = false;
               break;
            }
            wire* inPtr = available->at(j);
            this->inputs.push_back(inPtr);
         }
      }
      if(!found){
         cout << "Input: "<< inputs.at(i) <<" not declared" <<endl;
         *error = true;
         break;
      }
   }
   for(int i = 0; i<outputs.size(); i++){//check that outputs provided exist
      found = false;
      for(int j = 0; j<available->size(); j++){
         if (outputs.at(i).compare(available->at(j)->getName())==0){
            found = true;
            if(available->at(j)->getType() == INPUT ){ //can't use input as output
               cout << "Input: " << available->at(j)->getName() << " used as output."<< endl;
               *error = true;
               found = false;
               break;
            }
            wire* outPtr = available->at(j);
            this->outputs.push_back(outPtr);
         }
      }
      if(!found){
         cout << "Output: "<< outputs.at(i) <<" not declared" <<endl;
         *error = true;
         break;
      }
   }
   if(!found){
      return;
   }
   this->op = op;

   //determine width of datapath component
   this->width = 0;
   if(op == COMP){
      for(int i = 0; i< this->inputs.size(); i++){
         if(this->inputs.at(i)->getWidth() > this->width){
            this->width = this->inputs.at(i)->getWidth();
         }
      }
   }
   else{
      for(int i = 0; i< this->outputs.size(); i++){
         if(this->outputs.at(i)->getWidth() > this->width){
            this->width = this->outputs.at(i)->getWidth();
         }
      }
   }
   return;
}

operation Component::getOp(){
      return this->op;
}
int Component::getWidth(){
      return this->width;
}
string Component::getOpS(){
   switch(this->op){
      case REG: return "REG";
      case ADD: return "ADD";
      case SUB: return "SUB";
      case MUL: return "MUL";
      case COMP:return "COMP";
      case SHR: return "SHR";
      case SHL: return "SHL";
      case MUX: return "MUX";
      default:  return "error";
   }
}
operation parseOp(string in){
   if(in.compare("+") == 0){
      return ADD;
   }
   else if(in.compare("-") == 0){
      return SUB;
   }
   else if(in.compare("*") ==0){
      return MUL;
   }
   else if(in.compare(">") ==0){
      return COMP;
   }
   else if(in.compare("<") ==0){
      return COMP;
   }
   else if(in.compare("==") ==0){
      return COMP;
   }
   else if(in.compare("?") ==0){
      return MUX;
   }
   else if(in.compare(">>") ==0){
      return SHR;
   }
   else if(in.compare("<<") ==0){
      return SHL;
   }
   else{
      return ERROR_OP;
   }
}