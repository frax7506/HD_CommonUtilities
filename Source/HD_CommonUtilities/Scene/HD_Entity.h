#pragma once

#include "HD_EntityID.h"
#include "HD_Move.h"
#include "HD_Scene.h"
#include "HD_TransformComponent.h"
#include "HD_Vector.h"

class HD_Entity
{
public:
	HD_Entity();
	HD_Entity(HD_EntityID aEntityID, HD_Scene* aScene);

	template<typename ComponentType>
	void AddComponent();

	template<typename ComponentType, typename... Args>
	void EmplaceComponent(Args&&... args);

	template<typename ComponentType>
	ComponentType& GetComponent();

	void SetPosition(const HD_Vector3_f32& aPosition);

private:
	HD_EntityID myID;
	HD_Scene* myScene;
};

HD_Entity::HD_Entity()
	: myID(0)
	, myScene(nullptr)
{
}

HD_Entity::HD_Entity(HD_EntityID aEntityID, HD_Scene* aScene)
	: myID(aEntityID)
	, myScene(aScene)
{
}

template<typename ComponentType>
void HD_Entity::AddComponent()
{
	myScene->myECS.AddComponent<ComponentType>(myID);
	GetComponent<ComponentType>().SetOwner(this);
}

template<typename ComponentType, typename... Args>
void HD_Entity::EmplaceComponent(Args&&... args)
{
	myScene->myECS.EmplaceComponent<ComponentType>(myID, HD_Forward<Args>(args)...);
}

template<typename ComponentType>
ComponentType& HD_Entity::GetComponent()
{
	return myScene->myECS.GetComponent<ComponentType>(myID);
}

void HD_Entity::SetPosition(const HD_Vector3_f32& aPosition)
{
	HD_TransformComponent& transformComponent = GetComponent<HD_TransformComponent>();
	transformComponent.myTransform.SetPosition(aPosition);
}
