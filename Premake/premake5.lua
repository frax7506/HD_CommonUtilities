projectRootFolder = ".."
projectRootPath = projectRootFolder .. "/"

projectFilesHDCommonUtilitiesFolder = projectRootPath .. "ProjectFiles/HD_CommonUtilities"
projectFilesTestsFolder = projectRootPath .. "ProjectFiles/Tests"

sourceHDCommonUtilitiesFolder = projectRootPath .. "Source/HD_CommonUtilities"
sourceHDCommonUtilitiesPath = sourceHDCommonUtilitiesFolder .. "/"
sourceHDCommonUtilitiesContainersFolder = sourceHDCommonUtilitiesPath .. "Containers"
sourceHDCommonUtilitiesContainersPath = sourceHDCommonUtilitiesContainersFolder .. "/"
sourceHDCommonUtilitiesMathFolder = sourceHDCommonUtilitiesPath .. "Math"
sourceHDCommonUtilitiesMathPath = sourceHDCommonUtilitiesMathFolder .. "/"
sourceHDCommonUtilitiesMiscFolder = sourceHDCommonUtilitiesPath .. "Misc"
sourceHDCommonUtilitiesMiscPath = sourceHDCommonUtilitiesMiscFolder .. "/"
sourceHDCommonUtilitiesNatvisFolder = sourceHDCommonUtilitiesPath .. "Natvis"
sourceHDCommonUtilitiesNatvisPath = sourceHDCommonUtilitiesNatvisFolder .. "/"
sourceHDCommonUtilitiesProfilingFolder = sourceHDCommonUtilitiesPath .. "Profiling"
sourceHDCommonUtilitiesProfilingPath = sourceHDCommonUtilitiesProfilingFolder .. "/"

sourceTestsFolder = projectRootPath .. "Source/Tests"
sourceTestsPath = sourceTestsFolder .. "/"
sourceTestsContainersFolder = sourceTestsPath .. "Containers"
sourceTestsContainersPath = sourceTestsContainersFolder .. "/"
sourceTestsMathFolder = sourceTestsPath .. "Math"
sourceTestsMathPath = sourceTestsMathFolder .. "/"
sourceTestsMiscFolder = sourceTestsPath .. "Misc"
sourceTestsMiscPath = sourceTestsMiscFolder .. "/"
sourceTestsUtilsFolder = sourceTestsPath .. "Utils"
sourceTestsUtilsPath = sourceTestsUtilsFolder .. "/"

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
	location(projectFilesHDCommonUtilitiesFolder)
	pchheader("stdafx.h")
	pchsource(sourceHDCommonUtilitiesPath .. "stdafx.cpp")
	files
	{
		sourceHDCommonUtilitiesContainersPath .. "*.h",
		sourceHDCommonUtilitiesMathPath .. "*.h",
		sourceHDCommonUtilitiesMiscPath .. "*.h",
		sourceHDCommonUtilitiesMiscPath .. "*.cpp",
		sourceHDCommonUtilitiesNatvisPath .. "*.natvis",
		sourceHDCommonUtilitiesProfilingPath .. "*.h",
		sourceHDCommonUtilitiesProfilingPath .. "*.cpp",
		sourceHDCommonUtilitiesPath .. "stdafx.h",
		sourceHDCommonUtilitiesPath .. "stdafx.cpp"
	}
	
	includedirs
	{
		sourceHDCommonUtilitiesContainersFolder,
		sourceHDCommonUtilitiesMathFolder,
		sourceHDCommonUtilitiesMiscFolder
	}
		
	warnings("Extra")
	fatalwarnings("All")
	defines("_CRT_SECURE_NO_WARNINGS")

	filter("configurations:Retail")
		defines("_RETAIL")
	
	filter({})
	
project("Tests")
	dependson("HD_CommonUtilities")
	kind("SharedLib")
	language("C++")
	cppdialect("C++17")
	
	targetname("Tests_$(Configuration)")
	targetdir("$(SolutionDir)Output/Tests")
	objdir("$(SolutionDir)Intermediate/Tests")
	location(projectFilesTestsFolder)
	pchheader("stdafx.h")
	pchsource(sourceTestsPath .. "stdafx.cpp")
	files
	{
		sourceTestsContainersPath .. "*.cpp",
		sourceTestsMathPath .. "*.cpp",
		sourceTestsMiscPath .. "*.cpp",
		sourceTestsUtilsPath .. "*.h",
		sourceTestsUtilsPath .. "*.cpp",
		sourceTestsPath .. "stdafx.h",
		sourceTestsPath .. "stdafx.cpp"
	}
	
	libdirs("$(SolutionDir)Output/HD_CommonUtilities")
	links("HD_CommonUtilities_$(Configuration)")
	includedirs
	{
		sourceHDCommonUtilitiesContainersFolder,
		sourceHDCommonUtilitiesMathFolder,
		sourceHDCommonUtilitiesMiscFolder,
		sourceTestsUtilsFolder
	}
	
	warnings("Extra")
	fatalwarnings("All")
	defines("_CRT_SECURE_NO_WARNINGS")

	filter("configurations:Retail")
		defines("_RETAIL")
	
	filter({})
