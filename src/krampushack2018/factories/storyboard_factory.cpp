


#include <krampushack2018/factories/storyboard_factory.h>

#include <krampushack2018/user_events.h>



StoryboardScreen *StoryboardFactory::create_opening_storyboard_screen(Display *display)
{
   std::vector<std::string> pages;

   pages.push_back("Oh no!\n\nThere has been a big Christmas mix up this year and Krampus accidentally got the wrong list of Naughty kids.");
   pages.push_back("What's even worse is that it's already Christmas Eve!\n\nKrampus needs to punish all the naughty kids or it'll be a Christmas disaster!");
   pages.push_back("Your task:\n\nTravel around Krampus Cavern, find out who the naughty kids are, and deliver their well deserved Christmas punishment.");
   pages.push_back("\nUse the ARROW KEYS and SPACEBAR to play.  Once you get the legendary Stone of Defiance, you can activate it by pressing the R key.");
   pages.push_back("And one last thing!");
   pages.push_back("\nYou won't be able to do much damage on your own. You'll need to find a proper weapon to inflict some REAL Christmas pain!");
   pages.push_back("Good Luck!");

   StoryboardScreen *storyboard_screen = new StoryboardScreen(display, pages, START_GAME_EVENT);
   return storyboard_screen;
}



StoryboardScreen *StoryboardFactory::create_closing_storyboard_screen(Display *display)
{
   std::vector<std::string> pages;

   pages.push_back("\nCongratulations!\n\nWow!  You sure served up a healthy dish of comeuppance with a side of eggnog!");
   pages.push_back("\nThanks to you, Christmas has been saved and all the naughty children will have plenty to think about through the year.");
   pages.push_back("Santa thanks you, too.");
   pages.push_back("\nAnd so do I! :)");
   pages.push_back("\n\nThanks for being a part of KrampusHack 2016!");

   StoryboardScreen *storyboard_screen = new StoryboardScreen(display, pages, START_TITLE_SCREEN);
   return storyboard_screen;
}



