local EngineRootDir = '../../../..'

workspace "Game"
	architecture "x86_64"
	startproject "Game"
	multiprocessorcompile "On"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Game"
	kind "SharedLib"
	language "C#"
	dotnetframework "4.8"

	targetdir ("Binaries")
	objdir ("Intermediates")

	files 
	{
		"Source/**.cs",
		"Properties/**.cs"
	}

	links
	{
		"Engine-ScriptCore"
	}
	
	filter "configurations:Debug"
		optimize "Off"
		symbols "Default"

	filter "configurations:Release"
		optimize "On"
		symbols "Default"

	filter "configurations:Dist"
		optimize "Full"
		symbols "Off"


group "GameEngine"
	include (EngineRootDir .. "/Engine-ScriptCore")
group ""