#pragma once


#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro_flare/object2d.h>


class Bitmap3D : public object2d
{
private:
   static Bitmap3D *dummy;

public:
   ALLEGRO_BITMAP *_bitmap;
   int _flags;

   static Bitmap3D *get_dummy()
   {
      if (!dummy) dummy = new Bitmap3D(NULL);
      return dummy;
   }

public:
   Bitmap3D(ALLEGRO_BITMAP *bitmap)
      : object2d(0,0,128,128)
      , _bitmap(bitmap)
      , _flags(ALLEGRO_FLAGS_EMPTY)
   {
      this->bitmap(_bitmap);
   }
   inline Bitmap3D &clean()
   {
      if (_placement) _placement->clear();
      if (_appearance) _appearance->clear();
      _bitmap = NULL;
      *_h = 128;
      *_w = 128;
      return *this;
   }
   inline Bitmap3D &align(float x, float y) { object2d::align(x, y); return *this; }
   inline Bitmap3D &position(float x, float y) { object2d::position(x, y); return *this; }
   inline Bitmap3D &anchor(float x, float y) { object2d::anchor(x, y); return *this; }
   inline Bitmap3D &scale(float x, float y) { object2d::scale(x, y); return *this; }
   inline Bitmap3D &scale(float s) { object2d::scale(s); return *this; }
   inline Bitmap3D &opacity(float opacity) { object2d::opacity(opacity); return *this; }
   inline Bitmap3D &save(std::string filename) { al_save_bitmap(filename.c_str(), _bitmap); return *this; }
   inline Bitmap3D &flags(int flags) { _flags = flags; return *this; }
   ALLEGRO_BITMAP *get_bitmap() { return _bitmap; }
   inline Bitmap3D &bitmap(ALLEGRO_BITMAP *bitmap)
   {
      //if (_bitmap == bitmap) return *this; //<- this line is not necessairy, and creates a bug when the object is initialized
      _bitmap = bitmap;
      if (_bitmap)
      {
         *_w = al_get_bitmap_width(_bitmap);
         *_h = al_get_bitmap_height(_bitmap);
      }
      else
      {
         *_w = 10;
         *_h = 10;
      }
      return *this;
   }
   inline Bitmap3D &draw_raw()
   {
      if (_bitmap)
      {
         if (_appearance) al_draw_tinted_bitmap(_bitmap, color::color(_appearance->color, _appearance->opacity), 0, 0, _flags);
         else al_draw_bitmap(_bitmap, 0, 0, _flags);
      }
      return *this;
   }
   inline Bitmap3D &draw()
   {
      if (_placement) _placement->start_transform();
      draw_raw();
      if (_placement) _placement->restore_transform();
      return *this;
   }
};


