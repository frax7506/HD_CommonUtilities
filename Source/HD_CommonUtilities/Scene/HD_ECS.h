#pragma once

#include "HD_EntityID.h"
#include "HD_HashMap.h"

#include <typeindex>

class HD_EntitiesContainer
{
public:


private:

};

class HD_ECS
{
public:
	HD_ECS();
	~HD_ECS();

	HD_EntityID CreateEntity();

	template<typename ComponentType>
	void AddComponent(HD_EntityID aEntityID);

	template<typename ComponentType, typename... Args>
	void EmplaceComponent(HD_EntityID aEntityID, Args&&... args);

	template<typename ComponentType>
	void RemoveComponent(HD_EntityID aEntityID);

	template<typename ComponentType>
	bool HasComponent(HD_EntityID aEntityID);

	template<typename ComponentType>
	ComponentType& GetComponent(HD_EntityID aEntityID);

	template<typename ComponentType>
	HD_EntitiesContainer& GetEntitiesWithComponent();

	void Clear();

private:
	
};

template<typename ComponentType>
void HD_ECS::AddComponent(HD_EntityID aEntityID)
{

}

template<typename ComponentType, typename... Args>
void HD_ECS::EmplaceComponent(HD_EntityID aEntityID, Args&&... args)
{

}

template<typename ComponentType>
void HD_ECS::RemoveComponent(HD_EntityID aEntityID)
{

}

template<typename ComponentType>
bool HD_ECS::HasComponent(HD_EntityID aEntityID)
{

}

template<typename ComponentType>
ComponentType& HD_ECS::GetComponent(HD_EntityID aEntityID)
{

}

template<typename ComponentType>
HD_EntitiesContainer& HD_ECS::GetEntitiesWithComponent()
{

}
