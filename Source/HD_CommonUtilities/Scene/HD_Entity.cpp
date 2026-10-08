#include "HD_Entity.h"
#include "HD_TransformComponent.h"

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

void HD_Entity::SetPosition(const HD_Vector3_f32& aPosition)
{
	HD_TransformComponent& transformComponent = GetComponent<HD_TransformComponent>();
	transformComponent.myTransform.SetPosition(aPosition);
}
