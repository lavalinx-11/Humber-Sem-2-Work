#pragma once
#ifndef SCENE4G_H
#define SCENE4G_H
#include "Scene.h"
#include <Vector.h>
#include <Matrix.h>
#include "Trackball.h"
#include "Camera.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Body;
class Mesh;
class Shader;
class Texture;

class Scene4g : public Scene {
private:
	Body* sub;
	Shader* tesselationShader;
	Shader* reflectionShader;
	Mesh* mesh;
	Body* terrain;
	Mesh* terrainMesh;
	Matrix4 terrainModelMatrix;
	Texture* terrainTexture;
	Texture* heightMap;
	float tessLevel = 1.0f;
	Texture* texture;
	Matrix4 modelMatrix;
	bool drawInWireMode;
	Trackball trackball;
	Vec4 Diffuse[5];
	Vec4 Specular[5];
	Vec3 Litpos[5];
	Camera* cam;

public:
	explicit Scene4g();
	virtual ~Scene4g();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE4G_H