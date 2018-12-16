


#include <krampushack2018/sprite_sheet.hpp>

#include <allegro_flare/framework.h>
#include <allegro_flare/image_processing.h>



SpriteSheet::SpriteSheet(std::string filename, int sprite_width, int sprite_height, int num_rows, int num_columns, int scale)
   : atlas(Framework::bitmap(filename))
   , sprites()
   , sprite_width(sprite_width)
   , sprite_height(sprite_height)
   , num_rows(num_rows)
   , num_columns(num_columns)
   , scale(scale)
{
   _create_atlas_copy();
   _create_sub_sprites();
}



void SpriteSheet::_create_atlas_copy()
{
   atlas = create_pixel_perfect_scaled_render(atlas, scale);
}



bool SpriteSheet::_create_sub_sprites()
{
   if (!atlas) return false;

   for (unsigned cursor_y=0; cursor_y<num_rows; cursor_y++)
      for (unsigned cursor_x=0; cursor_x<num_columns; cursor_x++)
      {
         ALLEGRO_BITMAP *sub_bitmap = al_create_sub_bitmap(atlas,
               cursor_x * sprite_width * scale,
               cursor_y * sprite_height * scale,
               sprite_width * scale,
               sprite_height * scale);

         sprites.push_back(sub_bitmap);
      }

   return true;
}



SpriteSheet::~SpriteSheet()
{
   for (auto &sprite : sprites) al_destroy_bitmap(sprite);
   al_destroy_bitmap(atlas);
}



ALLEGRO_BITMAP *SpriteSheet::get_sprite(int index)
{
   if (index < 0 || index >= sprites.size()) return nullptr;
   return sprites[index];
}



