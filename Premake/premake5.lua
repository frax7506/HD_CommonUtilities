workspace("HD_CommonUtilities")
	configurations({ "Debug", "Release", "Retail" })
	platforms("x64")
	location("..")
	
project("HD_CommonUtilities")
	kind("StaticLib")
	language("C++")
	cppdialect("C++17")
	
	targetname("HD_CommonUtilities_$(Configuration)")
	targetdir("../Output/HD_CommonUtilities")
	objdir("../Intermediate/HD_CommonUtilities")
	location("../HD_CommonUtilities")
	files({ "../HD_CommonUtilities/*.h", "../HD_CommonUtilities/*.cpp", "../HD_CommonUtilities/HD_CommonUtilities.natvis" })
	pchheader("stdafx.h")
	pchsource("../HD_CommonUtilities/stdafx.cpp")
		
	warnings("Extra")
	fatalwarnings({"All"})
	defines("_CRT_SECURE_NO_WARNINGS")

	filter("configurations:Retail")
		defines("_RETAIL")
	
	filter({})
	
	vpaths
	{
		["Containers"] =
		{
			"../HD_CommonUtilities/HD_ArrayIterator.h",
			"../HD_CommonUtilities/HD_CircularArray.h",
			"../HD_CommonUtilities/HD_DataBuffer.h",
			"../HD_CommonUtilities/HD_GrowingArray.h",
			"../HD_CommonUtilities/HD_HashMap.h",
			"../HD_CommonUtilities/HD_HybridString.h",
			"../HD_CommonUtilities/HD_HybridString.cpp",
			"../HD_CommonUtilities/HD_Map.h",
			"../HD_CommonUtilities/HD_Pair.h",
			"../HD_CommonUtilities/HD_StaticArray.h",
			"../HD_CommonUtilities/HD_StaticStack.h",
			"../HD_CommonUtilities/HD_String.h"
		},
		["Math"] =
		{
			"../HD_CommonUtilities/HD_AABB_2D.h",
			"../HD_CommonUtilities/HD_Math.h",
			"../HD_CommonUtilities/HD_Vector2.h",
			"../HD_CommonUtilities/HD_Vector3.h"
		},
		["Misc"] =
		{
			"../HD_CommonUtilities/HD_ExeArgs.h",
			"../HD_CommonUtilities/HD_ExeArgs.cpp",
			"../HD_CommonUtilities/HD_Hash.h",
			"../HD_CommonUtilities/HD_IsFundamental.h",
			"../HD_CommonUtilities/HD_Logger.h",
			"../HD_CommonUtilities/HD_Logger.cpp",
			"../HD_CommonUtilities/HD_PreprocessorMacros.h",
			"../HD_CommonUtilities/HD_Random.h",
			"../HD_CommonUtilities/HD_Random.cpp",
			"../HD_CommonUtilities/HD_Singleton.h",
			"../HD_CommonUtilities/HD_StringUtils.h",
			"../HD_CommonUtilities/HD_Time.h",
			"../HD_CommonUtilities/HD_Time.cpp",
			"../HD_CommonUtilities/HD_Types.h",
			"../HD_CommonUtilities/HD_Utilities.h",
			"../HD_CommonUtilities/OptimizedWindowsInclude.h"
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
	dependson("HD_CommonUtilities")
	kind("SharedLib")
	language("C++")
	cppdialect("C++17")
	
	targetname("Tests_$(Configuration)")
	targetdir("../Output/Tests")
	objdir("../Intermediate/Tests")
	location("../Tests")
	files({ "../Tests/*.h", "../Tests/*.cpp" })
	pchheader("stdafx.h")
	pchsource("../Tests/stdafx.cpp")
	
	libdirs("../Output/HD_CommonUtilities")
	links("HD_CommonUtilities_$(Configuration)")
	includedirs("../HD_CommonUtilities")
	
	warnings("Extra")
	fatalwarnings({"All"})
	defines("_CRT_SECURE_NO_WARNINGS")

	filter("configurations:Retail")
		defines("_RETAIL")
	
	filter({})
	
	vpaths
	{
		["Containers"] =
		{
			"../Tests/HD_AABB_2D_Tests.cpp",
			"../Tests/HD_CircularArray_Tests.cpp",
			"../Tests/HD_DataBuffer_Tests.cpp",
			"../Tests/HD_GrowingArray_Tests.cpp",
			"../Tests/HD_HashMap_Tests.cpp",
			"../Tests/HD_HybridString_Tests.cpp",
			"../Tests/HD_Map_Tests.cpp",
			"../Tests/HD_Pair_Tests.cpp",
			"../Tests/HD_StaticArray_Tests.cpp",
			"../Tests/HD_StaticStack_Tests.cpp",
			"../Tests/HD_String_Tests.cpp"
		},
		["Math"] =
		{
			"../Tests/HD_Math_Tests.cpp",
			"../Tests/HD_Vector2_Tests.cpp",
			"../Tests/HD_Vector3_Tests.cpp"
		},
		["Misc"] =
		{
			"../Tests/HD_IsFundamental_Tests.cpp",
			"../Tests/HD_ExeArgs_Tests.cpp"
		}
	}
