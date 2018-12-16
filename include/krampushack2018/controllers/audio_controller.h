#pragma once



#include <allegro_flare/objects/sound_object.h>



class AudioController
{
private:
   Sound game_show_music;
   Sound storyboard_music;
   Sound haunting_music;
   Sound hurt_sound_effect;
   Sound tada_sound_effect;
   Sound win_cheer_sound_effect;
   Sound fail_moan_sound_effect;
   Sound strong_punch_sound_effect;
   int current_music_track_num;

public:
   AudioController();
   ~AudioController();

   void play_game_show_music();
   void play_storyboard_music();
   void play_haunting_music();
   void play_hurt_sound_effect();
   void play_tada_sound_effect();
   void play_strong_punch_sound_effect();

   void stop_all();

   void play_audio_track_by_id(int id);
   void play_sound_effect_by_id(int id);
};



