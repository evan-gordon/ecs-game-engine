//Evan Gordon

#include "c_TargetEntity.h"

c_TargetEntity::c_TargetEntity()
	:isLinked(false), target(NULL)
{}

c_TargetEntity::c_TargetEntity(c_WorldObject& target)
	:isLinked(true), target(&target)
{}

c_TargetEntity::~c_TargetEntity()
{}