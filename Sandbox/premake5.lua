
project "Sandbox"
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
        "%{wks.location}/GameEngine/vendor/spdlog/include",
        "%{wks.location}/GameEngine/src",
        "%{wks.location}/GameEngine/vendor",
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
