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
		EngineEditor(ApplicationCommandLineArgs args)
			: Application("Engine Editor", args)
		{
			PushLayer(new EditorLayer());
		}

		~EngineEditor()
		{

		}
	};


	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new EngineEditor(args);
	}
}

