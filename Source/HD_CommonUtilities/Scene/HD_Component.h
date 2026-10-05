#pragma once

class HD_Entity;

#define DECLARE_COMPONENT \
public: \
	void SetOwner(HD_Entity* aOwnerEntity) \
	{ \
		myEntity = aOwnerEntity; \
	} \
	\
private: \
	HD_Entity* myEntity = nullptr;

// Future work:
//	* myEntity probably should be some kind of handle.
