


#include <krampushack2018/entities/entity_base.h>
#include <krampushack2018/helpers/scene_collection_helper.h>
#include <krampushack2018/helpers/scene_collision_helper.h>
#include <krampushack2018/models/scene.h>
#include <algorithm>



Scene::Scene(int width)
   : ElementID(nullptr)
   , floor_min_y(465)
   , floor_max_y(600)
   , width(width)
{}



Scene::~Scene()
{
}



void Scene::set_y_bounds(float min_y, float max_y)
{
   floor_min_y = min_y;
   floor_max_y = max_y;
}



void Scene::get_y_bounds(float *min_y, float *max_y)
{
   *min_y = floor_min_y;
   *max_y = floor_max_y;
}



float Scene::get_width()
{
   return width;
}



void Scene::update_all()
{
   SceneCollisionHelper collision_helper(this);
   collision_helper.resolve_collisions();
}



void Scene::cleanup_all()
{
   SceneCollectionHelper collection_helper(this);

   for (auto &descendant : collection_helper.get_all_flagged_for_deletion())
      delete descendant;
}



void Scene::draw_all()
{
   SceneCollectionHelper collection_helper(this);

   for (auto &entity : collection_helper.get_all_entities_y_sorted())
      entity->draw();
}



