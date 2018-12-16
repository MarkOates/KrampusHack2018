#pragma once



#include <krampushack2018/entities/entity_base.h>



class DoorEntity : public EntityBase
{
public:
   DoorEntity(ElementID *parent, std::string name, int destination_scene, std::string destination_door_name, ALLEGRO_BITMAP *door_img, float x, float y);
};



