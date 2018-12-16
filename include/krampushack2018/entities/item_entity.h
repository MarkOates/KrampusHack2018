#pragma once



#include <krampushack2018/entities/entity_base.h>



class ItemEntity : public EntityBase
{
public:
   ItemEntity(ElementID *parent, ALLEGRO_BITMAP *image, int item_type_num, float x, float y);
};



