#include "io.h"
#include <sstream>
#include <cctype>
#include <istream>

#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

vector<string> splitLine(string line){
	vector<string> out;

	stringstream stream;
	stream.str(line);
	
	while(stream){
      string temp;
		stream >> temp;
      if(temp.size()>0){
         char last = temp[temp.length()-1];
         if(last == ','){
            temp = temp.substr(0, temp.size()-1);
         }
         out.push_back(temp);
      }
	}
	
	return out;
}
