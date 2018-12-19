


#include <krampushack2018/entities/krampus_entity.hpp>

#include <allegro_flare/user_event_emitter.h>
#include <krampushack2018/factories/entity_factory.hpp>
#include <krampushack2018/music_track_nums.hpp>
#include <krampushack2018/user_events.hpp>
#include <cmath>



KrampusEntity::KrampusEntity(ElementID *parent, SpriteSheet *sprite_sheet, float x, float y)
   : EntityBase(parent, "krampus", x, y)
   , state_is_busy(false)
   , walking_speed(5.0)
   , running_speed(11.0)
   , facing_right(true)
   , _has_weapon(false)
   , _has_stone_of_defiance(false)
   , club_bitmap(nullptr)
   , state(STANDING)
   , sprite_sheet(sprite_sheet)
{
   place.size = vec3d(120, 30, 0);
   bitmap.bitmap(sprite_sheet->get_sprite(18));
   bitmap.align(0.5, 1.0);
   bitmap.scale(2.0, 2.0);
   bitmap.position(place.size.x/2, place.size.y/2);

   club_bitmap.bitmap(sprite_sheet->get_sprite(23));
   club_bitmap.align(0.5, 0.95);

   set("bound_in_world");

   set_state(STANDING, true);
}



KrampusEntity::~KrampusEntity()
{
}



void KrampusEntity::update()
{
   float previous_state_counter = state_counter;
   state_counter += 1.0 / 60.0;
   place += velocity;

   switch(state)
   {
   case MOVING_LEFT:
      {
         float final_velocity = walking_speed;
         if (key_pressed(ALLEGRO_KEY_R)) final_velocity = running_speed;
         velocity.position = vec3d(-final_velocity, 0.0, 0.0);

         float bounce_counter = sin(al_get_time()*36)*0.5 + 0.5;
         bitmap.anchor(0, bounce_counter * -12);
      }
      break;
   case MOVING_RIGHT:
      {
         float final_velocity = walking_speed;
         if (key_pressed(ALLEGRO_KEY_R)) final_velocity = running_speed;
         velocity.position = vec3d(final_velocity, 0.0, 0.0);

         float bounce_counter = sin(al_get_time()*36)*0.5 + 0.5;
         bitmap.anchor(0, bounce_counter * -12);
      }
      break;
   case MOVING_UP:
      {
         float bounce_counter = sin(al_get_time()*36)*0.5 + 0.5;
         bitmap.anchor(0, bounce_counter * -12);
      }
      break;
   case MOVING_DOWN:
      {
         float bounce_counter = sin(al_get_time()*36)*0.5 + 0.5;
         bitmap.anchor(0, bounce_counter * -12);
      }
      break;
   case STANDING:
      break;
   case ATTACKING:
      {
         float scale = 2.0;
         if (state_counter*scale >= 0.4 && previous_state_counter*scale < 0.4)
         {
            bitmap.bitmap(sprite_sheet->get_sprite(20));
            club_bitmap.position(bitmap.w()/2+30, 25);
            club_bitmap.rotation(FULL_ROTATION * 0.05);
         }
         if (state_counter*scale >= 0.5 && previous_state_counter*scale < 0.5)
         {
            bitmap.bitmap(sprite_sheet->get_sprite(21));
            club_bitmap.position(bitmap.w()/2 + 36, bitmap.h()-20);
            club_bitmap.rotation(FULL_ROTATION * 0.25 + 0.1);

            float dh = place.h;
            float dy = place.y;
            float dw = 80;
            float dx = facing_right ? place.position.x + place.size.x : place.position.x - place.size.x;
            if (has_weapon())
            {
               UserEventEmitter::emit_event(PLAY_SOUND_EFFECT, STRONG_PUNCH_SOUND_EFFECT);
               EntityFactory::create_krampus_attack_damage_zone_with_club(get_parent(), dx, dy, dw*2, dh);
            }
            else EntityFactory::create_krampus_attack_damage_zone(get_parent(), dx, dy, dw, dh);
         }
         if (state_counter*scale >= 0.7 && previous_state_counter*scale < 0.7)
         {
            bitmap.bitmap(sprite_sheet->get_sprite(22));
            club_bitmap.position(bitmap.w()/2 + 36, bitmap.h()-20);
            club_bitmap.rotation(FULL_ROTATION * 0.25 - 0.2);
         }
         if (state_counter*scale >= 1.0 && previous_state_counter*scale < 1.0)
         {
            set_state(STANDING, true);
         }
         break;
      }
   case CELEBRATING:
      {
         float previous_state_counter_modded = std::fmod(previous_state_counter, 0.4);
         float state_counter_modded = std::fmod(state_counter, 0.4);
         float scale = 1.0;
         if (state_counter_modded*scale >= 0.1 && previous_state_counter_modded*scale < 0.1) bitmap.bitmap(sprite_sheet->get_sprite(19));
         if (state_counter_modded*scale >= 0.3 && previous_state_counter_modded*scale < 0.3) bitmap.bitmap(sprite_sheet->get_sprite(18));
      }
      break;
   case USING_MAGIC:
      if (state_counter >= 1.6 && previous_state_counter < 1.6) set_state(STANDING, true);
      break;
   default:
      break;
   }
}



void KrampusEntity::draw()
{
   place.start_transform();
   bitmap.start_transform();
   bitmap.draw_raw();
   if (has_weapon()) club_bitmap.draw();
   bitmap.restore_transform();
   place.restore_transform();
}



void KrampusEntity::attack()
{
   set_state(ATTACKING);
}



void KrampusEntity::stand_still()
{
   set_state(STANDING);
}



void KrampusEntity::move_up()
{
   set_state(MOVING_UP);
}



void KrampusEntity::move_down()
{
   set_state(MOVING_DOWN);
}



void KrampusEntity::move_left()
{
   set_state(MOVING_LEFT);
}



void KrampusEntity::move_right()
{
   set_state(MOVING_RIGHT);
}



void KrampusEntity::run_left()
{
   set_state(MOVING_LEFT);
}



void KrampusEntity::run_right()
{
   set_state(MOVING_RIGHT);
}



void KrampusEntity::face_left()
{
   facing_right = false;
   bitmap.flip(true, false);
}



void KrampusEntity::face_right()
{
   facing_right = true;
   bitmap.flip(false, false);
}



void KrampusEntity::celebrate()
{
   set_state(CELEBRATING);
}



void KrampusEntity::use_stone_of_defiance()
{
   if (_has_stone_of_defiance) set_state(USING_MAGIC);
}



bool KrampusEntity::set_state(state_t new_state, bool override_if_busy)
{
   if (override_if_busy) state_is_busy = false;

   if (state_is_busy) return false;

   state_counter = 0.0;
   state = new_state;

   switch(new_state)
   {
   case MOVING_UP:
      bitmap.bitmap(sprite_sheet->get_sprite(18));
      velocity.position = vec3d(0.0, -walking_speed/2, 0.0);
      break;
   case MOVING_DOWN:
      bitmap.bitmap(sprite_sheet->get_sprite(18));
      velocity.position = vec3d(0.0, walking_speed/2, 0.0);
      break;
   case MOVING_LEFT:
      bitmap.bitmap(sprite_sheet->get_sprite(18));
      face_left();
      velocity.position = vec3d(-walking_speed, 0.0, 0.0);
      break;
   case MOVING_RIGHT:
      bitmap.bitmap(sprite_sheet->get_sprite(18));
      face_right();
      velocity.position = vec3d(walking_speed, 0.0, 0.0);
      break;
   case STANDING:
      bitmap.anchor(0, 0);
      bitmap.bitmap(sprite_sheet->get_sprite(18));
      velocity.position = vec3d(0.0, 0.0, 0.0);
      club_bitmap.position(bitmap.w()/2 + 36, bitmap.h()-20);
      club_bitmap.rotation(FULL_ROTATION * 0.25 - 0.2);
      break;
   case ATTACKING:
      bitmap.anchor(0, 0);
      state_is_busy = true;
      bitmap.bitmap(sprite_sheet->get_sprite(19));
      velocity.position = vec3d(0.0, 0.0, 0.0);
      club_bitmap.position(bitmap.w()/2, 10);
      club_bitmap.rotation(FULL_ROTATION * -0.2);
      break;
   case CELEBRATING:
      bitmap.anchor(0, 0);
      bitmap.bitmap(sprite_sheet->get_sprite(19));
      velocity.position = vec3d(0.0, 0.0, 0.0);
      break;
   case USING_MAGIC:
      bitmap.anchor(0, 0);
      state_is_busy = true;
      bitmap.bitmap(sprite_sheet->get_sprite(19));
      velocity.position = vec3d(0.0, 0.0, 0.0);
      UserEventEmitter::emit_event(USE_STONE_OF_DEFIANCE_EVENT);
      break;
   default:
      return false;
      break;
   }

   return true;
}



void KrampusEntity::get_weapon()
{
   _has_weapon = true;
}



void KrampusEntity::get_stone_of_defiance()
{
   _has_stone_of_defiance = true;
}



bool KrampusEntity::is_idle()
{
   return state == STANDING;
}



bool KrampusEntity::has_weapon()
{
   return _has_weapon;
}



