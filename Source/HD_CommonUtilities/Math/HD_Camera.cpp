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

void HD_Camera::InitAsPerspectiveCamera(const HD_Vector2ui& aResolution, float aVerticalFoV, float aNear, float aFar)
{
	SetPerspectiveProjection(aResolution, aVerticalFoV, aNear, aFar);
}

void HD_Camera::InitAsOrthographicCamera(float aLeft, float aRight, float aTop, float aBottom, float aNear, float aFar)
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

void HD_Camera::SetResolution(const HD_Vector2ui& aResolution)
{
	assert(myIsUsingPerspectiveProjection && "Setting the resolution on an orthographic camera has no effect.");

	myResolution = aResolution;
	myIsProjectionDirty = true;
}

void HD_Camera::SetVerticalFoV(float aVerticalFoV)
{
	assert(myIsUsingPerspectiveProjection && "Setting the field of view on an orthographic camera has no effect.");

	myVerticalFoV = aVerticalFoV;
	myIsProjectionDirty = true;
}

void HD_Camera::SetPerspectiveProjection(const HD_Vector2ui& aResolution, float aVerticalFoV, float aNear, float aFar)
{
	assert(0.f < aNear && aNear < aFar);

	myResolution = aResolution;
	myVerticalFoV = aVerticalFoV;
	myNear = aNear;
	myFar = aFar;

	myIsUsingPerspectiveProjection = true;
	myIsProjectionDirty = true;
}

void HD_Camera::SetOrthographicProjection(float aLeft, float aRight, float aTop, float aBottom, float aNear, float aFar)
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

void HD_Camera::SetPosition(const HD_Vector3f& aPosition)
{
	myTransform.SetPosition(aPosition);
}

void HD_Camera::SetHeading(float aHeading)
{
	myTransform.SetRotationAroundY(aHeading);
}

void HD_Camera::SetPitch(float aPitch)
{
	myTransform.SetRotationAroundX(aPitch);
}

void HD_Camera::SetBank(float aBank)
{
	myTransform.SetRotationAroundZ(aBank);
}

HD_Vector3f HD_Camera::GetPosition() const
{
	return myTransform.GetPosition();
}

HD_Vector3f HD_Camera::GetRotationInHPB() const
{
	return myTransform.GetRotationInHPB();
}

HD_Vector3f HD_Camera::GetRight() const
{
	return myTransform.GetRightVector();
}

HD_Vector3f HD_Camera::GetUp() const
{
	return myTransform.GetUpVector();
}

HD_Vector3f HD_Camera::GetForward() const
{
	return myTransform.GetForwardVector();
}

const HD_Matrix4x4f& HD_Camera::GetProjection() const
{
	return myProjection;
}

HD_Vector4f HD_Camera::WorldSpaceToClipSpace(const HD_Vector4f& aPointInWorldSpace) const
{
	HD_Vector4f viewSpace = aPointInWorldSpace * myTransform.GetFastInverse();
	HD_Vector4f clipSpace = viewSpace * myProjection;
	return clipSpace;
}

HD_Vector3f HD_Camera::ClipSpaceToPerspectiveDivide(const HD_Vector4f& aPointInClipSpace) const
{
	HD_Vector3f pointInClipSpaceXYZ(aPointInClipSpace.myX, aPointInClipSpace.myY, aPointInClipSpace.myZ);
	HD_Vector3f postPerspectiveDivide = pointInClipSpaceXYZ / aPointInClipSpace.myW;

	return postPerspectiveDivide;
}

HD_Vector3f HD_Camera::PerspectiveDivideToScreenSpace(const HD_Vector3f& aPointPostPerspectiveDivide) const
{
	float aspectRatio = static_cast<float>(myResolution.myX) / static_cast<float>(myResolution.myY);
	float screenSpaceX = HD_Remap(aPointPostPerspectiveDivide.myX, -1.f, 1.f, 0.f, aspectRatio);
	float screenSpaceY = HD_Remap(aPointPostPerspectiveDivide.myY, -1.f, 1.f, 0.f, 1.f);

	HD_Vector3f screenSpace(screenSpaceX, screenSpaceY, aPointPostPerspectiveDivide.myZ);
	return screenSpace;
}

void HD_Camera::CalculateProjection()
{
	myProjection = HD_Matrix4x4f::Identity;

	if (myIsUsingPerspectiveProjection)
	{
		float resolutionWidth = static_cast<float>(myResolution.myX);
		float resolutionHeight = static_cast<float>(myResolution.myY);

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
