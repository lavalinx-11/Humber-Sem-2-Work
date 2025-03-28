#include "Light.h"

Light::Light() {
	litPos = Vec3(0.0f, 0.0f, 0.0f);
	DifColour = Vec4(0.6f, 0.6f, 0.3f, 0.0f);
	SpecColour = Vec4(0.3f, 0.3f, 0.3f, 0.0f);
}

Light::Light(Vec3 lightP, Vec4 KD, Vec4 KS) {
	litPos = lightP;
	DifColour = KD;
	SpecColour = KS;
}
