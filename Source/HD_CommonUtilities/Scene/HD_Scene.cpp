#include "HD_Scene.h"

#include "HD_Entity.h"
#include "HD_EntityID.h"
#include "HD_TransformComponent.h"

HD_Scene::HD_Scene()
{
}

HD_Scene::~HD_Scene()
{
}

HD_Entity HD_Scene::CreateEntity()
{
	HD_EntityID entityID = myECS.CreateEntity();
	HD_Entity entity(entityID, this);
	entity.AddComponent<HD_TransformComponent>();

	return entity;
}
