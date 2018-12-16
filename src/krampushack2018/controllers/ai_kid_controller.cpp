


#include <krampushack2018/controllers/ai_kid_controller.hpp>



AIKidController::AIKidController(KidEntity *kid)
   : kid(kid)
   , state_counter(0.0)
{}



KidEntity::state_t AIKidController::_get_a_random_state()
{
   std::vector<KidEntity::state_t> possible_states = {
         KidEntity::STATE_STANDING_STILL,
         KidEntity::STATE_WALKING_UP,
         KidEntity::STATE_WALKING_DOWN,
         KidEntity::STATE_WALKING_LEFT,
         KidEntity::STATE_WALKING_RIGHT
      };

   return possible_states[random_int(0, possible_states.size()-1)];
}



KidEntity::state_t AIKidController::_get_a_random_state_different_from_current_one()
{
   KidEntity::state_t random_state = _get_a_random_state();
   while ((random_state = _get_a_random_state()) == kid->state);

   return random_state;
}



void AIKidController::set_new_state()
{
   kid->set_state(_get_a_random_state_different_from_current_one());

   float duration_until_next_state_chage = random_float(0.5, 5.0);
   state_counter = duration_until_next_state_chage;
}



void AIKidController::update()
{
   state_counter -= 1.0/60.0;

   if (state_counter <= 0) set_new_state();
}



bool AIKidController::is_controlling(KidEntity *possibly_controlled_kid)
{
   return kid == possibly_controlled_kid;
}



