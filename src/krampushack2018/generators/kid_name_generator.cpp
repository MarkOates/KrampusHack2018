


#include <krampushack2018/generators/kid_name_generator.h>

#include <algorithm>



KidNameGenerator::KidNameGenerator()
   : boy_names(
      { "Adam"
      , "Billy"
      , "Bruce"
      , "Chris"
      , "Christopher"
      , "David"
      , "Donald"
      , "Donny"
      , "Frankie"
      , "George"
      , "Gorby"
      , "Greg"
      , "Hamilton"
      , "Homer"
      , "Hugo"
      , "Jack"
      , "James"
      , "Jeremy"
      , "Johnathan"
      , "Johnny"
      , "Jules"
      , "Kirk"
      , "Luther"
      , "Matt"
      , "Michael"
      , "Nick"
      , "Norman"
      , "Patrick"
      , "Paul"
      , "Peter"
      , "Richard"
      , "Robert"
      , "Sam"
      , "Thomas"
      , "Tim"
      , "Timmy"
      , "Toby"
      , "Tommy"
      , "Walter"
      , "Edward"
     })
   , girl_names(
      { "Abigail"
      , "Annabelle"
      , "Audrey"
      , "Beth"
      , "Caren"
      , "Caroline"
      , "Christine"
      , "Claire"
      , "Doris"
      , "Elise"
      , "Elizabeth"
      , "Ella"
      , "Emily"
      , "Erica"
      , "Florence"
      , "Gloria"
      , "Grace"
      , "Hannah"
      , "Hellen"
      , "Ingrid"
      , "Jill"
      , "Kelly"
      , "Lily"
      , "Lisa"
      , "Madelyn"
      , "Mary"
      , "Natalie"
      , "Nichole"
      , "Noel"
      , "Olga"
      , "Penelope"
      , "Penny"
      , "Sarah"
      , "Scarlett"
      , "Sally"
      , "Stacy"
      , "Tanya"
      , "Tara"
      , "Vivian"
      , "Wendy"
     })
   , next_boy_name_index(0)
   , next_girl_name_index(0)
{
   std::random_shuffle(boy_names.begin(), boy_names.end());
   std::random_shuffle(girl_names.begin(), girl_names.end());
}



std::string KidNameGenerator::get_boy_name()
{
   if (next_boy_name_index >= boy_names.size()) return "";

   return boy_names[next_boy_name_index++];
}



std::string KidNameGenerator::get_girl_name()
{
   if (next_girl_name_index >= girl_names.size()) return "";

   return girl_names[next_girl_name_index++];
}



