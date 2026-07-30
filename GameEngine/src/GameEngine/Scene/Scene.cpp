#include "gepch.h"
#include "Scene.h"

#include "Components.h"
#include "Entity.h"
#include "GameEngine/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace GameEngine
{
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;

		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;
		GE_CORE_INFO("Destroying entity: {0}", tag.c_str());
		m_Registry.destroy(entity);

		if (!m_Registry.valid(entity))
			GE_CORE_WARN("Entity destroyed");
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// update scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					if (!nsc.Instance)
					{
						nsc.Instance = nsc.InstantiateScript();
						nsc.Instance->m_Entity = Entity{ entity, this };
						nsc.Instance->OnCreate();
					}
					
					nsc.Instance->OnUpdate(ts);
				});
		}


		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransformMatrix;
		glm::mat4* cameraTransform = nullptr;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>(); 
			view.each([&](auto entity, auto& transform, auto& camera)
				{
					if (camera.Primary)
					{
						mainCamera = &camera.Camera;
						cameraTransformMatrix = transform.GetTransform(); 
						cameraTransform = &cameraTransformMatrix;        
					}
				});
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, *cameraTransform);

			m_Registry.view<TransformComponent, SpriteRendererComponent>().each([](auto& transform, auto& sprite)
				{
					//GE_CORE_INFO("Drawing sprite entity");
					Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
				});

			Renderer2D::EndScene();
		}
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// resize non-fixed aspect camera
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
			{
				cameraComponent.Camera.SetViewportSize(width, height);
			}
		}


	}

	Entity Scene::GetPrimaryCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();

		for (auto entity : view)
		{
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.Primary)
				return Entity{ entity, this };
		}
		
		return {};
	}

	uint32_t Scene::GetEntityCount()
	{
		uint32_t count = 0;
		for (auto entity : m_Registry.storage<entt::entity>())
			count++;
		return count;
	}


	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{
		/*m_Registry.view<TransformComponent, SpriteRendererComponent>().each([](auto& transform, auto& sprite)
			{
				Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
			});*/
		
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{
	}

}

