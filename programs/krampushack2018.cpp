


#include <allegro_flare/allegro_flare.h>

#include <krampushack2018/controllers/audio_controller.hpp>
#include <krampushack2018/factories/storyboard_factory.hpp>
#include <krampushack2018/screens/title_screen.hpp>
#include <krampushack2018/screens/game_play_screen.hpp>
#include <krampushack2018/user_events.hpp>



class KrampusHack2018 : public Screen
{
public:
   Screen *current_screen;
   AudioController audio_controller;
	KrampusHack2018(Display *display)
      : Screen(display)
      , current_screen(nullptr)
      , audio_controller()
   {
      UserEventEmitter::emit_event(START_TITLE_SCREEN);
   }

   void user_event_func() override
   {
      ALLEGRO_EVENT *event = Framework::current_event;

      switch (event->user.type)
      {
      case START_TITLE_SCREEN:
         if (current_screen) delete current_screen;
         current_screen = new TitleScreen(display);
         audio_controller.play_game_show_music();
         break;
      case START_INTRO_STORYBOARD_SCREEN:
         if (current_screen) delete current_screen;
         current_screen = StoryboardFactory::create_opening_storyboard_screen(display);
         audio_controller.play_storyboard_music();
         break;
      case START_CLOSING_STORYBOARD_SCREEN:
         if (current_screen) delete current_screen;
         current_screen = StoryboardFactory::create_closing_storyboard_screen(display);
         audio_controller.play_game_show_music();
         break;
      case START_GAME_EVENT:
         delete current_screen;
         current_screen = new GamePlayScreen(display);
         break;
      case PLAY_MUSIC_TRACK:
         {
            int track_id = event->user.data1;
            audio_controller.play_audio_track_by_id(track_id);
         }
         break;
      case PLAY_SOUND_EFFECT:
         {
            int sound_effect_id = event->user.data1;
            audio_controller.play_sound_effect_by_id(sound_effect_id);
         }
         break;
      case QUIT_GAME_EVENT:
         Framework::shutdown_program = true;
         break;
      }
   }
};



int main(int argc, char **argv)
{
	Framework::initialize();
	Display *display = Framework::create_display(1280, 720, ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   KrampusHack2018 krampushack2018(display);
	Framework::run_loop();
	return 0;
}



