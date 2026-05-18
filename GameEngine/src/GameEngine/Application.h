#pragma once

#include "Core.h"

#include "Window.h"
#include "Events/Event.h"
#include "GameEngine/LayerStack.h"
#include "GameEngine/Events/ApplicationEvent.h"

#include "GameEngine/ImGui/ImGuiLayer.h"

#include "GameEngine/Renderer/Shader.h"
#include "GameEngine/Renderer/Buffer.h"
#include "GameEngine/Renderer/VertexArray.h"

namespace GameEngine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }

		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<VertexArray> m_SquareVA;

	private:
		static Application* s_Instance;
	};

	// To be defined in Client
	Application* CreateApplication();
}


