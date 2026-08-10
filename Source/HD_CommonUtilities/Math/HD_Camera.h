#pragma once

#include "HD_Matrix.h"
#include "HD_Types.h"

class HD_Camera
{
public:
	HD_Camera();

	void InitAsPerspectiveCamera(const HD_Vector2_u32& aResolution, f32 aVerticalFoV, f32 aNear, f32 aFar);
	void InitAsOrthographicCamera(f32 aLeft, f32 aRight, f32 aTop, f32 aBottom, f32 aNear, f32 aFar);

	void Update();

	void SetResolution(const HD_Vector2_u32& aResolution);
	void SetVerticalFoV(f32 aVerticalFoV);

	void SetPerspectiveProjection(const HD_Vector2_u32& aResolution, f32 aVerticalFoV, f32 aNear, f32 aFar);
	void SetOrthographicProjection(f32 aLeft, f32 aRight, f32 aTop, f32 aBottom, f32 aNear, f32 aFar);

	void SetPosition(const HD_Vector3_f32& aPosition);
	void SetHeading(f32 aHeading);
	void SetPitch(f32 aPitch);
	void SetBank(f32 aBank);

	HD_Vector3_f32 GetPosition() const;
	HD_Vector3_f32 GetRotationInHPB() const;

	HD_Vector3_f32 GetRight() const;
	HD_Vector3_f32 GetUp() const;
	HD_Vector3_f32 GetForward() const;

	const HD_Matrix4x4_f32& GetTransform() const;
	const HD_Matrix4x4_f32& GetProjection() const;

	HD_Vector4_f32 WorldSpaceToClipSpace(const HD_Vector4_f32& aPointInWorldSpace) const;
	HD_Vector3_f32 ClipSpaceToPerspectiveDivide(const HD_Vector4_f32& aPointInClipSpace) const;
	HD_Vector3_f32 PerspectiveDivideToScreenSpace(const HD_Vector3_f32& aPointPostPerspectiveDivide) const;

private:
	void CalculateProjection();

	HD_Matrix4x4_f32 myTransform;
	HD_Matrix4x4_f32 myProjection;
	bool myIsProjectionDirty;

	// Perspective variables
	HD_Vector2_u32 myResolution;
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
