#include "HD_Camera.h"

#include <cassert>

HD_Camera::HD_Camera()
	: myIsProjectionDirty(false)
	, myVerticalFoV(0.f)
	, myLeft(0.f)
	, myRight(0.f)
	, myTop(0.f)
	, myBottom(0.f)
	, myNear(0.f)
	, myFar(0.f)
	, myIsUsingPerspectiveProjection(true)
{
}

void HD_Camera::InitAsPerspectiveCamera(const HD_Vector2_u32& aResolution, f32 aVerticalFoV, f32 aNear, f32 aFar)
{
	SetPerspectiveProjection(aResolution, aVerticalFoV, aNear, aFar);
}

void HD_Camera::InitAsOrthographicCamera(f32 aLeft, f32 aRight, f32 aTop, f32 aBottom, f32 aNear, f32 aFar)
{
	SetOrthographicProjection(aLeft, aRight, aTop, aBottom, aNear, aFar);
}

void HD_Camera::Update()
{
	if (myIsProjectionDirty)
	{
		CalculateProjection();
		myIsProjectionDirty = false;
	}
}

void HD_Camera::SetResolution(const HD_Vector2_u32& aResolution)
{
	assert(myIsUsingPerspectiveProjection && "Setting the resolution on an orthographic camera has no effect.");

	myResolution = aResolution;
	myIsProjectionDirty = true;
}

void HD_Camera::SetVerticalFoV(f32 aVerticalFoV)
{
	assert(myIsUsingPerspectiveProjection && "Setting the field of view on an orthographic camera has no effect.");

	myVerticalFoV = aVerticalFoV;
	myIsProjectionDirty = true;
}

void HD_Camera::SetPerspectiveProjection(const HD_Vector2_u32& aResolution, f32 aVerticalFoV, f32 aNear, f32 aFar)
{
	assert(0.f < aNear && aNear < aFar);

	myResolution = aResolution;
	myVerticalFoV = aVerticalFoV;
	myNear = aNear;
	myFar = aFar;

	myIsUsingPerspectiveProjection = true;
	myIsProjectionDirty = true;
}

void HD_Camera::SetOrthographicProjection(f32 aLeft, f32 aRight, f32 aTop, f32 aBottom, f32 aNear, f32 aFar)
{
	assert(aLeft < aRight && aBottom < aTop && aNear < aFar);

	myLeft = aLeft;
	myRight = aRight;
	myTop = aTop;
	myBottom = aBottom;

	myNear = aNear;
	myFar = aFar;

	myIsUsingPerspectiveProjection = false;
	myIsProjectionDirty = true;
}

void HD_Camera::SetPosition(const HD_Vector3_f32& aPosition)
{
	myTransform.SetPosition(aPosition);
}

void HD_Camera::SetRotation(const HD_Matrix4x4_f32& aRotationMatrix)
{
	myTransform.SetRotation(aRotationMatrix);
}

void HD_Camera::SetHeading(f32 aHeading)
{
	myTransform.SetRotationAroundY(aHeading);
}

void HD_Camera::SetPitch(f32 aPitch)
{
	myTransform.SetRotationAroundX(aPitch);
}

void HD_Camera::SetBank(f32 aBank)
{
	myTransform.SetRotationAroundZ(aBank);
}

HD_Vector3_f32 HD_Camera::GetPosition() const
{
	return myTransform.GetPosition();
}

HD_Vector3_f32 HD_Camera::GetRotationInHPB() const
{
	return myTransform.GetRotationInHPB();
}

HD_Matrix4x4_f32 HD_Camera::GetRotation() const
{
	return myTransform.GetRotation();
}

HD_Vector3_f32 HD_Camera::GetRight() const
{
	return myTransform.GetRightVector();
}

HD_Vector3_f32 HD_Camera::GetUp() const
{
	return myTransform.GetUpVector();
}

HD_Vector3_f32 HD_Camera::GetForward() const
{
	return myTransform.GetForwardVector();
}

const HD_Matrix4x4_f32& HD_Camera::GetTransform() const
{
	return myTransform;
}

const HD_Matrix4x4_f32& HD_Camera::GetProjection() const
{
	return myProjection;
}

HD_Vector4_f32 HD_Camera::WorldSpaceToClipSpace(const HD_Vector4_f32& aPointInWorldSpace) const
{
	HD_Vector4_f32 viewSpace = aPointInWorldSpace * myTransform.GetFastInverse();
	HD_Vector4_f32 clipSpace = viewSpace * myProjection;
	return clipSpace;
}

HD_Vector3_f32 HD_Camera::ClipSpaceToPerspectiveDivide(const HD_Vector4_f32& aPointInClipSpace) const
{
	HD_Vector3_f32 pointInClipSpaceXYZ(aPointInClipSpace.myX, aPointInClipSpace.myY, aPointInClipSpace.myZ);
	HD_Vector3_f32 postPerspectiveDivide = pointInClipSpaceXYZ / aPointInClipSpace.myW;

	return postPerspectiveDivide;
}

HD_Vector3_f32 HD_Camera::PerspectiveDivideToScreenSpace(const HD_Vector3_f32& aPointPostPerspectiveDivide) const
{
	f32 aspectRatio = static_cast<f32>(myResolution.myX) / static_cast<f32>(myResolution.myY);
	f32 screenSpaceX = HD_Remap(aPointPostPerspectiveDivide.myX, -1.f, 1.f, 0.f, aspectRatio);
	f32 screenSpaceY = HD_Remap(aPointPostPerspectiveDivide.myY, -1.f, 1.f, 0.f, 1.f);

	HD_Vector3_f32 screenSpace(screenSpaceX, screenSpaceY, aPointPostPerspectiveDivide.myZ);
	return screenSpace;
}

void HD_Camera::CalculateProjection()
{
	myProjection = HD_Matrix4x4_f32::Identity;

	if (myIsUsingPerspectiveProjection)
	{
		f32 resolutionWidth = static_cast<f32>(myResolution.myX);
		f32 resolutionHeight = static_cast<f32>(myResolution.myY);

		myProjection(1, 1) = (resolutionHeight / resolutionWidth) * (1.f / HD_Tan(myVerticalFoV / 2.f));
		myProjection(2, 2) = 1.f / HD_Tan(myVerticalFoV / 2.f);
		myProjection(3, 3) = myFar / (myFar - myNear);
		myProjection(3, 4) = 1.f;
		myProjection(4, 3) = (-1.f * myNear) * (myFar / (myFar - myNear));
		myProjection(4, 4) = 0.f;
	}
	else
	{
		myProjection(1, 1) = 2.f / (myRight - myLeft);
		myProjection(2, 2) = 2.f / (myBottom - myTop);
		myProjection(3, 3) = 1.f / (myFar - myNear);

		myProjection(4, 1) = (-1.f * (myRight + myLeft)) / (myRight - myLeft);
		myProjection(4, 2) = (-1.f * (myBottom + myTop)) / (myBottom - myTop);
		myProjection(4, 3) = (-1.f * myNear) / (myFar - myNear);
	}
}
