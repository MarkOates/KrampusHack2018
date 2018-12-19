


#include <krampushack2018/entities/item_entity.hpp>



ItemEntity::ItemEntity(ElementID *parent, ALLEGRO_BITMAP *bmp, int item_type_int, float x, float y)
   : EntityBase(parent, "item", x, y)
{
   place.size = vec3d(80, 20, 0);
   bitmap.bitmap(bmp);
   bitmap.align(0.5, 1.0);
   bitmap.scale(2.0, 2.0);

   set("item_type_int", item_type_int);
}



