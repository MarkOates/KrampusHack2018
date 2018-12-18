#pragma once



#include <allegro_flare/inventory.h>
#include <krampushack2018/models/Bitmap3D.hpp>
#include <krampushack2018/models/naughty_list.hpp>
#include <krampushack2018/sprite_sheet.hpp>



class HUD
{
private:
   enum mode_t
   {
      MODE_GAME_PLAY,
      MODE_CINEMA
   };

   Inventory *player_inventory;
   NaughtyList *naughty_list;
   int player_health;
   int player_max_health;

   mode_t mode;
   void set_mode(mode_t new_mode);
   Bitmap3D chrome_bitmap;
   ALLEGRO_FONT *font;
   ALLEGRO_FONT *font_bigger;
   SpriteSheet sprite_sheet;
   Bitmap3D club_item_bitmap;
   Bitmap3D key_item_bitmap;
   Bitmap3D stone_of_defiance_item_bitmap;
   Bitmap3D naughty_list_item_bitmap;
   float black_bar_counter;

public:
   HUD(Inventory *player_inventory, NaughtyList *naughty_list);

   void set_values(int player_health, int player_max_health);

   void update();
   void draw();

   void set_to_cinema_mode();
   void set_to_game_play_mode();
};



