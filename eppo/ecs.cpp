#include "ecs.h"

#include <iostream>

void Component::update()
{
}

void Component::on_delete()
{
}

Entity::Entity()
{
	// empty
}

Entity::~Entity()
{
	for (Component* component : components)
	{
		component->on_delete();
	}
}

const std::string& Entity::get_name() const
{
	return name;
}

void Entity::add_component(Component* component)
{
	components.push_back(component);
}

void Entity::update()
{
	for (Component* component : components)
	{
		component->update();
	}

	on_update();
}

void Entity::on_update()
{

}

void Entity::draw()
{
}

ECS::~ECS()
{
	std::cout << "ECS Shutdown\n";
}

void ECS::add_entity(Entity* entity)
{
	entities.push_back(std::shared_ptr<Entity>(entity));
}

void ECS::update()
{
	for (int i = 0; i < entities.size(); i++)
	{
		Entity* entity = entities[i].get();

		if (entity->should_remove == false)
		{
			entity->update();
		}
		else
		{
			entities.erase(entities.begin() + i);
		}
	}
}

void ECS::draw()
{
	for (auto ent : entities)
	{
		ent.get()->draw();
	}
}