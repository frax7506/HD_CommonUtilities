projectRootFolder = ".."
projectRootPath = projectRootFolder .. "/"

sourceHDCommonUtilitiesFolder = projectRootPath .. "HD_CommonUtilities"
sourceHDCommonUtilitiesPath = sourceHDCommonUtilitiesFolder .. "/"

sourceTestsFolder = projectRootPath .. "Tests"
sourceTestsPath = sourceTestsFolder .. "/"

workspace("HD_CommonUtilities")
	configurations({ "Debug", "Release", "Retail" })
	platforms("x64")
	location(projectRootFolder)
	
project("HD_CommonUtilities")
	kind("StaticLib")
	language("C++")
	cppdialect("C++17")
	
	targetname("HD_CommonUtilities_$(Configuration)")
	targetdir("$(SolutionDir)Output/HD_CommonUtilities")
	objdir("$(Solutiondir)Intermediate/HD_CommonUtilities")
	location(sourceHDCommonUtilitiesFolder)
	files({ sourceHDCommonUtilitiesPath.. "*.h", sourceHDCommonUtilitiesPath .. "*.cpp", sourceHDCommonUtilitiesPath .. "HD_CommonUtilities.natvis" })
	pchheader("stdafx.h")
	pchsource(sourceHDCommonUtilitiesPath .. "stdafx.cpp")
		
	warnings("Extra")
	fatalwarnings("All")
	defines("_CRT_SECURE_NO_WARNINGS")

	filter("configurations:Retail")
		defines("_RETAIL")
	
	filter({})
	
	vpaths
	{
		["Containers"] =
		{
			sourceHDCommonUtilitiesPath .. "HD_ArrayIterator.h",
			sourceHDCommonUtilitiesPath .. "HD_Bitset.h",
			sourceHDCommonUtilitiesPath .. "HD_CircularArray.h",
			sourceHDCommonUtilitiesPath .. "HD_DataBuffer.h",
			sourceHDCommonUtilitiesPath .. "HD_GrowingArray.h",
			sourceHDCommonUtilitiesPath .. "HD_HashMap.h",
			sourceHDCommonUtilitiesPath .. "HD_Map.h",
			sourceHDCommonUtilitiesPath .. "HD_Pair.h",
			sourceHDCommonUtilitiesPath .. "HD_StaticArray.h",
			sourceHDCommonUtilitiesPath .. "HD_StaticStack.h",
			sourceHDCommonUtilitiesPath .. "HD_String.h"
		},
		["Math"] =
		{
			sourceHDCommonUtilitiesPath .. "HD_AABB_2D.h",
			sourceHDCommonUtilitiesPath .. "HD_AABB_3D.h",
			sourceHDCommonUtilitiesPath .. "HD_Camera.h",
			sourceHDCommonUtilitiesPath .. "HD_Math.h",
			sourceHDCommonUtilitiesPath .. "HD_Matrix.h",
			sourceHDCommonUtilitiesPath .. "HD_Matrix3x3.h",
			sourceHDCommonUtilitiesPath .. "HD_Matrix4x4.h",
			sourceHDCommonUtilitiesPath .. "HD_Vector2.h",
			sourceHDCommonUtilitiesPath .. "HD_Vector3.h",
			sourceHDCommonUtilitiesPath .. "HD_Vector4.h"
		},
		["Misc"] =
		{
			sourceHDCommonUtilitiesPath .. "HD_ExeArgs.h",
			sourceHDCommonUtilitiesPath .. "HD_ExeArgs.cpp",
			sourceHDCommonUtilitiesPath .. "HD_Format.h",
			sourceHDCommonUtilitiesPath .. "HD_Hash.h",
			sourceHDCommonUtilitiesPath .. "HD_IsFundamental.h",
			sourceHDCommonUtilitiesPath .. "HD_Logger.h",
			sourceHDCommonUtilitiesPath .. "HD_Logger.cpp",
			sourceHDCommonUtilitiesPath .. "HD_Move.h",
			sourceHDCommonUtilitiesPath .. "HD_PreprocessorMacros.h",
			sourceHDCommonUtilitiesPath .. "HD_Random.h",
			sourceHDCommonUtilitiesPath .. "HD_Random.cpp",
			sourceHDCommonUtilitiesPath .. "HD_SafeDelete.h",
			sourceHDCommonUtilitiesPath .. "HD_Singleton.h",
			sourceHDCommonUtilitiesPath .. "HD_StringUtils.h",
			sourceHDCommonUtilitiesPath .. "HD_Swap.h",
			sourceHDCommonUtilitiesPath .. "HD_Time.h",
			sourceHDCommonUtilitiesPath .. "HD_Time.cpp",
			sourceHDCommonUtilitiesPath .. "HD_Types.h",
			sourceHDCommonUtilitiesPath .. "HD_TypeTraits.h",
			sourceHDCommonUtilitiesPath .. "HD_Unused.h",
			sourceHDCommonUtilitiesPath .. "OptimizedWindowsInclude.h"
		},
		["Natvis"] =
		{
			sourceHDCommonUtilitiesPath .. "HD_CommonUtilities.natvis"
		},
		["Profiling"] =
		{
			sourceHDCommonUtilitiesPath .. "HD_ScopedTimer.h",
			sourceHDCommonUtilitiesPath .. "HD_ScopedTimer.cpp"
		}
	}
	
project("Tests")
	dependson("HD_CommonUtilities")
	kind("SharedLib")
	language("C++")
	cppdialect("C++17")
	
	targetname("Tests_$(Configuration)")
	targetdir("$(SolutionDir)Output/Tests")
	objdir("$(SolutionDir)Intermediate/Tests")
	location(sourceTestsFolder)
	files({ sourceTestsPath .. "*.h", sourceTestsPath .. "*.cpp" })
	pchheader("stdafx.h")
	pchsource(sourceTestsPath .. "stdafx.cpp")
	
	libdirs("$(SolutionDir)Output/HD_CommonUtilities")
	links("HD_CommonUtilities_$(Configuration)")
	includedirs(sourceHDCommonUtilitiesFolder)
	
	warnings("Extra")
	fatalwarnings("All")
	defines("_CRT_SECURE_NO_WARNINGS")

	filter("configurations:Retail")
		defines("_RETAIL")
	
	filter({})
	
	vpaths
	{
		["Containers"] =
		{
			
			sourceTestsPath .. "HD_Bitset_Tests.cpp",
			sourceTestsPath .. "HD_CircularArray_Tests.cpp",
			sourceTestsPath .. "HD_DataBuffer_Tests.cpp",
			sourceTestsPath .. "HD_GrowingArray_Tests.cpp",
			sourceTestsPath .. "HD_HashMap_Tests.cpp",
			sourceTestsPath .. "HD_Logger_Tests.cpp",
			sourceTestsPath .. "HD_Map_Tests.cpp",
			sourceTestsPath .. "HD_Pair_Tests.cpp",
			sourceTestsPath .. "HD_StaticArray_Tests.cpp",
			sourceTestsPath .. "HD_StaticStack_Tests.cpp",
			sourceTestsPath .. "HD_String_Tests.cpp"
		},
		["Math"] =
		{
			sourceTestsPath .. "HD_AABB_2D_Tests.cpp",
			sourceTestsPath .. "HD_AABB_3D_Tests.cpp",
			sourceTestsPath .. "HD_Math_Tests.cpp",
			sourceTestsPath .. "HD_Matrix3x3_Tests.cpp",
			sourceTestsPath .. "HD_Matrix4x4_Tests.cpp",
			sourceTestsPath .. "HD_Vector2_Tests.cpp",
			sourceTestsPath .. "HD_Vector3_Tests.cpp",
			sourceTestsPath .. "HD_Vector4_Tests.cpp"
		},
		["Misc"] =
		{
			sourceTestsPath .. "HD_ExeArgs_Tests.cpp",
			sourceTestsPath .. "HD_Format_Tests.cpp",
			sourceTestsPath .. "HD_IsFundamental_Tests.cpp"
		},
		["Utils"] =
		{
			sourceTestsPath .. "TestUtils.h",
			sourceTestsPath .. "TestUtils.cpp"
		}
	}
