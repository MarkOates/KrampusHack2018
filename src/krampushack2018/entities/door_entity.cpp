


#include <krampushack2018/entities/door_entity.h>



DoorEntity::DoorEntity(ElementID *parent, std::string name, int destination_scene, std::string destination_door_name, ALLEGRO_BITMAP *door_img, float x, float y)
   : EntityBase(parent, "door", x, y)
{
   bitmap.bitmap(door_img);
   bitmap.align(0.5, 1.0);
   bitmap.scale(1.5, 1.2);
   place.size = vec2d(80, 5);

   set("door_name", name);
   set("destination_scene", destination_scene);
   set("destination_door_name", destination_door_name);
}



