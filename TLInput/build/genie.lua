solution "TLInput"
	configurations { "Debug", "Release" }
	platforms { "x64" }
	language "C++"
	
project "TLInput"
	kind "sharedLib"
	files {
		"../include/**.h",
		"../src/**.cpp"
	}
	includedirs {
		"../include",
		"../../TLC/include"
	}
	vpaths {
		["*"] = "../src/TerraLens/",
		["include"] = "../include/TerraLens/"
	}
	links { "IVC" }
	defines { "ICL_EXPORTS" }
	
	windowstargetplatformversion "10.0.18362.0"
	flags {
		"Symbols"
		}
	
	configuration "Debug"
		targetdir "../lib/Debug"
		libdirs { "../../TLC/lib" }
	
	configuration "Release"
		targetdir "../lib/Release"
		flags { "OptimizeSpeed", }
		libdirs { "../../TLC/lib" }
	
	