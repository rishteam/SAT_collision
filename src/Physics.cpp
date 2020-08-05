#include "Physics.h"

Physics::Physics(){
    mass = 10;
    velocity = Vec2(1.0, -1.0);
    angularVelocity = 0;
    force = Vec2(0.0, 0.0);
    torque = 0;
}

void Physics::print_Physics_info()
{
    fmt::print("[Physics]\nVelocity:\n");
    velocity.print_Vector();
    fmt::print("mass: {}\n", mass);
    fmt::print("angularVelocity: {}\n", angularVelocity);
}

std::pair<Vec2, float> Physics::getPhysicsData()
{
    return std::make_pair(position, angle);
}

float Physics::getMass()
{
    return mass;
}

float Physics::getfriction()
{
    return friction;
}


void Physics::AddForce(const Vec2& f)
{
    force += f;
}

void Physics::TransformPhysicsCoordinate(const Vec2 ps, float angle_)
{
    this->position = ps;
    this->angle = angle_;
}

void Physics::ComputeForce(float delta_t, Vec2 gravity)
{
    if (this->invMass == 0.0f)
        return;
    else
    {
        this->velocity += delta_t * (gravity + this->invMass * this->force);
        this->angularVelocity += delta_t * this->invI * this->torque;
    }
}

void Physics::IntegrateVelocities(float delta_t)
{
    auto tmp = delta_t * velocity;
    position += tmp;
    auto tmp2 = delta_t * angularVelocity;
    angle += tmp2;

    this->force.Set(0.0f, 0.0f);
    this->torque = 0.0f;
}

