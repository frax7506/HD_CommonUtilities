#pragma once

#include "HD_Matrix.h"
#include "HD_Types.h"

class HD_Camera
{
public:
	HD_Camera();

	void InitAsPerspectiveCamera(const HD_Vector2u& aResolution, f32 aVerticalFoV, f32 aNear, f32 aFar);
	void InitAsOrthographicCamera(f32 aLeft, f32 aRight, f32 aTop, f32 aBottom, f32 aNear, f32 aFar);

	void Update();

	void SetResolution(const HD_Vector2u& aResolution);
	void SetVerticalFoV(f32 aVerticalFoV);

	void SetPerspectiveProjection(const HD_Vector2u& aResolution, f32 aVerticalFoV, f32 aNear, f32 aFar);
	void SetOrthographicProjection(f32 aLeft, f32 aRight, f32 aTop, f32 aBottom, f32 aNear, f32 aFar);

	void SetPosition(const HD_Vector3f& aPosition);
	void SetHeading(f32 aHeading);
	void SetPitch(f32 aPitch);
	void SetBank(f32 aBank);

	HD_Vector3f GetPosition() const;
	HD_Vector3f GetRotationInHPB() const;

	HD_Vector3f GetRight() const;
	HD_Vector3f GetUp() const;
	HD_Vector3f GetForward() const;

	const HD_Matrix4x4f& GetTransform() const;
	const HD_Matrix4x4f& GetProjection() const;

	HD_Vector4f WorldSpaceToClipSpace(const HD_Vector4f& aPointInWorldSpace) const;
	HD_Vector3f ClipSpaceToPerspectiveDivide(const HD_Vector4f& aPointInClipSpace) const;
	HD_Vector3f PerspectiveDivideToScreenSpace(const HD_Vector3f& aPointPostPerspectiveDivide) const;

private:
	void CalculateProjection();

	HD_Matrix4x4f myTransform;
	HD_Matrix4x4f myProjection;
	bool myIsProjectionDirty;

	// Perspective variables
	HD_Vector2u myResolution;
	f32 myVerticalFoV;

	// Orthographic variables
	f32 myLeft;
	f32 myRight;
	f32 myTop;
	f32 myBottom;

	// Both perspective and orthographic variables
	f32 myNear;
	f32 myFar;

	bool myIsUsingPerspectiveProjection;
};
