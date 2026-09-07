
VULKAN_SDK = os.getenv("VULKAN_SDK")

-- Include directories relative to the root folder (sol dir)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/GameEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/GameEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/GameEngine/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/GameEngine/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/GameEngine/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/GameEngine/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/GameEngine/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/GameEngine/vendor/ImGuizmo"
IncludeDir["shaderc"] = "%{wks.location}/GameEngine/vendor/shaderc/include"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/GameEngine/vendor/SPIRV-Cross"
IncludeDir["Box2D"] = "%{wks.location}/GameEngine/vendor/Box2D/include"
IncludeDir["mono"] = "%{wks.location}/GameEngine/vendor/mono/include"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"] = "%{VULKAN_SDK}/Lib"

LibraryDir["mono"] = "%{wks.location}/GameEngine/vendor/mono/lib/%{cfg.buildcfg}"

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