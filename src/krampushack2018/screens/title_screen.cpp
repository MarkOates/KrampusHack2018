


#include <allegro_flare/framework.h>
#include <allegro_flare/user_event_emitter.h>
#include <krampushack2018/screens/title_screen.hpp>
#include <krampushack2018/user_events.hpp>



#define MENU_OPTION_START "start"
#define MENU_OPTION_EXIT "exit"



TitleScreen::TitleScreen(Display *display)
   : Screen(display)
   , fonts()
   , menu_cursor_pos(0)
   , title(TextObject("The Krampus"))
   , title2(TextObject("Christmas Calamity"))
   , menu_items({TextObject(MENU_OPTION_START), TextObject(MENU_OPTION_EXIT)})
   , state(SHOWING_TITLE)
{
   ALLEGRO_FONT *font = fonts["ChronoTrigger.ttf 60"];

   title.font(font)
      .align(0.5, 1.1)
      .scale(2, 2)
      .position(display->center(), display->middle()-100);

   title2.font(font)
      .align(0.5, -0.1)
      .scale(2, 2)
      .position(display->center(), display->middle()-100);

   int count = 0;
   for (auto &menu_item : menu_items)
   {
      menu_item.font(font)
         .align(0.5, 0.5)
         .scale(1.0, 1.0)
         .position(display->center(), display->middle()+count*50 + 100);

      count++;
   }

   refresh_focused_menu_item();
}



void TitleScreen::primary_timer_func()
{
   al_clear_to_color(color::black);

   // draw the title
   title.draw();
   title2.draw();

   // draw the menu options
   for (auto &menu_item : menu_items) menu_item.draw();
}



void TitleScreen::key_down_func()
{
   switch(Framework::current_event->keyboard.keycode)
   {
   case ALLEGRO_KEY_UP:
      cursor_up_action();
      break;
   case ALLEGRO_KEY_DOWN:
      cursor_down_action();
      break;
   case ALLEGRO_KEY_ENTER:
   case ALLEGRO_KEY_SPACE:
      select_option_action();
      break;
   }
}



void TitleScreen::cursor_up_action()
{
   menu_cursor_pos--;
   if (menu_cursor_pos < 0) menu_cursor_pos = menu_items.size() - 1;
   refresh_focused_menu_item();
}



void TitleScreen::cursor_down_action()
{
   menu_cursor_pos++;
   if (menu_cursor_pos >= menu_items.size()) menu_cursor_pos = 0;
   refresh_focused_menu_item();
}



void TitleScreen::refresh_focused_menu_item()
{
   for (unsigned i=0; i<menu_items.size(); i++)
   {
      if (i == menu_cursor_pos) menu_items[i].scale(1.5, 1.5).color(color::yellow);
      else menu_items[i].scale(1.0, 1.0).color(color::gray);
   }
}



void TitleScreen::select_option_action()
{
   state = ITEM_SELECTED;

   std::string selected_menu_str = menu_items[menu_cursor_pos].str;

   if (selected_menu_str == MENU_OPTION_START)
      UserEventEmitter::emit_event(START_INTRO_STORYBOARD_SCREEN);
   else if (selected_menu_str == MENU_OPTION_EXIT)
      UserEventEmitter::emit_event(QUIT_GAME_EVENT);
}



