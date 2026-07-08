#pragma once

#include "HD_PreprocessorMacros.h"

#if !IS_RETAIL_BUILD

#include "HD_HashMap.h"
#include "HD_Singleton.h"
#include "HD_String.h"
#include "HD_Types.h"
#include "HD_Vector2.h"
#include "HD_Vector3.h"

class HD_ExeArgs : public HD_Singleton<HD_ExeArgs>
{
public:
	void Init(u32 argc, const char* argv[]);

	bool IsPresent(const char* aExeArgName) const;

	s32 GetValueS32(const char* aExeArgS32Name) const;
	f32 GetValueF32(const char* aExeArgF32Name) const;
	bool GetValueBool(const char* aExeArgBoolName) const;
	HD_Vector2f GetValueVector2f(const char* aExeArgVector2fName) const;
	HD_Vector3f GetValueVector3f(const char* aExeArgVector3fName) const;
	HD_String GetValueString(const char* aExeArgStringName) const;

private:
	HD_HashMap<HD_String, HD_String> myExeArgToValueMap;
};

#endif // !IS_RETAIL_BUILD
