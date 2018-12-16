#pragma once



#include <krampushack2018/models/scene.h>



#define ONE_SCREEN_WIDTH (256*5)
#define FLOOR_TOP (465)
#define FLOOR_BOTTOM (600)
#define FLOOR_MIDDLE ((FLOOR_BOTTOM-FLOOR_TOP)/2.0+FLOOR_TOP)



class SceneFactory
{
private:
   static float door_notch_x(int pos);

   static Scene *_create_scene_by_dimentions(int screen_widths, int background_type=1);
   static Scene *create_test_scene();

   static Scene *create_scene_0();
   static Scene *create_scene_1();
   static Scene *create_scene_2();
   static Scene *create_scene_3();
   static Scene *create_scene_4();
   static Scene *create_scene_5();
   static Scene *create_scene_6();
   static Scene *create_scene_7();
   static Scene *create_scene_8();
   static Scene *create_scene_9();

public:
   static Scene *create_scene_by_id(int scene_id);
};



