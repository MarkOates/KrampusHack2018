#pragma once



#include <allegro_flare/inventory.h>
#include <krampushack2018/models/naughty_list.h>
#include <krampushack2018/sprite_sheet.h>



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
   BitmapObject chrome_bitmap;
   ALLEGRO_FONT *font;
   ALLEGRO_FONT *font_bigger;
   SpriteSheet sprite_sheet;
   BitmapObject club_item_bitmap;
   BitmapObject key_item_bitmap;
   BitmapObject stone_of_defiance_item_bitmap;
   BitmapObject naughty_list_item_bitmap;
   float black_bar_counter;

public:
   HUD(Inventory *player_inventory, NaughtyList *naughty_list);

   void set_values(int player_health, int player_max_health);

   void update();
   void draw();

   void set_to_cinema_mode();
   void set_to_game_play_mode();
};



