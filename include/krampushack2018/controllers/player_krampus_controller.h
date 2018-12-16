#pragma once



#include <krampushack2018/entities/krampus_entity.h>



class PlayerKrampusController
{
private:
   KrampusEntity *krampus;

public:
   PlayerKrampusController();

   void set_krampus(KrampusEntity *krampus);
   bool has_a_krampus();

   void on_key_down(int al_keycode);
   void on_key_up(int al_keycode);

   void update_polled_keyboard_input();
};



