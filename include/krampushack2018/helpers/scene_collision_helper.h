#pragma once



#include <krampushack2018/models/scene.h>
#include <krampushack2018/helpers/scene_collection_helper.h>



class SceneCollisionHelper
{
private:
   Scene *scene;
   SceneCollectionHelper collections;

   void update_entities();
   void limit_sprites_to_world_bounds();
   void check_damage_zones_on_children();
   void check_krampus_on_door();
   void check_krampus_on_items();

public:
   SceneCollisionHelper(Scene *scene);

   void resolve_collisions();
};



