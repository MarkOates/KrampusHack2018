



#include <allegro_flare/gui/widgets/float_spinner.h>

#include <allegro_flare/gui/widgets/button.h>
#include <allegro_flare/gui/widgets/text_input.h>
#include <allegro_flare/useful.h> // for tostring




UIFloatSpinner::UIFloatSpinner(UIWidget *parent, float x, float y, float w, float h)
   : UISpinnerBase(parent, "UIFloatSpinner", x, y, w, h)
   , val(0.0)
   , increment_amount(0.1)
{
   text_input->set_text(tostring(val));
}




void UIFloatSpinner::set_val(std::string strval)
{
   val = atof(strval.c_str());
   text_input->set_text(tostring(val));
   on_change();
}




void UIFloatSpinner::set_increment(float increment_amount)
{
   this->increment_amount = increment_amount;
}




float UIFloatSpinner::get_val()
{
   return val;
}




void UIFloatSpinner::increment()
{
   val += increment_amount;
   text_input->set_text(tostring(val));
   on_change();
}




void UIFloatSpinner::decrement()
{
   val -= increment_amount;
   text_input->set_text(tostring(val));
   on_change();
}




