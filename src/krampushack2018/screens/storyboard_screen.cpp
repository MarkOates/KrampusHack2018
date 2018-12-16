


#include <krampushack2018/screens/storyboard_screen.hpp>

#include <allegro_flare/user_event_emitter.h>
#include <allegro_flare/framework.h>
#include <krampushack2018/user_events.hpp>



StoryboardScreen::StoryboardScreen(Display *display, std::vector<std::string> pages, intptr_t event_to_emit_after_completing)
   : Screen(display)
   , text_font(Framework::font("ChronoTrigger.ttf 60"))
   , pages(pages)
   , current_page(0)
   , event_to_emit_after_completing(event_to_emit_after_completing)
{
}



void StoryboardScreen::primary_timer_func()
{
   al_clear_to_color(color::hex("11141a"));

   if (current_page >= pages.size()) return;

   float x_padding = 150;
   float y_padding = 150;

   al_draw_multiline_text(
         text_font,
         color::hex("d0f2c5"),
         x_padding,
         y_padding,
         display->width() - x_padding*2,
         al_get_font_line_height(text_font)*1.75,
         0,
         pages[current_page].c_str()
      );
}



void StoryboardScreen::key_down_func()
{
   current_page++;

   if (current_page >= pages.size())
      UserEventEmitter::emit_event(event_to_emit_after_completing);
}



