#pragma once

#include <string>
#include <vector>
#include <memory>

class Component
{
public:
	virtual void update();
	virtual void on_delete();
};

class Entity
{
public:
	Entity();
	virtual ~Entity();
	const std::string& get_name() const;
	void add_component(Component* component);
	void update();
	virtual void draw();
	bool should_remove = false;
protected:
	virtual void on_update();
	std::string name = "Generic Entity";
	std::vector<Component*> components;
};

class ECS
{
public:
	~ECS();
	void add_entity(Entity* entity);
	void update();
	void draw();
private:
	std::vector<std::shared_ptr<Entity>> entities;
};