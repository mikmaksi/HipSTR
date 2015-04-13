#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>

#include "stringops.h"

void split_by_delim(const std::string &s, char delim, 
		    std::vector<std::string>& substrings){
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim))
    substrings.push_back(item);
}


std::string uppercase(std::string str){
  std::stringstream res;
  for (int i = 0; i < str.size(); i++)
    res << (char)toupper(str[i]);
  return res.str();
}
