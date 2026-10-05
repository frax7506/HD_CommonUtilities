#pragma once

#include "HD_ECS.h"

class HD_Entity;

class HD_Scene
{
	friend class HD_Entity;

public:
	HD_Scene();
	~HD_Scene();

	HD_Entity CreateEntity();

	template<typename ComponentType>
	HD_EntitiesContainer& GetEntitiesWithComponent();

private:
	HD_ECS myECS;
};

template<typename ComponentType>
HD_EntitiesContainer& HD_Scene::GetEntitiesWithComponent()
{
	return myECS.GetEntitiesWithComponent<ComponentType>();
}
