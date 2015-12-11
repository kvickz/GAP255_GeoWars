//Collision.h

#ifndef COLLISION_H
#define COLLISION_H

#include "Vector3.h"

#include "Constants.h"

struct Collision
{
    ObjectID m_objectID;
    Vector3 m_force;
    Vector3 m_direction;
    Vector3 m_position;

    Collision(Vector3 force, Vector3 position, ObjectID objectID)
        :m_objectID(objectID)
        , m_position(position)
        , m_force(force)
    {
        m_direction = m_force.Normalized();
    }
};

#endif // !COLLISION_H
