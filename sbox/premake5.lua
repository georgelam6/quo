-- TO COMPILE ON WINDOWS, REMOVE THE `links` ATTRIBUTE

workspace "sbox"
	configurations { "debug", "release" }

project "sbox"
	kind "ConsoleApp"
	language "C"

	includedirs {
		"../quo/"
	}

	files {
		"src/sbox.c"
	}

	filter "configurations:debug"
		symbols "on"

	filter "configurations:release"
		optimize "on"


	filter "platforms:linux"
		links {
	 		"GL",
	 		"X11"
		}
