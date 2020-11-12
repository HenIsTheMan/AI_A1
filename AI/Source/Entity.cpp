#include "Entity.h"

Entity::Entity():
	Entity(EntityAttribs())
{
}

Entity::Entity(const EntityAttribs& attribs):
	im_Attribs(attribs)
{
}

EntityType& Entity::RetrieveType(){
	return im_Attribs.im_Type;
}

Vector3& Entity::RetrievePos(){
	return im_Attribs.im_Pos;
}

Vector3& Entity::RetrieveScale(){
	return im_Attribs.im_Scale;
}

const EntityType& Entity::GetType() const{
	return im_Attribs.im_Type;
}

const Vector3& Entity::GetPos() const{
	return im_Attribs.im_Pos;
}

const Vector3& Entity::GetScale() const{
	return im_Attribs.im_Scale;
}

void Entity::SetType(const EntityType type){
	im_Attribs.im_Type = type;
}

void Entity::SetPos(const Vector3& pos){
	im_Attribs.im_Pos = pos;
}

void Entity::SetPos(const float x, const float y, const float z){
	im_Attribs.im_Pos = Vector3(x, y, z);
}

void Entity::SetScale(const Vector3& scale){
	im_Attribs.im_Scale = scale;
}

void Entity::SetScale(const float x, const float y, const float z){
	im_Attribs.im_Scale = Vector3(x, y, z);
}