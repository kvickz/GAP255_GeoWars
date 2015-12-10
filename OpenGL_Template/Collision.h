//Collision.h

#ifndef COLLISION_H
#define COLLISION_H

#include "Vector3.h"

struct Collision
{
    Vector3 m_force;
    Vector3 m_direction;

    Collision(Vector3 force)
    {
        m_force = force;
        m_direction = m_force.Normalized();
    }
};

#endif // !COLLISION_H
