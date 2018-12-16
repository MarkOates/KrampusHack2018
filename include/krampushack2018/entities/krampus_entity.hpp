#pragma once



#include <krampushack2018/entities/entity_base.hpp>
#include <krampushack2018/sprite_sheet.hpp>



class KrampusEntity : public EntityBase
{
public:
   enum state_t
   {
      WALKING_UP,
      WALKING_DOWN,
      WALKING_RIGHT,
      WALKING_LEFT,
      STANDING,
      CELEBRATING,
      ATTACKING,
      USING_MAGIC,
      DEAD
   };
   int state;
   float state_counter;
   bool state_is_busy;
   int walking_speed;
   bool facing_right;
   bool _has_weapon;
   bool _has_stone_of_defiance;
   BitmapObject club_bitmap;
   SpriteSheet *sprite_sheet;

   bool set_state(state_t new_state, bool override_if_busy=false);

public:
   KrampusEntity(ElementID *parent, SpriteSheet *sprite_sheet, float x, float y);
   virtual ~KrampusEntity();

   void update() override;
   void draw() override;

   void attack();
   void stand_still();
   void celebrate();
   void walk_up();
   void walk_down();
   void walk_left();
   void walk_right();
   void face_left();
   void face_right();
   void use_stone_of_defiance();

   void get_weapon();
   void get_stone_of_defiance();

   bool is_idle();
   bool has_weapon();
};



