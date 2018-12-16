


#include <krampushack2018/models/camera.h>



Camera::Camera(Display *display, EntityBase *target)
   : place(0, 0, display->width(), display->height())
   , target(target)
   , overlay_color(color::transparent)
   , motion()
{}



void Camera::set_target(EntityBase *new_target)
{
   target = new_target;
}



void Camera::update(float max_x)
{
   motion.update(al_get_time());

   if (target) place.x = target->place.x;
   place.y = place.h/2;

   if (place.x < place.w/2) place.x = place.w/2;
   if (place.x > max_x-place.w/2) place.x = max_x-place.w/2;
}



void Camera::start_transform()
{
   place.start_reverse_transform();
}



void Camera::restore_transform()
{
   place.restore_transform();
}



void Camera::draw_overlay()
{
   al_draw_filled_rectangle(0, 0, place.w, place.h, overlay_color);
}



void Camera::set_overlay_color(ALLEGRO_COLOR new_overlay_color)
{
   overlay_color = new_overlay_color;

   motion.clear_animations_on(&overlay_color.r);
   motion.clear_animations_on(&overlay_color.g);
   motion.clear_animations_on(&overlay_color.b);
   motion.clear_animations_on(&overlay_color.a);
}



void Camera::fade_to_black(float duration)
{
   motion.cmove_to(&overlay_color.r, 0, duration);
   motion.cmove_to(&overlay_color.g, 0, duration);
   motion.cmove_to(&overlay_color.b, 0, duration);
   motion.cmove_to(&overlay_color.a, 1.0, duration);
}



void Camera::fade_to_clear(float duration)
{
   motion.cmove_to(&overlay_color.r, 0, duration);
   motion.cmove_to(&overlay_color.g, 0, duration);
   motion.cmove_to(&overlay_color.b, 0, duration);
   motion.cmove_to(&overlay_color.a, 0, duration);
}



void Camera::set_zoom(float scale)
{
   place.scale.x = scale;
   place.scale.y = scale;
}



void Camera::zoom_to(float scale, float duration)
{
   motion.cmove_to(&place.scale.x, scale, duration);
   motion.cmove_to(&place.scale.y, scale, duration);
}



void Camera::tilt_to(float tilt, float duration)
{
   motion.cmove_to(&place.rotation, tilt, duration);
}



