newoption {
	trigger     = "name",
	value       = "app",
	description = "Project name.",
}

newoption {
	trigger     = "location",
	value       = "./",
	description = "Where to generate the project.",
}

location_dir = _OPTIONS["location"]
name = _OPTIONS["name"]

workspace(name)
	location(location_dir)
	configurations { "Debug", "Release" }

	project(name)
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		targetdir = location_dir .. "bin/%{cfg.buildcfg}"

		files{
			"../data/src/**"
		}

		includedirs {
			location_dir
		}

		flags{"LinkTimeOptimization"}
		exceptionhandling("Off")
		rtti("Off")

		buildoptions{"-lstdc++"}

		filter "toolset:gcc"
			buildoptions{"-pipe"}
			linkoptions{"-fuse-ld=gold"}

		filter "toolset:clang"
			buildoptions{"-pipe -fwhole-program-vtables -fforce-emit-vtables"}
			linkoptions{"-fuse-ld=lld"}

		filter "configurations:Debug"
			defines { "DEBUG" }
			symbols "On"

		filter "configurations:Release"
			defines { "NDEBUG" }
			optimize "Full"
			buildoptions{"-fdata-sections -ffunction-sections"} -- needed for -gc-sections
			linkoptions{"-s -Wl,--gc-sections -Wl,--as-needed"}