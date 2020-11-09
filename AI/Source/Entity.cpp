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

const EntityType& Entity::GetType() const{
	return im_Attribs.im_Type;
}

const Vector3& Entity::GetPos() const{
	return im_Attribs.im_Pos;
}