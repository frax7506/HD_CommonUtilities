projectRootFolder = ".."
projectRootPath = projectRootFolder .. "/"

projectFilesHDCommonUtilitiesFolder = projectRootPath .. "ProjectFiles/HD_CommonUtilities"
projectFilesTestsFolder = projectRootPath .. "ProjectFiles/Tests"

sourceHDCommonUtilitiesFolder = projectRootPath .. "Source/HD_CommonUtilities"
sourceTestsFolder = projectRootPath .. "Source/Tests"

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
	files
	{
		sourceHDCommonUtilitiesFolder .. "/**.h",
		sourceHDCommonUtilitiesFolder .. "/**.cpp",
		sourceHDCommonUtilitiesFolder .. "/**.natvis"
	}
	
	includedirs
	{
		sourceHDCommonUtilitiesFolder .. "/Containers",
		sourceHDCommonUtilitiesFolder .. "/Input",
		sourceHDCommonUtilitiesFolder .. "/Math",
		sourceHDCommonUtilitiesFolder .. "/Misc"
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
	pchsource(sourceTestsFolder .. "/stdafx.cpp")
	files
	{
		sourceTestsFolder .. "/**.h",
		sourceTestsFolder .. "/**.cpp"
	}
	
	libdirs("$(SolutionDir)Output/HD_CommonUtilities")
	links("HD_CommonUtilities_$(Configuration)")
	includedirs
	{
		sourceHDCommonUtilitiesFolder .. "/Containers",
		sourceHDCommonUtilitiesFolder .. "/Math",
		sourceHDCommonUtilitiesFolder .. "/Misc",
		sourceTestsFolder .. "/Utils"
	}
	
	warnings("Extra")
	fatalwarnings("All")
	defines("_CRT_SECURE_NO_WARNINGS")

	filter("configurations:Retail")
		defines("_RETAIL")
	
	filter({})
