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
	class Application
	{
	public:
		Application(const std::string& name = "Game Engine");
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }

		inline Window& GetWindow() { return *m_Window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
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
	Application* CreateApplication();
}


