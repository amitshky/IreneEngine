#include "pch.h"
#include "Entity.h"

namespace irene {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{

	}

}
