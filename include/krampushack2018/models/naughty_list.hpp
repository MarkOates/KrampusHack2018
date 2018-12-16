#pragma once



#include <krampushack2018/entities/kid_entity.hpp>
#include <krampushack2018/generators/kid_name_generator.hpp>
#include <string>
#include <vector>



class NaughtyList
{
public:
   class Kid
   {
   private:
      std::string name;
      int sprite_index;
      int scene_id;
      behavior_t behavior;
      bool killed;

   public:
      Kid(std::string name, int sprite_index, int scene_id, behavior_t behavoir);
      behavior_t get_behavior();
      std::string get_name();
      int get_sprite_index();
      bool is_naughty();
      bool is_nice();
      bool is_adult();
      bool is_alive();

      friend class NaughtyList;
   };

private:
   std::vector<Kid> kids;

   KidNameGenerator kid_name_generator;
   Kid _build_kid(int scene_id);
   int _get_random_sprite_for_boy();
   int _get_random_sprite_for_girl();
   int _get_random_sprite_for_adult();

public:
   NaughtyList();

   std::vector<Kid> get_alive_kids_for_scene(int scene);

   int get_num_alive_naughty_kids();
   int get_num_alive_nice_kids();
   int get_num_alive_adults();
   int get_num_total_naughty_kids();
   int get_num_total_nice_kids();
   int get_num_total_adults();

   bool are_all_naughty_kids_killed();
   bool are_any_nice_kids_killed();

   bool kill_kid_by_name(std::string name);
};



