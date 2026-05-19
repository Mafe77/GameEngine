#include <GameEngine.h>

class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{

		m_VertexArray.reset(GameEngine::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		std::shared_ptr<GameEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(GameEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

		GameEngine::BufferLayout layout = {
			{GameEngine::ShaderDataType::Float3, "a_Position"},
			{GameEngine::ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };

		std::shared_ptr<GameEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(GameEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}			
			
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}			
			
		)";

		m_Shader.reset(new GameEngine::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate(GameEngine::Timestep ts) override
	{
		if (GameEngine::Input::IsKeyPressed(GE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed * ts;
		else if (GameEngine::Input::IsKeyPressed(GE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed * ts;

		if (GameEngine::Input::IsKeyPressed(GE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed * ts;
		else if (GameEngine::Input::IsKeyPressed(GE_KEY_UP))
			m_CameraPosition.y += m_CameraSpeed * ts;


		if (GameEngine::Input::IsKeyPressed(GE_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (GameEngine::Input::IsKeyPressed(GE_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		GameEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		GameEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		GameEngine::Renderer::BeingScene(m_Camera);

		GameEngine::Renderer::Submit(m_Shader, m_VertexArray);

		GameEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(GameEngine::Event& event) override
	{

	}

private:
	std::shared_ptr<GameEngine::Shader> m_Shader;
	std::shared_ptr<GameEngine::VertexArray> m_VertexArray;

	GameEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
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
