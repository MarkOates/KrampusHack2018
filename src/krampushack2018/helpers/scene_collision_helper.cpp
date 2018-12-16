


#include <krampushack2018/helpers/scene_collision_helper.hpp>

#include <allegro_flare/user_event_emitter.h>
#include <krampushack2018/entities/damage_zone_entity.hpp>
#include <krampushack2018/entities/entity_base.hpp>
#include <krampushack2018/entities/kid_entity.hpp>
#include <krampushack2018/entities/krampus_entity.hpp>
#include <krampushack2018/helpers/scene_collection_helper.hpp>
#include <krampushack2018/user_events.hpp>



SceneCollisionHelper::SceneCollisionHelper(Scene *scene)
   : scene(scene)
   , collections(scene)
{}



void SceneCollisionHelper::resolve_collisions()
{
   if (!scene) return;

   update_entities();
   limit_sprites_to_world_bounds();
   check_damage_zones_on_children();
   check_krampus_on_door();
   check_krampus_on_items();
};



void SceneCollisionHelper::update_entities()
{
   for (auto &entity : collections.get_all_entities())
      entity->update();
}



void SceneCollisionHelper::limit_sprites_to_world_bounds()
{
   float min_y, max_y;
   scene->get_y_bounds(&min_y, &max_y);
   float max_x = scene->get_width();

   for (auto &entity : collections.get_entities_bound_in_world())
   {
      if (entity->place.y < min_y) entity->place.y = min_y;
      if (entity->place.y > max_y) entity->place.y = max_y;
      if (entity->place.x < 0) entity->place.x = 0;
      if (entity->place.x > max_x) entity->place.x = max_x;
   }
}



void SceneCollisionHelper::check_damage_zones_on_children()
{
   std::vector<KidEntity *> kids = collections.get_kids();

   // damage zone <-> kid collisions
   for (auto &damage_zone : collections.get_damage_zones())
   {
      for (auto &kid : kids)
      {
         if (damage_zone->is_dealing_damage() && damage_zone->collides(*kid))
         {
            if (damage_zone->is_krampus_damage_zone()) kid->take_hit();
            else if (damage_zone->is_krampus_damage_zone_with_club()) kid->flag_for_deletion();
         }
      }
   }
}



void SceneCollisionHelper::check_krampus_on_door()
{
   KrampusEntity *krampus = collections.get_krampus();
   for (auto &door : collections.get_doors())
   {
      if (door->place.collide(krampus->place.x, krampus->place.y))
      {
         int destination_scene = door->get_as_int("destination_scene");
         std::string destination_door_name = door->get_as_string("destination_door_name");
         char dest_door_char = destination_door_name.size() == 1 ? destination_door_name[0] : '!';

         UserEventEmitter::emit_event(ENTER_DOOR_EVENT, destination_scene, dest_door_char);
      }
   }
}



void SceneCollisionHelper::check_krampus_on_items()
{
   KrampusEntity *krampus = collections.get_krampus();
   for (auto &item : collections.get_items())
   {
      if (item->place.collide(krampus->place.x, krampus->place.y, 20, 10, 20, 10))
      {
         int item_type_int = item->get_as_int("item_type_int");
         UserEventEmitter::emit_event(COLLECT_ITEM_EVENT, item_type_int);
         item->flag_for_deletion();
      }
   }
}



