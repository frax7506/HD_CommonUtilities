#pragma once

#include "HD_Component.h"
#include "HD_Matrix.h"

class HD_TransformComponent
{
	DECLARE_COMPONENT
public:
	HD_TransformComponent();

	HD_Matrix4x4_f32 myTransform;
};
