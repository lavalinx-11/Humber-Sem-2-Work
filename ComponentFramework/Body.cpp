#include "Body.h"
#include <QMath.h>
#include <MMath.h>
Body::Body() : pos{}, vel{}, accel{}, mass{ 1.0f }, mesh{ nullptr }, texture{ nullptr } {
}

Body::~Body() {}

void Body::Update(float deltaTime) {
    /// From 1st semester physics class
    pos += vel * deltaTime + 0.5f * accel * deltaTime * deltaTime;
    vel += accel * deltaTime;
}

void Body::ApplyForce(Vec3 force) {
    accel = force / mass;
}

void Body::UpdateOrientation(float deltaTime) {
    //dir of angvel is rotaation axis
    //magn is angle
    float angleRad = VMath::mag(angularVel);
    float angleDeg = angleRad * RADIANS_TO_DEGREES;
    //if angle is zero kill
    if (angleRad < VERY_SMALL) { // no use == 0 for floats 
        return;
    }
    Vec3 axis = VMath::normalize(angularVel);
    Quaternion rotation = QMath::angleAxisRotation((angleDeg * deltaTime), axis);
    orientation = rotation * orientation;

}

void Body::ApplyTorque(Vec3 torque) {
    float test = (2.0f / 5.0f) * mass * (rad * rad);
    if (test < VERY_SMALL) {
        std::cout << "bad" << std::endl;
        return;
    }
    angularAcc = MMath::inverse(rotationalInertia) * torque;

}

void Body::UpdatePos(float deltaTime) {
    pos += vel * deltaTime + 0.5f * accel * deltaTime * deltaTime;
}

void Body::UpdateVel(float deltaTime) {
    vel += accel * deltaTime;
}

const Matrix4 Body::GetModelMatrix() const
{
    Matrix4 T = MMath::translate(pos);
    Matrix4 R = MMath::toMatrix4(orientation);
    Matrix4 S = MMath::scale(Vec3(rad, rad, rad));
    return(T * R * S);
}

void Body::UpdateAngularVel(float deltaTime) {
    angularVel += angularAcc * deltaTime;
}

bool Body::OnCreate() {
    //make rotational inertia in apply torque to make it able to be manipulate
    //
    rotationalInertia.loadIdentity();
    const float sphereI = (2.0f / 5.0f) * mass * (rad * rad);
    rotationalInertia = MMath::scale(sphereI, sphereI, sphereI);
    return true;
}

void Body::OnDestroy() {
}

void Body::Render() const {
}