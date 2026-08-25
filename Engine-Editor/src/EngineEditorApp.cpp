#include <GameEngine.h>
#include <GameEngine/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"
#include "EditorLayer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace GameEngine
{
	class EngineEditor : public Application
	{
	public:
		EngineEditor(const ApplicationSpecification& spec)
			: Application(spec)
		{
			PushLayer(new EditorLayer());
		}

		~EngineEditor()
		{

		}
	};


	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "EngineEditor";
		spec.CommandLineArgs = args;
		return new EngineEditor(spec);
	}
}

