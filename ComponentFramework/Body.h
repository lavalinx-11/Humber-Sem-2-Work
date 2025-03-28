#ifndef BODY_H
#define BODY_H
#include <Vector.h> /// This is in GameDev
#include <Quaternion.h>
using namespace MATH; 

/// Just forward declair these classes so I can define a pointer to them
/// Used later in the course
class Mesh;
class Texture;

class Body {
public:
    Body();
    ~Body();
/// Physics stuff
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	Vec3 angularAcc;
	Vec3 angularVel; // uses rad/s Points along rotaional axis. Magnitude it angular speed
	Quaternion orientation;
	Matrix3 rotationalInertia;
	float mass = 1;
	float rad = 1;

private: /// Graphics stuff 
	Mesh *mesh;
	Texture *texture;
	
public:
	bool OnCreate();
	void OnDestroy();
	void Update(float deltaTime);
	void Render() const;
	void ApplyForce(Vec3 force);
	//void setAccel(const Vec3 &accel_) { accel = accel_;}
	void UpdateOrientation(float deltaTime);
	// Updates angular acceleration using torque and rotational inertia
	void ApplyTorque(Vec3 torque);
	// Updates angular velocity using rotational equations of motion
	void UpdateAngularVel(float deltaTime);
	// Updates orientation quaternion using the angular velocity
	// Update position or velocity using the equations of motion. It's handy later on with constraints to have these as separate methods
	
	void UpdatePos(float deltaTime);
	void UpdateVel(float deltaTime);
	// Build a model matrix to send to the GPU
	const Matrix4 GetModelMatrix() const;
};

#endif
