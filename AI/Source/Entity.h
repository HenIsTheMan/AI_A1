#pragma once

#include "EntityAttribs.hpp"

class Entity final{
public:
	Entity();
	Entity(const EntityAttribs& attribs);
	~Entity() = default;

	EntityType& RetrieveType();
	Vector3& RetrievePos();

	///Getters
	const EntityType& GetType() const;
	const Vector3& GetPos() const;
private:
	EntityAttribs im_Attribs;
};