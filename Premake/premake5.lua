workspace("HD_CommonUtilities")
	configurations({"Debug", "Release"})
	platforms({"x64"})
	
project("HD_CommonUtilities")
	kind("StaticLib")
	language("C++")
	location("../HD_CommonUtilities")
	files("../HD_CommonUtilities/*.h")
	files("../HD_CommonUtilities/*.cpp")
	files("../HD_CommonUtilities/HD_CommonUtilities.natvis")
	pchheader("stdafx.h")
	pchsource("stdafx.cpp")
	
	filter({"configurations:Debug"})
		targetname("HD_CommonUtilities_Debug")
	
	filter({"configurations:Release"})
		targetname("HD_CommonUtilities_Release")
	
	targetdir("../Output/HD_CommonUtilities")
	warnings("Extra")
	flags({"FatalWarnings"})
	vpaths
	{
		["Containers"] = { "HD_ArrayIterator.h", "HD_GrowingArray.h", "HD_Map.h", "HD_Pair.h", "HD_StaticArray.h", "HD_StaticStack.h", "HD_String.h" },
		["Math"] = { "HD_Box.h", "HD_Math.h", "HD_Vector2.h" },
		["Misc"] = { "HD_Random.h", "HD_Rancom.cpp", "Types.h", "Utilities.h" }
		["Natvis"] = { "HD_CommonUtilities.natvis" }
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
	pchsource("stdafx.cpp")
	
	filter({"configurations:Debug"})
		links({"HD_CommonUtilities_Debug"})
		targetname("Tests_Debug")
	
	filter({"configurations:Release"})
		links({"HD_CommonUtilities_Release"})
		targetname("Tests_Release")
	
	targetdir("../Output/Tests")
	warnings("Extra")
	flags({"FatalWarnings"})
