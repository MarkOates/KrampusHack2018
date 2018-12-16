#pragma once



#include <krampushack2018/entities/entity_base.h>

#include <allegro_flare/shader.h>
#include <krampushack2018/sprite_sheet.h>



enum behavior_t
{
   BEHAVIOR_ADULT,
   BEHAVIOR_NAUGHTY,
   BEHAVIOR_NICE
};



class KidEntity : public EntityBase
{
private:
   enum state_t
   {
      STATE_STANDING_STILL,
      STATE_TAKING_HIT,
      STATE_WALKING_UP,
      STATE_WALKING_DOWN,
      STATE_WALKING_LEFT,
      STATE_WALKING_RIGHT
   };

   behavior_t behavior;
   std::string name;
   float walk_speed;
   state_t state;
   Shader *flat_color_shader;
   float identity_reveal_counter;
   ALLEGRO_BITMAP *kid_bitmap, *identity_bitmap;
   ALLEGRO_COLOR get_identity_color();
   float get_identity_tint_intensity();

   void set_state(state_t);

   friend class AIKidController;

public:
   KidEntity(ElementID *parent, SpriteSheet *sprite_sheet, Shader *flat_color_shader, float x, float y, std::string name, behavior_t behavior, int sprite_index, int identity_sprite_index);
   virtual ~KidEntity();

   void update() override;
   void draw() override;

   void stand_still();
   void walk_up();
   void walk_down();
   void walk_left();
   void walk_right();
   void take_hit();

   void reveal_behavior();
   std::string get_name();
};



