


#include <krampushack2018/screens/game_play_screen.hpp>

#include <allegro_flare/allegro_flare.h>
#include <allegro_flare/user_event_emitter.h>
#include <krampushack2018/entities/door_entity.hpp>
#include <krampushack2018/factories/entity_factory.hpp>
#include <krampushack2018/factories/scene_factory.hpp>
#include <krampushack2018/helpers/scene_collection_helper.hpp>
#include <krampushack2018/item_type_nums.hpp>
#include <krampushack2018/music_track_nums.hpp>
#include <krampushack2018/user_events.hpp>



#define TEST_SCENE_ID 999
#define START_SCENE_ID 0



GamePlayScreen::GamePlayScreen(Display *display)
   : Screen(display)
   , scene(nullptr)
   , state(NONE)
   , player_krampus_controller()
   , ai_kid_controllers()
   , player_inventory()
   , naughty_list()
   , hud(&player_inventory, &naughty_list)
   , state_helper(this)
   , camera(display, nullptr)
   , _item_recently_collected(0)
{
   enter_scene(START_SCENE_ID);
   set_state(GAME_PLAY);
}



void GamePlayScreen::primary_timer_func()
{
   update();
   draw();
}



void GamePlayScreen::key_down_func()
{
   int al_keycode = Framework::current_event->keyboard.keycode;

   state_helper.process_key_down(al_keycode);
}



void GamePlayScreen::key_up_func()
{
   int al_keycode = Framework::current_event->keyboard.keycode;

   switch (state)
   {
   case GAME_PLAY:
      player_krampus_controller.on_key_up(al_keycode);
      break;
   case ENTERING_THROUGH_DOOR:
      // nothing
      break;
   default:
      break;
   }
}



void GamePlayScreen::user_event_func()
{
   ALLEGRO_EVENT *event = Framework::current_event;

   switch (event->user.type)
   {
   case ENTER_DOOR_EVENT:
      {
         int scene_id = event->user.data1;
         std::string destination_door_name;
         destination_door_name.push_back((char)event->user.data2);
         enter_scene(scene_id, destination_door_name[0]);
         break;
      }
   case COLLECT_ITEM_EVENT:
      {
         int item_type_int = event->user.data1;
         player_inventory.add_item(item_type_int);
         _item_recently_collected = item_type_int;

         if (item_type_int == ITEM_TYPE_CLUB)
         {
            SceneCollectionHelper collections(scene);
            KrampusEntity *krampus = collections.get_krampus();
            krampus->get_weapon();
         }
         else if (item_type_int == ITEM_TYPE_STONE_OF_DEFIANCE)
         {
            SceneCollectionHelper collections(scene);
            KrampusEntity *krampus = collections.get_krampus();
            krampus->get_stone_of_defiance();
         }

         set_state(ITEM_COLLECTED);
         break;
      }
   case USE_STONE_OF_DEFIANCE_EVENT:
      {
         set_state(USING_STONE_OF_DEFIANCE);
         break;
      }
   }
}



void GamePlayScreen::update()
{
   state_helper.update_state();
}



void GamePlayScreen::draw()
{
   state_helper.draw_state();
}



void GamePlayScreen::set_state(state_t new_state)
{
   state_helper.set_state(new_state);
}



void GamePlayScreen::enter_scene(int scene_id, char door_name)
{
   if (scene) delete scene;

   scene = SceneFactory::create_scene_by_id(scene_id);

   SceneCollectionHelper collections(scene);

   std::vector<NaughtyList::Kid> naughty_list_kids = naughty_list.get_alive_kids_for_scene(scene_id);
   KrampusEntity *krampus = collections.get_krampus();
   DoorEntity *door = collections.get_door(door_name);

   // create entities for the alive kids in this scene
   for (auto &kid : naughty_list_kids)
   {
      float min_y, max_y;
      float scene_width = scene->get_width();
      scene->get_y_bounds(&min_y, &max_y);

      float new_kid_x = random_float(0, scene->get_width());
      float new_kid_y = random_float(min_y, max_y);

      EntityFactory::create_named_kid(scene, kid.get_name(), kid.get_behavior(), kid.get_sprite_index(), new_kid_x, new_kid_y);
   }

   // create AI controllers to control the kids
   ai_kid_controllers.clear();

   for (auto &kid : collections.get_kids())
      ai_kid_controllers.push_back(AIKidController(kid));

   // equip the KrampusEntity with a weapon (if the player has one)
   if (player_inventory.has_item(ITEM_TYPE_CLUB)) krampus->get_weapon();
   if (player_inventory.has_item(ITEM_TYPE_STONE_OF_DEFIANCE)) krampus->get_stone_of_defiance();

   // set the player controller to control krampus
   player_krampus_controller.set_krampus(krampus);

   // have the camera follow krampus
   camera.set_target(krampus);

   // start (or resume) the music for this scene
   UserEventEmitter::emit_event(PLAY_MUSIC_TRACK, HAUNTING_MUSIC);

   // place krampus at the destination_door and walk down
   if (door)
   {
      krampus->place.position = door->place.position + vec2d(0.0, door->place.size.y/2 + krampus->place.size.y/2) + 5;
   }

   set_state(ENTERING_THROUGH_DOOR);
}



void GamePlayScreen::_destroy_ai_kid_controller_for(KidEntity *kid)
{
   for (unsigned i=0; i<ai_kid_controllers.size(); i++)
      if (ai_kid_controllers[i].is_controlling(kid))
      {
         ai_kid_controllers.erase(ai_kid_controllers.begin() + i);
         i--;
      }
}



