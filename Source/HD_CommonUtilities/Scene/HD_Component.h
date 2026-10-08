#pragma once

class HD_Entity;

#define DECLARE_COMPONENT \
friend class HD_Entity; \
\
private: \
	void SetOwner(HD_Entity* aOwnerEntity) \
	{ \
		myEntity = aOwnerEntity; \
	} \
	\
	HD_Entity* myEntity = nullptr;

// Future work:
//	* myEntity probably should be some kind of handle.
