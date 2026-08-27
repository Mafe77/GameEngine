workspace "GameEngine"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

VULKAN_SDK = os.getenv("VULKAN_SDK")

-- Include directories relative to the root folder (sol dir)
IncludeDir = {}
IncludeDir["GLFW"] = "GameEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "GameEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "GameEngine/vendor/imgui"
IncludeDir["glm"] = "GameEngine/vendor/glm"
IncludeDir["stb_image"] = "GameEngine/vendor/stb_image"
IncludeDir["entt"] = "GameEngine/vendor/entt/include"
IncludeDir["yaml_cpp"] = "GameEngine/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "GameEngine/vendor/ImGuizmo"
IncludeDir["shaderc"] = "GameEngine/vendor/shaderc/include"
IncludeDir["SPIRV_Cross"] = "GameEngine/vendor/SPIRV-Cross"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["Box2D"] = "GameEngine/vendor/Box2D/include"
IncludeDir["mono"] = "GameEngine/vendor/mono/include"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"] = "%{VULKAN_SDK}/Lib"
LibraryDir["mono"] = "vendor/mono/lib/%{cfg.buildcfg}"

Library = {}
Library["mono"] = "%{LibraryDir.mono}/libmono-static-sgen.lib"

Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"

Library["WinSock"] = "Ws2_32.lib"
Library["WinMM"] = "Winmm.lib"
Library["WinVersion"] = "Version.lib"
Library["BCrypt"] = "Bcrypt.lib"

group "Dependencies"
    include "GameEngine/vendor/GLFW"
    include "GameEngine/vendor/Glad"
    include "GameEngine/vendor/imgui"
    include "GameEngine/vendor/yaml-cpp"
    include "GameEngine/vendor/Box2D"

group ""

project "GameEngine"
    location "GameEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "gepch.h"
    pchsource "GameEngine/src/gepch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",

        "%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
        "%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS",
        "YAML_CPP_STATIC_DEFINE"
	}

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.yaml_cpp}",
        "%{IncludeDir.ImGuizmo}",
        "%{IncludeDir.VulkanSDK}",
        "%{IncludeDir.Box2D}",
        "%{IncludeDir.mono}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "yaml-cpp",
        "opengl32.lib",
        "Box2D",

        "%{Library.mono}"
    }

    filter "files:GameEngine/vendor/ImGuizmo/**.cpp"
        enablepch "Off"
    

    filter "system:windows"
        systemversion "latest"
        buildoptions "/utf-8"

        defines
        {
            "GE_PLATFORM_WINDOWS",
            "GE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }
        links
		{
			"%{Library.WinSock}",
			"%{Library.WinMM}",
			"%{Library.WinVersion}",
			"%{Library.BCrypt}",
		}

    filter "configurations:Debug"
        defines "GE_DEBUG"
        runtime "Debug"
        symbols "on"

        links
		{
			"%{Library.ShaderC_Debug}",
			"%{Library.SPIRV_Cross_Debug}",
			"%{Library.SPIRV_Cross_GLSL_Debug}"
		}

    filter "configurations:Release"
        defines "GE_RELEASE"
        runtime "Release"
        optimize "on"

        links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}

    filter "configurations:Dist"
        defines "GE_DIST"
        runtime "Release"
        optimize "on"

        links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "GameEngine/vendor/spdlog/include",
        "GameEngine/src",
        "GameEngine/vendor",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.ImGuizmo}"
    }

    links
    {
        "GameEngine"
    }

    filter "system:windows"
        systemversion "latest"
        buildoptions "/utf-8"
        defines
        {
            "GE_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "GE_DEBUG"
        runtime "Debug"
        symbols "on"

        postbuildcommands
        {
            '{COPY} "%{VULKAN_SDK}/Bin/shaderc_sharedd.dll" "%{cfg.targetdir}"'
        }

    filter "configurations:Release"
        defines "GE_RELEASE"
        runtime "Release"
        optimize "on"

        postbuildcommands
        {
            '{COPY} "%{VULKAN_SDK}/Bin/shaderc_shared.dll" "%{cfg.targetdir}"'
        }

    filter "configurations:Dist"
        defines "GE_DIST"
        runtime "Release"
        optimize "on"

        postbuildcommands
        {
            '{COPY} "%{VULKAN_SDK}/Bin/shaderc_shared.dll" "%{cfg.targetdir}"'
        }


project "Engine-Editor"
    location "Engine-Editor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "GameEngine/vendor/spdlog/include",
        "GameEngine/src",
        "GameEngine/vendor",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.yaml_cpp}",
        "%{IncludeDir.ImGuizmo}"

    }

    links
    {
        "GameEngine"
    }

    filter "system:windows"
        systemversion "latest"
        buildoptions "/utf-8"
        defines
        {
            "GE_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "GE_DEBUG"
        runtime "Debug"
        symbols "on"

        postbuildcommands
        {
            '{COPY} "%{VULKAN_SDK}/Bin/shaderc_sharedd.dll" "%{cfg.targetdir}"'
        }

    filter "configurations:Release"
        defines "GE_RELEASE"
        runtime "Release"
        optimize "on"

        postbuildcommands
        {
            '{COPY} "%{VULKAN_SDK}/Bin/shaderc_shared.dll" "%{cfg.targetdir}"'
        }

    filter "configurations:Dist"
        defines "GE_DIST"
        runtime "Release"
        optimize "on"

        postbuildcommands
        {
            '{COPY} "%{VULKAN_SDK}/Bin/shaderc_shared.dll" "%{cfg.targetdir}"'
        }

project "Engine-ScriptCore"
    location "Engine-ScriptCore"
    kind "SharedLib"
    language "C#"
    dotnetframework "4.8"

    targetdir ("%{wks.location}/Engine-Editor/Resources/Scripts")
	objdir ("%{wks.location}/Engine-Editor/Resources/Scripts/Intermediates")

    files 
	{
		"Source/**.cs",
		"Properties/**.cs"
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