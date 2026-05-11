#include <GameEngine.h>

class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (GameEngine::Input::IsKeyPressed(GE_KEY_TAB))
			GE_INFO("Tab key is pressed");
	}

	void OnEvent(GameEngine::Event& event) override
	{
		//GE_TRACE("{0}", event);
	}
};

class Sandbox : public GameEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};


GameEngine::Application* GameEngine::CreateApplication()
{
	return new Sandbox();
}
