#include "pch.h"
#include "Scene.h"

#include "Entity.h"
#include "Components.h"
#include "Irene/Renderer/Renderer3D.h"

#include <glm/glm.hpp>

namespace irene {

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
		auto& tag = entity.AddComponent<TagComponent>(name);
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		//auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		//for (auto& entity : group)
		//{
		//	auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
		//	Renderer3D::DrawCube(transform, sprite.Color);
		//}
	}
	
}