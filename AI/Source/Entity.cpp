#include "Entity.h"

Entity::Entity():
	Entity(EntityAttribs())
{
}

Entity::Entity(const EntityAttribs& attribs):
	im_Attribs(attribs)
{
}

Vector3& Entity::RetrieveLocalPos(){
	return im_Attribs.im_LocalPos;
}

Vector3& Entity::RetrieveLocalScale(){
	return im_Attribs.im_LocalScale;
}

const EntityType& Entity::GetType() const{
	return im_Attribs.im_Type;
}

const Vector3& Entity::GetLocalPos() const{
	return im_Attribs.im_LocalPos;
}

const Vector3& Entity::GetLocalScale() const{
	return im_Attribs.im_LocalScale;
}

void Entity::SetType(const EntityType type){
	im_Attribs.im_Type = type;
}

void Entity::SetLocalPos(const Vector3& pos){
	im_Attribs.im_LocalPos = pos;
}

void Entity::SetLocalPos(const float x, const float y, const float z){
	im_Attribs.im_LocalPos = Vector3(x, y, z);
}

void Entity::SetLocalScale(const Vector3& scale){
	im_Attribs.im_LocalScale = scale;
}

void Entity::SetLocalScale(const float x, const float y, const float z){
	im_Attribs.im_LocalScale = Vector3(x, y, z);
}