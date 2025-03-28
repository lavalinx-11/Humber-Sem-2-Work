#pragma once
#include <Vector.h>
#include <iostream>
#include <VMath.h>
#include <MMath.h>
using namespace MATH;
using namespace std;


class Light {
	//needs 2 vec4s and a vec3
	//vec4 for types of light
	//vec3 for light pos
	//needs to be an array to be able to pass on multiple lights simultaneously
	//needs to be able to be stored in a UBO
public:
	
	Vec3 litPos;
	Vec4 DifColour;
	Vec4 SpecColour;
	Light();
	Light(Vec3 lightP, Vec4 KD, Vec4 KS);
};