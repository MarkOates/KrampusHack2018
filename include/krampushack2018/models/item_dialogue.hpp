#pragma once



#include <allegro_flare/objects/bitmap_object.h>
#include <krampushack2018/models/Bitmap3D.hpp>
#include <vector>
#include <string>



class ItemDialogue
{
private:
   placement2d place;
   std::vector<std::string> pages;
   ALLEGRO_FONT *font;
   Bitmap3D bitmap;
   bool showing_continue_notification;

public:
   ItemDialogue(float x, float y, float w, float h, ALLEGRO_BITMAP *item_bitmap, ALLEGRO_FONT *font, std::vector<std::string> pages);

   void draw(int page_num);
   int get_num_pages();
   void set_showing_continue_notification();
};



