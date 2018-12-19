#pragma once



#include <krampushack2018/entities/entity_base.hpp>



class BackgroundEntity : public EntityBase
{
public:
   BackgroundEntity(ElementID *parent, ALLEGRO_BITMAP *al_bitmap, float x, float y);
   ~BackgroundEntity();

   void draw() override;
};



