#include "Camera.h"
#include <SDL.h>
#include <MMath.h>
#include <glew.h>
#include "Debug.h"
#include "Mesh.h"
#include "Shader.h"
#include "Body.h"
#include <SDL_image.h>
Camera::Camera() {
	projection = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 10000.0f);
	orientation = Quaternion(1.0f, Vec3(0.0f, 0.0f, 0.0f));
	position = Vec3(0.0f, 0.0f, -25.0f);
	view = MMath::toMatrix4(orientation) * MMath::translate(position);

}

void Camera::dontTrackY() {

	trackball.XaxisLock = false;
	trackball.ZaxisLock = false;
}

void Camera::SetView(const Quaternion& orientation_, const Vec3& position_) {
	orientation = orientation_;
	position = position_;
}

void Camera::OnDestroy() {
	if (skybox) {
		skybox->OnDestroy();
		delete skybox;
	}
}

Camera::~Camera() {}

bool Camera::OnCreate() {//uses default skybox setup
	skybox = new SkyBox("textures/StarSkyboxPosx.png",
						"textures/StarSkyboxPosy.png",
						"textures/StarSkyboxPosz.png",
						"textures/StarSkyboxNegx.png",
						"textures/StarSkyboxNegY.png",
						"textures/StarSkyboxnegz.png");
	std::cout << "working " << std::endl;
	
	if (skybox->OnCreate() == false) {
		return false;
	}
	return true;

}
//has a dynamic skybox setup which allows me to input any skybox I want while setting up the scene going through the camera
bool Camera::SkySetup(const char* posXFileName_, const char* posYFileName_, const char* posZFileName_, const char* negXFileName_, const char* negYFileName_, const char* negZFileName_) {
	
	skybox = new SkyBox(posXFileName_,
						posYFileName_,
						posZFileName_,
						negXFileName_,
						negYFileName_,
						negZFileName_);
	if (skybox->OnCreate() == false) {
		return false;
	}
	return true;
}



void Camera::HandelEvents(const SDL_Event& sdlEvent) {
	trackball.HandleEvents(sdlEvent);
	orientation = trackball.getQuat();
}

/// Our PASS tutor didn't like the name Render since it can't render itself. 
/// I hope this meets with his approval
void Camera::RenderSkyBox() const{
	if (skybox == nullptr) return;
	//depth test makes it so the things farther away are aren't drawn or shown
	glDisable(GL_CULL_FACE);//turns off depth test so that things that are within it are visible
	//cull face is a way of performance gain in opengl. "If you're seeing a texture/triangle that's going clockwise then it's backwards so it doesn't draw it to save performance
	glDisable(GL_DEPTH_TEST);
	glUseProgram(skybox->GetShader()->GetProgram());//goes through the skybox class to get the program id and turn on the shader
	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("projectionMatrix"), 1, GL_FALSE, projection);//gets the projection matrix
	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("viewMatrix"), 1, GL_FALSE, MMath::toMatrix4(orientation));
	/// Here I has turned on the shader and set the matricies. The shader will remain in this state
	/// until I turn off the shader. In Skybox::Render, I will bind the textures, because that is where
	/// they are, then draw the cube.  
	skybox->Render();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glUseProgram(0);
}