


#include <krampushack2018/models/naughty_list.hpp>
#include <allegro_flare/useful.h>



NaughtyList::Kid::Kid(std::string name, int sprite_index, int scene_id, behavior_t behavior)
   : name(name)
   , scene_id(scene_id)
   , sprite_index(sprite_index)
   , behavior(behavior)
   , killed(false)
{}



behavior_t NaughtyList::Kid::get_behavior()
{
   return behavior;
}



std::string NaughtyList::Kid::get_name()
{
   return name;
}



int NaughtyList::Kid::get_sprite_index()
{
   return sprite_index;
}



bool NaughtyList::Kid::is_naughty()
{
   return behavior == BEHAVIOR_NAUGHTY;
}



bool NaughtyList::Kid::is_nice()
{
   return behavior == BEHAVIOR_NICE;
}



bool NaughtyList::Kid::is_adult()
{
   return behavior == BEHAVIOR_ADULT;
}



bool NaughtyList::Kid::is_alive()
{
   return !killed;
}



NaughtyList::Kid NaughtyList::_build_kid(int scene_id)
{
   static int behavior_distribution = -1;
   behavior_distribution += 1;
   behavior_distribution = behavior_distribution % 5;

   static bool boy_girl = true;
   boy_girl = !boy_girl;

   std::string name = "";
   int sprite_index = -1;
   behavior_t behavior = BEHAVIOR_NAUGHTY;
   std::vector<behavior_t> non_adult_behaviors = { BEHAVIOR_NAUGHTY, BEHAVIOR_NICE };

   switch(behavior_distribution)
   {
      case 0:
      case 2:
         behavior = BEHAVIOR_NAUGHTY;
         break;
      case 1:
      case 3:
         behavior = BEHAVIOR_NICE;
         break;
      case 4:
         sprite_index = _get_random_sprite_for_adult();
         name = (boy_girl) ? kid_name_generator.get_boy_name() : kid_name_generator.get_girl_name();
         behavior = BEHAVIOR_ADULT;
         break;
   }

   if (behavior != BEHAVIOR_ADULT)
   {
      if (boy_girl)
      {
         name = kid_name_generator.get_boy_name();
         sprite_index = _get_random_sprite_for_boy();
      }
      else
      {
         name = kid_name_generator.get_girl_name();
         sprite_index = _get_random_sprite_for_girl();
      }
   }

   return Kid(name, sprite_index, scene_id, behavior);
}



int NaughtyList::_get_random_sprite_for_boy()
{
   std::vector<int> boy_sprites = {2, 4, 8, 9, 15, 16};
   return random_element<int>(boy_sprites);
}



int NaughtyList::_get_random_sprite_for_girl()
{
   std::vector<int> girl_sprites = {3, 5, 6, 11, 14, 17};
   return random_element<int>(girl_sprites);
}



int NaughtyList::_get_random_sprite_for_adult()
{
   std::vector<int> girl_sprites = {0, 1, 7, 10, 12, 13};
   return random_element<int>(girl_sprites);
}



NaughtyList::NaughtyList()
   : kids()
   , kid_name_generator()
{
   std::vector<std::pair<int, int>> scene_kids =
   {
   // {scene_id, num_of_kids}
      {1, 20},
      {2, 3},
      {3, 6},
      {5, 1},
      {6, 1},
      {7, 25}
   };

   // generate the kids for each scene
   for (unsigned i=0; i<scene_kids.size(); i++)
   {
      int scene_id = scene_kids[i].first;
      int num_kids = scene_kids[i].second;

      for (unsigned i=0; i<num_kids; i++)
         kids.push_back(_build_kid(scene_id));
   }
}



std::vector<NaughtyList::Kid> NaughtyList::get_alive_kids_for_scene(int scene)
{
   std::vector<Kid> results;

   for (auto &kid : kids)
      if (kid.is_alive() && kid.scene_id == scene) results.push_back(kid);

   return results;
}



int NaughtyList::get_num_alive_naughty_kids()
{
   int count = 0;

   for (auto &kid : kids)
      if (kid.is_alive() && kid.behavior == BEHAVIOR_NAUGHTY) count++;

   return count;
}



int NaughtyList::get_num_alive_nice_kids()
{
   int count = 0;

   for (auto &kid : kids)
      if (kid.is_alive() && kid.behavior == BEHAVIOR_NICE) count++;

   return count;
}



int NaughtyList::get_num_alive_adults()
{
   int count = 0;

   for (auto &kid : kids)
      if (kid.is_alive() && kid.behavior == BEHAVIOR_ADULT) count++;

   return count;
}



int NaughtyList::get_num_total_naughty_kids()
{
   int count = 0;

   for (auto &kid : kids) if (kid.behavior == BEHAVIOR_NAUGHTY) count++;

   return count;
}



int NaughtyList::get_num_total_nice_kids()
{
   int count = 0;

   for (auto &kid : kids) if (kid.behavior == BEHAVIOR_NICE) count++;

   return count;
}



int NaughtyList::get_num_total_adults()
{
   int count = 0;

   for (auto &kid : kids) if (kid.behavior == BEHAVIOR_ADULT) count++;

   return count;
}



bool NaughtyList::are_all_naughty_kids_killed()
{
   if (get_num_alive_naughty_kids() == 0) return true;
   return false;
}



bool NaughtyList::are_any_nice_kids_killed()
{
   if (get_num_alive_nice_kids() < get_num_total_nice_kids()) return true;
   return false;
}



bool NaughtyList::kill_kid_by_name(std::string name)
{
   Kid *found_kid = nullptr;

   // find the kid
   for (auto &kid : kids)
      if (kid.name == name)
      {
         found_kid = &kid;
         break;
      }

   if (found_kid && found_kid->is_alive())
   {
      found_kid->killed = true;
      return true;
   }

   return false;
}



