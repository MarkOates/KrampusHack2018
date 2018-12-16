#pragma once



#include <krampushack2018/screens/storyboard_screen.hpp>



class StoryboardFactory
{
public:
   static StoryboardScreen *create_opening_storyboard_screen(Display *display);
   static StoryboardScreen *create_closing_storyboard_screen(Display *display);
};



