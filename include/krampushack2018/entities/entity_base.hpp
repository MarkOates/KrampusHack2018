#pragma once



#include <krampushack2018/models/Bitmap3D.hpp>
#include <allegro_flare/placement3d.h>
#include <allegro_flare/element_id.h>



class EntityBase : public ElementID
{
public:
   placement3d place;
   placement3d velocity;
   Bitmap3D bitmap;

   EntityBase(ElementID *parent, std::string type, float x, float y);
   virtual ~EntityBase();

   virtual void update();
   virtual void draw();

   void flag_for_deletion();
   bool collides(const EntityBase &other);
};



