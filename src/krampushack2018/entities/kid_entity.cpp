


#include <krampushack2018/entities/kid_entity.hpp>

#include <allegro_flare/user_event_emitter.h>
#include <cmath>
#include <krampushack2018/music_track_nums.hpp>
#include <krampushack2018/user_events.hpp>



#define IDENTITY_REVEAL_MAX 999.9



KidEntity::KidEntity(ElementID *parent, SpriteSheet *sprite_sheet, Shader *flat_color_shader, float x, float y, std::string name, behavior_t behavior, int sprite_index, int identity_sprite_index)
   : EntityBase(parent, "kid", x, y)
   , behavior(behavior)
   , name(name)
   , walk_speed(1.5)
   , state(STATE_STANDING_STILL)
   , flat_color_shader(flat_color_shader)
   , identity_reveal_counter(IDENTITY_REVEAL_MAX)
   , kid_bitmap(sprite_sheet->get_sprite(sprite_index))
   , identity_bitmap(sprite_sheet->get_sprite(identity_sprite_index))
{
   place.size = vec2d(60, 30);

   if (sprite_index < 0) sprite_index = random_int(0, 16);
   bitmap.bitmap(kid_bitmap);
   bitmap.align(0.5, 1.0);
   bitmap.scale(2.0, 2.0);

   set("bound_in_world");
}



KidEntity::~KidEntity()
{
}



void KidEntity::reveal_behavior()
{
   identity_reveal_counter = 0.0;
}



void KidEntity::update()
{
   if (identity_reveal_counter < IDENTITY_REVEAL_MAX)
      identity_reveal_counter += 1.0 / 60.0;

   place += velocity;

   switch(state)
   {
   case STATE_TAKING_HIT:
      break;
   default:
      break;
   }
}



void KidEntity::draw()
{
   ALLEGRO_COLOR identity_color = get_identity_color();
   float tint_intensity = get_identity_tint_intensity();

   flat_color_shader->use();

   flat_color_shader->set_vec3("tint", identity_color.r, identity_color.g, identity_color.b);
   flat_color_shader->set_float("tint_intensity", tint_intensity);

   place.start_transform();
   bitmap.position(place.size.x/2, place.size.y/2);
      bitmap.opacity(1.0);
      bitmap.bitmap(kid_bitmap);
      bitmap.draw();

   flat_color_shader->stop();

   bitmap.bitmap(identity_bitmap);
      bitmap.opacity(tint_intensity);
      bitmap.draw();

   place.restore_transform();

}



void KidEntity::stand_still()
{
   set_state(STATE_STANDING_STILL);
}



void KidEntity::walk_up()
{
   set_state(STATE_WALKING_UP);
}



void KidEntity::walk_down()
{
   set_state(STATE_WALKING_DOWN);
}



void KidEntity::walk_left()
{
   set_state(STATE_WALKING_UP);
}



void KidEntity::walk_right()
{
   set_state(STATE_WALKING_RIGHT);
}



void KidEntity::take_hit()
{
   set_state(STATE_TAKING_HIT);
}



void KidEntity::set_state(state_t new_state)
{
   state = new_state;

   switch (state)
   {
   case STATE_STANDING_STILL:
      velocity.position = vec2d(0.0, 0.0);
      break;
   case STATE_WALKING_UP:
      velocity.position = vec2d(0.0, -walk_speed/2);
      break;
   case STATE_WALKING_DOWN:
      velocity.position = vec2d(0.0, walk_speed/2);
      break;
   case STATE_WALKING_LEFT:
      velocity.position = vec2d(-walk_speed, 0.0);
      break;
   case STATE_WALKING_RIGHT:
      velocity.position = vec2d(walk_speed, 0.0);
      break;
   case STATE_TAKING_HIT:
      velocity.position = vec2d(0.0, 0.0);
      UserEventEmitter::emit_event(PLAY_SOUND_EFFECT, HURT_SOUND_EFFECT);
      reveal_behavior();
      break;
   }
}



ALLEGRO_COLOR KidEntity::get_identity_color()
{
   ALLEGRO_COLOR identity_color;

   switch(behavior)
   {
   case BEHAVIOR_ADULT:
      identity_color = color::gray;
      break;
   case BEHAVIOR_NAUGHTY:
      identity_color = color::firebrick;
      break;
   case BEHAVIOR_NICE:
      identity_color = color::white;
      break;
   }

   return identity_color;
}



float KidEntity::get_identity_tint_intensity()
{
   float strobe_speed = 3.0;
   float identiy_reveal_duration = 4.0;

   switch (behavior)
   {
   case BEHAVIOR_ADULT:
      return 1.0 - std::min(identity_reveal_counter*(1.0/identiy_reveal_duration), 1.0);
      break;
   case BEHAVIOR_NAUGHTY:
      strobe_speed = 3.0;
      break;
   case BEHAVIOR_NICE:
      strobe_speed = 1.0;
      break;
   }

   float normalized_oscilation = sin(al_get_time() * strobe_speed*4) * 0.5 + 0.5;
   float tint_intensity = 1.0 - std::min(identity_reveal_counter*(1.0/identiy_reveal_duration), 1.0);

   return normalized_oscilation * interpolator::fast_in(tint_intensity);
}



std::string KidEntity::get_name()
{
   return name;
}



