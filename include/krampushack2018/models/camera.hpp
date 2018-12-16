#pragma once



#include <allegro_flare/display.h>
#include <allegro_flare/motion.h>
#include <krampushack2018/entities/entity_base.hpp>



class Camera
{
private:
   placement2d place;
   EntityBase *target;
   ALLEGRO_COLOR overlay_color;
   Motion motion;

public:
   Camera(Display *display, EntityBase *target);

   void set_target(EntityBase *new_target=nullptr);

   void update(float max_x);
   void start_transform();
   void restore_transform();
   void set_overlay_color(ALLEGRO_COLOR new_overlay_color);
   void fade_to_black(float duration=0.4);
   void fade_to_clear(float duration=0.4);
   void set_zoom(float scale=1.0);
   void zoom_to(float scale=1.0, float duration=0.4);
   void tilt_to(float tilt, float duration=0.4);

   void draw_overlay();
};



