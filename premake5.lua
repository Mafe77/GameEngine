include "Dependencies.lua"

workspace "GameEngine"
    architecture "x64"
    startproject "Engine-Editor"
    multiprocessorcompile "On"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "GameEngine/vendor/GLFW"
    include "GameEngine/vendor/Glad"
    include "GameEngine/vendor/imgui"
    include "GameEngine/vendor/yaml-cpp"
    include "GameEngine/vendor/Box2D"
group ""

group "Core"
    include "GameEngine"
    include "Engine-ScriptCore"
group ""

group "Tools"
    include "Engine-Editor"
group ""

group "Misc"
    include "Sandbox"
group ""