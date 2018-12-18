


#include <krampushack2018/controllers/player_krampus_controller.hpp>

#include <allegro_flare/useful.h> // for key_pressed()



PlayerKrampusController::PlayerKrampusController()
   : krampus(nullptr)
{}



void PlayerKrampusController::set_krampus(KrampusEntity *new_krampus)
{
   krampus = new_krampus;
}



bool PlayerKrampusController::has_a_krampus()
{
   return krampus != nullptr;
}



void PlayerKrampusController::on_key_down(int al_keycode)
{
   if (!has_a_krampus()) return;

   switch(al_keycode)
   {
   case ALLEGRO_KEY_SPACE: krampus->attack(); break;
   case ALLEGRO_KEY_R: krampus->use_stone_of_defiance(); break;
   default: break;
   }
}



void PlayerKrampusController::on_key_up(int al_keycode)
{
   if (!has_a_krampus()) return;

   switch(al_keycode)
   {
   case ALLEGRO_KEY_UP: krampus->stand_still(); break;
   case ALLEGRO_KEY_DOWN: krampus->stand_still(); break;
   case ALLEGRO_KEY_RIGHT: krampus->stand_still(); break;
   case ALLEGRO_KEY_LEFT: krampus->stand_still(); break;
   default: break;
   }
}



void PlayerKrampusController::update_polled_keyboard_input()
{
   if (krampus->is_idle())
   {
      if (key_pressed(ALLEGRO_KEY_RIGHT)) krampus->move_right();
      if (key_pressed(ALLEGRO_KEY_LEFT)) krampus->move_left();
      if (key_pressed(ALLEGRO_KEY_UP)) krampus->move_up();
      if (key_pressed(ALLEGRO_KEY_DOWN)) krampus->move_down();
   }
}



