#include "io.h"
#include <sstream>

using namespace std;
struct tokens: std::ctype<char> 
{
    tokens(): std::ctype<char>(get_table()) {}

    static std::ctype_base::mask const* get_table()
    {
        typedef std::ctype<char> cctype;
        static const cctype::mask *const_rc= cctype::classic_table();

        static cctype::mask rc[cctype::table_size];
        std::memcpy(rc, const_rc, cctype::table_size * sizeof(cctype::mask));

        rc[','] = std::ctype_base::space; 
        rc[' '] = std::ctype_base::space; 
        return &rc[0];
    }
};

vector<string> splitLine(string line){
   stringstream ss(line);
   ss.imbue(locale(locale(), new tokens()));
   istream_iterator<string> begin(ss);
   istream_iterator<string> end;
   vector<string> words(begin, end);
   return words;
}