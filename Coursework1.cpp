#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/MeshGeometry.h"
#include "../../Common/Maths.h"

#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "RasterisationMesh.h"

#include "Renderer.h"

using namespace NCL;
using namespace CSC3223;


//Initialise asteroid
RenderObject* InitAsteroid(Renderer& renderer){
	//Cube
	std::vector<Vector3> verts = {
	Vector3(-1.0f, 1.0f, 1.0f),
	Vector3(1.0f, 1.0f, 1.0f),
	Vector3(-1.0f, -1.0f, 1.0f),
	Vector3(1.0f, -1.0f, 1.0f),

	Vector3(1.0f, -1.0f, -1.0f),
	Vector3(1.0f, 1.0f, 1.0f),
	Vector3(1.0f, 1.0f, -1.0f),
	Vector3(-1.0f, 1.0f, 1.0f),

	Vector3(-1.0f, 1.0f, -1.0f),
	Vector3(-1.0f, -1.0f, 1.0f),
	Vector3(-1.0f, -1.0f, -1.0f),
	Vector3(1.0f, -1.0f, -1.0f),

	Vector3(-1.0f, 1.0f, -1.0f),
	Vector3(1.0f, 1.0f, -1.0f) };

	//Colours. Work with texture to give dark / light spots
	std::vector<Vector4>  colours = { Vector4(0.0, 0.0, 0.0, 1), Vector4(0.1, 0.1, 0.1, 1), Vector4(0.18, 0.18, 0.18, 1),
									  Vector4(0.18, 0.18, 0.18, 1), Vector4(0.18, 0.18, 0.18, 1), Vector4(0.18, 0.18, 0.18, 1),
									  Vector4(0.18, 0.18, 0.18, 1), Vector4(0.0, 0.0, 0.0, 1), Vector4(0.1, 0.1, 0.1, 1),
									  Vector4(0.18, 0.18, 0.18, 1), Vector4(0.15, 0.15, 0.15, 1), Vector4(0.18, 0.18, 0.18, 1),
									  Vector4(0.15, 0.15, 0.15, 1), Vector4(0.18, 0.18, 0.18, 1)};
	OGLMesh* tri = new OGLMesh();
	tri->SetVertexPositions(verts);
	tri->SetVertexColours(colours);
	tri->SetPrimitiveType(GeometryPrimitive::TriangleStrip);

	std::vector<Vector2> texCoords = { Vector2(0, 0), Vector2(1, 0), Vector2(0, 1), Vector2(1, 1),
		Vector2(0, 0), Vector2(1, 0), Vector2(0, 1), Vector2(1, 1),
		Vector2(0, 0), Vector2(1, 0), Vector2(0, 1), Vector2(1, 1),
		Vector2(0, 0), Vector2(1, 0), Vector2(0, 1), Vector2(1, 1), }
;
	tri->SetVertexTextureCoords(texCoords);
	tri->UploadToGPU();

	RenderObject* asteroid = new RenderObject(tri);
	renderer.AddRenderObject(asteroid);

	TextureBase* newTex = OGLTexture::RGBATextureFromFilename("asteroid.png");
	renderer.EnableMipMapFiltering(*(OGLTexture*)newTex);
	asteroid->SetBaseTexture(newTex);

	return asteroid;
}

RenderObject* InitShip(Renderer& renderer) {
	std::vector<Vector3> verts = { Vector3(-1, 0, 1), Vector3(1,0,1), Vector3(0, 0, -1),
									Vector3(-1, 0, 1), Vector3(1, 0, 1), Vector3(0, 0.5, 1),
									Vector3(-1, 0, 1), Vector3(0, 0.5, 1), Vector3(0, 0, -1),
									Vector3(1, 0, 1), Vector3(0, 0.5, 1), Vector3(0, 0, -1) };

	std::vector<Vector4>  colours = { Vector4(1, 0, 0, 1), Vector4(1, 0, 0, 1), Vector4(0, 0, 1, 1),
								Vector4(1, 0, 0, 1), Vector4(1, 0, 0, 1), Vector4(0, 0, 1, 1),
								Vector4(1, 0, 0, 1), Vector4(0, 0, 1, 1), Vector4(0, 0, 1, 1),
								Vector4(1, 0, 0, 1), Vector4(0, 0, 1, 1), Vector4(0, 0, 1, 1)};


	OGLMesh* tri = new OGLMesh();
	tri->SetVertexPositions(verts);
	tri->SetVertexColours(colours);
	tri->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri->UploadToGPU();

	RenderObject* renderObj = new RenderObject(tri);

	renderer.AddRenderObject(renderObj);

	return renderObj;
}

void InitStarField(Renderer& renderer) {
	OGLMesh* points = new OGLMesh();

	//Colour to full white
	std::vector<Vector4>  colours = { Vector4(1, 1, 1, 1) };

	points->SetVertexPositions({ Vector3(0, 0, 0)});
	points->SetPrimitiveType(GeometryPrimitive::Points);
	points->SetVertexColours(colours);
	points->UploadToGPU();

	//Generate points field
	for (int y = -40; y < 30; ++y) {
		for (int x = -40; x < 30; ++x) {
			float zAmount = rand() % 50;

			Matrix4 translate = Matrix4::Translation(Vector3(((x + 1) * 10), (y + 1) * 10, -50 - zAmount));

			renderer.AddRenderObject(new RenderObject(points, translate));
		}
	}

	renderer.AddRenderObject(new RenderObject(points));
}


int main() {
	Window*w = Window::CreateGameWindow("CSC3223 Coursework 1!");

	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer* renderer = new Renderer(*w);

	//Set background to black. We ARE in space.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	InitStarField(*renderer);
	RenderObject* asteroid = InitAsteroid(*renderer);
	RenderObject* ship = InitShip(*renderer);

	//set up proj matrix
	float aspect = w->GetScreenAspect();
	Matrix4 proj = Matrix4::Perspective(1.0f, 1000.0f, aspect, 45.0f);

	Vector3 viewPosition(0, 0, 0);
	Vector3 shipPosition(0, 0, -10);
	Vector3 rotation(0, 0, 0);

	Vector3 asteroidPosition(0, 0, -15);
	float asteroidRotation = 0.0f;

	float velocity = 0.0f;
	renderer->EnableDepthBuffer(true);
	renderer->EnableBlending(true);
	renderer->SetBlendToLinear();
	bool depthState = true;
	bool blendingState = true;

	//TODO: Bad way to do game loop. Update this
	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		float time = w->GetTimer()->GetDeltaTime();

		renderer->Update(time);

		renderer->DrawString("Coursework 1", Vector2(10, 10));

		renderer->Render();

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NEXT)) {
			w->ShowConsole(false);
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_HOME)) {
			w->SetFullScreen(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_END)) {
			w->SetFullScreen(false);
		}

		if (Window::GetKeyboard()->KeyHeld(KEYBOARD_SHIFT)) {
			velocity = 10;
		}
		else if (Window::GetKeyboard()->KeyHeld(KEYBOARD_CONTROL)) {
			velocity = -5;
		}
		else {
			velocity = 0;
		}
		if (Window::GetKeyboard()->KeyHeld(KEYBOARD_A)) {
			rotation.z += 50 * time;
		}
		if (Window::GetKeyboard()->KeyHeld(KEYBOARD_D)) {
			rotation.z -= 50 * time;
		}
		if (Window::GetKeyboard()->KeyHeld(KEYBOARD_W)) {
			rotation.x -= 50 * time;
		}
		if (Window::GetKeyboard()->KeyHeld(KEYBOARD_S)) {
			rotation.x += 50 * time;
		}


		//DEPTH
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F1)) {
			depthState = !depthState;
			renderer->EnableDepthBuffer(depthState);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F2)) {
			renderer->SetDepthTestToLEqual();
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F3)) {
			renderer->SetDepthTestToAlways();

		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F4)) {
			renderer->SetDepthTestToGreater();

		}

		//BLENDING
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F5)) {
			blendingState = !blendingState;
			renderer->EnableBlending(blendingState);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F6)) {
			renderer->SetBlendToLinear();
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F7)) {
			renderer->SetBlendToAdditive();
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F8)) {
			renderer->SetBlendToInvert();
		}

		//Rotate and translate asteroid
		asteroidRotation += 10 * time;
		asteroidPosition.z -= time * 0.5;

		asteroid->SetTransform(Matrix4::Translation((asteroidPosition)) * Matrix4::Rotation(asteroidRotation, Vector3(0, 1, 0)));

		Matrix4 zAxis = Matrix4::Rotation(rotation.z, Vector3(0, 0, 1));
		Matrix4 xAxis = Matrix4::Rotation(rotation.x, Vector3(1, 0, 0));

		//Ideally put this in own method or convert to use matrix
		shipPosition.y += sin(DegreesToRadians(rotation.x)) * cos(DegreesToRadians(rotation.z)) * velocity * time;
		shipPosition.z -= cos(DegreesToRadians(rotation.x)) * velocity * time;
		shipPosition.x -= sin(DegreesToRadians(rotation.z)) * sin(DegreesToRadians(rotation.x)) * velocity * time;

		//Move and rotate ship
		ship->SetTransform(Matrix4::Translation(shipPosition) * zAxis * xAxis);

		//Set camera to origin of ship and rotate
		viewPosition.y = -shipPosition.y;
		viewPosition.x = -shipPosition.x;
		viewPosition.z = -shipPosition.z - 10;

		//TODO: Camera follow. Currently only tracks z movement

		renderer->SetViewMatrix(Matrix4::Translation(viewPosition));
		renderer->SetProjectionMatrix(proj);

		w->SetTitle("Coursework 1");
	}

	delete renderer;
	delete asteroid;
	delete ship;

	Window::DestroyGameWindow();
}