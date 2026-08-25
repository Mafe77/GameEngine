#pragma once

#include "Core.h"

#include "Window.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Core/LayerStack.h"
#include "GameEngine/Events/ApplicationEvent.h"

#include "GameEngine/Core/Timestep.h"
#include "GameEngine/ImGui/ImGuiLayer.h"


namespace GameEngine
{
	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			GE_CORE_ASSERT(index < Count, "AppCommandArgs");
			return Args[index];
		}
	};

	struct ApplicationSpecification
	{
		std::string Name = "Engine Application";
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& specification);
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }

		const ApplicationSpecification& GetSpecificiation() const { return m_Specification; }

		inline Window& GetWindow() { return *m_Window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		ApplicationSpecification m_Specification;
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in Client
	Application* CreateApplication(ApplicationCommandLineArgs args);
}


