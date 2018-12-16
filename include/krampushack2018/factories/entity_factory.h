#pragma once



#include <krampushack2018/sprite_sheet.h>

#include <allegro_flare/shader.h>
#include <krampushack2018/entities/entity_base.h>
#include <krampushack2018/entities/kid_entity.h>



class EntityFactory
{
private:
   SpriteSheet character_sprite_sheet;
   Shader flat_color_shader;
   ALLEGRO_BITMAP *background1;
   ALLEGRO_BITMAP *background2;
   ALLEGRO_BITMAP *background3;
   ALLEGRO_BITMAP *background4;
   ALLEGRO_BITMAP *background5;
   ALLEGRO_BITMAP *background6;
   ALLEGRO_BITMAP *door1;
   ALLEGRO_BITMAP *door2;
   ALLEGRO_BITMAP *door3;
   ALLEGRO_BITMAP *door4;
   ALLEGRO_BITMAP *door5;
   ALLEGRO_BITMAP *door6;
   ALLEGRO_BITMAP *club_item;
   static EntityFactory *instance;
   static EntityFactory *get_instance();

   EntityFactory();
   ~EntityFactory();

public:
   static EntityBase *create_random_kid(ElementID *parent, float x, float y);
   static KidEntity *create_named_kid(ElementID *parent, std::string name, behavior_t behavior, int sprite_index, float x, float y);
   static EntityBase *create_krampus(ElementID *parent, float x, float y);
   static EntityBase *create_krampus_attack_damage_zone(ElementID *parent, float x, float y, float w, float h);
   static EntityBase *create_krampus_attack_damage_zone_with_club(ElementID *parent, float x, float y, float w, float h);
   static EntityBase *create_door1(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);
   static EntityBase *create_door2(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);
   static EntityBase *create_door3(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);
   static EntityBase *create_door4(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);
   static EntityBase *create_door5(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);
   static EntityBase *create_door6(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);
   static EntityBase *create_club_item(ElementID *parent, float x, float y);
   static EntityBase *create_stone_of_defiance_item(ElementID *parent, float x, float y);
   static EntityBase *create_naughty_list_item(ElementID *parent, float x, float y);
   static EntityBase *create_key_item(ElementID *parent, float x, float y);

   static EntityBase *create_background1(ElementID *parent, float x, float y);
   static EntityBase *create_background2(ElementID *parent, float x, float y);
   static EntityBase *create_background3(ElementID *parent, float x, float y);
   static EntityBase *create_background4(ElementID *parent, float x, float y);
   static EntityBase *create_background5(ElementID *parent, float x, float y);
   static EntityBase *create_background6(ElementID *parent, float x, float y);
};



