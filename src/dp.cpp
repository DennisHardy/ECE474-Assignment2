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
      case COMP:
         inputs.push_back(words.at(2));
         inputs.push_back(words.at(4));
         outputs.resize(3);
         if(words.at(3).compare(">") == 0){
            outputs.at(0) = words.at(0);
         }
         else if(words.at(3).compare("<") == 0){
            outputs.at(1) = words.at(0);
         }
         else if(words.at(3).compare("==") == 0){
            outputs.at(2) = words.at(0);
         }
         break;
      case ADD:
      case SUB:
      case MUL:
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
      Component *tempComponent = new Component(inputs, outputs, op, available, this->components.size(), &error);
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
      if(addMe->getOp() == COMP){
         for(int i = 0; i < this->components.size(); i++){
            if((this->components.at(i)->getInput(1).compare(addMe->getInput(1)) == 0) &&
               (this->components.at(i)->getInput(2).compare(addMe->getInput(2)) == 0)){
                  cout << "Two comparators with same inputs FIXME:combine";
                  if((this->components.at(i)->getOutputS(0).compare("") == 0) &&
                     (addMe->getOutputS(0).compare("") !=0)){
                        this->components.at(i)->setOutput(0, addMe->getOutput(0));
                     }
                  if((this->components.at(i)->getOutputS(1).compare("") == 0) &&
                     (addMe->getOutputS(1).compare("") !=0)){
                        this->components.at(i)->setOutput(1, addMe->getOutput(1));
                     }
                  if((this->components.at(i)->getOutputS(2).compare("") == 0) &&
                     (addMe->getOutputS(2).compare("") !=0)){
                        this->components.at(i)->setOutput(2, addMe->getOutput(2));
                     }
                  return true;
            }
         }
      }
      this->components.push_back(addMe);
      return true;
}

Component::Component( vector<string> inputs, vector<string> outputs, operation op, Wires *available, int id, bool* error){
   
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
   this->id = id;
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
int Component::getId(){
      return this->id;
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

string Component::getInput(int i){
   if(i >= this->inputs.size() || i < 0){
      return "error";
   }
   else{
      return this->inputs.at(i)->getName();
   }
}
string Component::getOutputS(int i){
   if(i >= this->outputs.size() || i < 0){
      return "error";
   }
   else{
      return this->outputs.at(i)->getName();
   }
}
wire* Component::getOutput(int i){
   if(i >= this->outputs.size() || i < 0){
      return nullptr;
   }
   else{
      return this->outputs.at(i);
   }
}
void Component::setOutput(int i, wire* out){
   if(i >= this->outputs.size() || i < 0){
      return;
   }
   else{
      this->outputs.at(i) = out;
   }
}
string Component::print(){
   stringstream out;
   switch(this->op){
      case REG: 
         out << "REG";
         break;
      case COMP:
         out << this->getOpS();
         out << " #(" << this->getWidth() << ") ";
         out << this->getOpS() << this->getId() <<"(" << this->inputs.at(0)->getName() << ", " << this->inputs.at(1)->getName() << ", ";
         out << this->outputs.at(0)->getName() << ", " << this->outputs.at(1)->getName() << ", " << this->outputs.at(2)->getName() << ");" << endl;
         break;
      case ADD: 
      case SUB: 
      case MUL: 
      case SHR: 
      case SHL: 
         out << this->getOpS();
         out << " #(" << this->getWidth() << ") ";
         out << this->getOpS() << this->getId() <<"(" << this->inputs.at(0)->getName() << ", " << this->inputs.at(1)->getName() << ", ";
         out << this->outputs.at(0)->getName() << ");" << endl;
         break;
      case MUX: 
         out << "MUX2x1" << endl;
         break;
      default:  
         out << "error" << endl;
         break;
   }
   return out.str();
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