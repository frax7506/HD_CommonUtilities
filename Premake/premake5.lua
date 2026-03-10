workspace("HD_CommonUtilities")
	configurations({"Debug", "Release"})
	platforms({"x64"})
	location("..")
	
project("HD_CommonUtilities")
	kind("StaticLib")
	language("C++")
	location("../HD_CommonUtilities")
	files("../HD_CommonUtilities/*.h")
	files("../HD_CommonUtilities/*.cpp")
	files("../HD_CommonUtilities/HD_CommonUtilities.natvis")
	pchheader("stdafx.h")
	pchsource("../HD_CommonUtilities/stdafx.cpp")
	objdir("../Intermediate/HD_CommonUtilities")
	
	filter({"configurations:Debug"})
		targetname("HD_CommonUtilities_Debug")
		targetdir("../Output/HD_CommonUtilities")
	
	filter({"configurations:Release"})
		targetname("HD_CommonUtilities_Release")
		targetdir("../Output/HD_CommonUtilities")
		
	warnings("Extra")
	fatalwarnings({"All"})
	vpaths
	{
		["Containers"] =
		{
			"../HD_CommonUtilities/HD_ArrayIterator.h",
			"../HD_CommonUtilities/HD_CircularArray.h",
			"../HD_CommonUtilities/HD_DataBuffer.h",
			"../HD_CommonUtilities/HD_GrowingArray.h",
			"../HD_CommonUtilities/HD_Map.h",
			"../HD_CommonUtilities/HD_Pair.h",
			"../HD_CommonUtilities/HD_StaticArray.h",
			"../HD_CommonUtilities/HD_StaticStack.h",
			"../HD_CommonUtilities/HD_String.h",
			"../HD_CommonUtilities/HD_String.cpp"
		},
		["Math"] =
		{
			"../HD_CommonUtilities/HD_AABB_2D.h",
			"../HD_CommonUtilities/HD_Math.h",
			"../HD_CommonUtilities/HD_Vector2.h"
		},
		["Misc"] =
		{
			"../HD_CommonUtilities/HD_IsFundamental.h",
			"../HD_CommonUtilities/HD_PreprocessorMacros.h",
			"../HD_CommonUtilities/HD_Random.h",
			"../HD_CommonUtilities/HD_Random.cpp",
			"../HD_CommonUtilities/HD_Singleton.h",
			"../HD_CommonUtilities/HD_Time.h",
			"../HD_CommonUtilities/HD_Time.cpp",
			"../HD_CommonUtilities/HD_Types.h",
			"../HD_CommonUtilities/HD_Utilities.h"
		},
		["Natvis"] =
		{
			"../HD_CommonUtilities/HD_CommonUtilities.natvis"
		},
		["Profiling"] =
		{
			"../HD_CommonUtilities/HD_ScopedTimer.h",
			"../HD_CommonUtilities/HD_ScopedTimer.cpp"
		}
	}
	
project("Tests")
	kind("SharedLib")
	language("C++")
	location("../Tests")
	files("../Tests/*.h")
	files("../Tests/*.cpp")
	libdirs({"../Output/HD_CommonUtilities"})
	includedirs({"../HD_CommonUtilities"})
	pchheader("stdafx.h")
	pchsource("../Tests/stdafx.cpp")
	objdir("../Intermediate/Tests")
	
	filter({"configurations:Debug"})
		links({"HD_CommonUtilities_Debug"})
		targetname("Tests_Debug")
		targetdir("../Output/Tests")
	
	filter({"configurations:Release"})
		links({"HD_CommonUtilities_Release"})
		targetname("Tests_Release")
		targetdir("../Output/Tests")
	
	warnings("Extra")
	fatalwarnings({"All"})
	vpaths
	{
		["Containers"] =
		{
			"../Tests/HD_AABB_2D_Tests.cpp",
			"../Tests/HD_CircularArray_Tests.cpp",
			"../Tests/HD_DataBuffer_Tests.cpp",
			"../Tests/HD_GrowingArray_Tests.cpp",
			"../Tests/HD_Map_Tests.cpp",
			"../Tests/HD_Pair_Tests.cpp",
			"../Tests/HD_StaticArray_Tests.cpp",
			"../Tests/HD_StaticStack_Tests.cpp",
			"../Tests/HD_String_Tests.cpp"
		},
		["Math"] =
		{
			"../Tests/HD_Math_Tests.cpp",
			"../Tests/HD_Vector2_Tests.cpp"
		},
		["Misc"] =
		{
			"../Tests/HD_IsFundamental_Tests.cpp"
		}
	}
