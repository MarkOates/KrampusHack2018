


#include <krampushack2018/entities/background_entity.h>



BackgroundEntity::BackgroundEntity(ElementID *parent, ALLEGRO_BITMAP *al_bitmap, float x, float y)
   : EntityBase(parent, "background", x, y)
{
   place.align = vec2d(0.0, 0.0);
   bitmap.bitmap(al_bitmap);
}



BackgroundEntity::~BackgroundEntity()
{}



void BackgroundEntity::draw()
{
   place.start_transform();
   bitmap.draw();
   place.restore_transform();
}



