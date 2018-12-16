#pragma once



#include <string>
#include <vector>



class KidNameGenerator
{
private:
   std::vector<std::string> boy_names;
   std::vector<std::string> girl_names;
   int next_boy_name_index;
   int next_girl_name_index;

public:
   KidNameGenerator();

   std::string get_boy_name();
   std::string get_girl_name();
};



