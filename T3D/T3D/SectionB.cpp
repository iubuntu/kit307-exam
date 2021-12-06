
#include "SectionB.h"
#include "Camera.h"
#include "KeyboardController.h"
#include "RotateBehaviour.h"
#include "GLShader.h"
#include "Sphere.h"
#include "Animation.h"
#include <vector>

#include "GLRenderer.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "KeyboardController.h"
#include <string>


//#include "AnimationTest.h"
//#include "LookAtBehaviour.h"

#include "ExamSound.h"
#include "Terrain.h"
#include "Billboard.h"
#include "ParticleEmitter.h"
#include "ParticleGravity.h"
#include "LookAtBehaviour.h"
#include "Clock.h"


#include "Tablet.h"
#include "ExamAnimation.h"
#include "DrawTask.h"
namespace T3D {

	SectionB::SectionB(void)
	{
		QuaternionNumber = 0;
		drawTask = nullptr;
		drawArea = new Texture(1024, 640, false);
		drawArea->clear(Colour(255, 255, 255, 255));
	}


	SectionB::~SectionB(void)
	{
	}


	Quaternion SectionB::GetShoulderQuaternion() {
		Quaternion q;
		if (QuaternionNumber % 2 == 0) {
			q = Quaternion(Vector3(0, 0, 0));
		}
		else {
			if (QuaternionNumber % 4 == 1) {
				q = Quaternion(Vector3(0, 270 * Math::DEG2RAD, 0));
			}
			else {
				q = Quaternion(Vector3(0, -270 * Math::DEG2RAD, 0));
			}

		}
		QuaternionNumber++;
		return q;

	}



	bool SectionB::init() {
		WinGLApplication::init();



		//Create a skybox and add some fog
		renderer->loadSkybox("Resources/dsb");
		renderer->setFog(0.007f, 0.8f, 0.8f, 0.8f, 1.0f);
		renderer->toggleFog();

		//Add a light
		GameObject* lightObj = new GameObject(this);
		Light* light = new Light(Light::Type::DIRECTIONAL);
		light->setAmbient(1, 1, 1);
		light->setDiffuse(1, 1, 1);
		light->setSpecular(1, 1, 1);
		lightObj->setLight(light);
		//lightObj->getTransform()->setLocalRotation(Vector3(-45 * Math::DEG2RAD, 70 * Math::DEG2RAD, 0));
		lightObj->getTransform()->setParent(root);

		//Create some basic materials
		Material* red = renderer->createMaterial(Renderer::PR_OPAQUE);
		red->setDiffuse(1, 0, 0, 1);
		Material* green = renderer->createMaterial(Renderer::PR_OPAQUE);
		green->setDiffuse(0, 1, 0, 1);
		Material* blue = renderer->createMaterial(Renderer::PR_OPAQUE);
		blue->setDiffuse(0, 0, 1, 1);

		//Create some textured materials (using texture files)
		Texture* smileytex = new Texture("Resources/Smiley.bmp", true, true);
		renderer->loadTexture(smileytex);
		Material* smiley = renderer->createMaterial(Renderer::PR_OPAQUE);
		smiley->setTexture(smileytex);

		Texture* sparkletex = new Texture("Resources/sparkle.png", true, true);
		renderer->loadTexture(sparkletex);
		Material* sparklemat = renderer->createMaterial(Renderer::PR_TRANSPARENT);
		sparklemat->setEmissive(1, 1, 1, 1);
		sparklemat->setBlending(Material::BlendMode::DEFAULT);
		sparklemat->setSortedDraw(true, false);
		sparklemat->setTexture(sparkletex);

		//Create a textured material by adding text
		Texture* texttex = new Texture(256, 32);
		texttex->clear(Colour(255, 255, 255, 255));
		font* f = getFont("resources/FreeSerifBold.ttf", 24);
		if (f != NULL) {
			texttex->writeText(2, 0, "Hickory", Colour(0, 255, 0, 255), f->getFont());
			texttex->writeText(64, 0, " Dickory Dock", Colour(255, 12, 0, 0), f->getFont());
		}
		renderer->loadTexture(texttex, true);
		Material* textmat = renderer->createMaterial(Renderer::PR_OPAQUE);
		textmat->setTexture(texttex, 1);
		textmat->setEmissive(1, 1, 1, 1);

		//Create a material with a procedurally generated texture
		Texture* proctex = new Texture(512, 512);
		proctex->createFractal(Colour(40, 150, 50, 255), Colour(120, 220, 100, 255), 25.0f, false);
		renderer->loadTexture(proctex, true);
		Material* procmat = renderer->createMaterial(Renderer::PR_TERRAIN);
		procmat->setTexture(proctex, 50);
		procmat->setSpecular(0, 0, 0, 0);

		//Create a camera
		GameObject* camObj = new GameObject(this);
		renderer->camera = new Camera(0.3, 300.0, 45.0, 1.6);
		camObj->getTransform()->setLocalPosition(Vector3(0, 0, 50));
		//camObj->getTransform()->setLocalRotation(Quaternion(Vector3(0, 180 * Math::DEG2RAD, 0)));

		camObj->setCamera(renderer->camera);
		camObj->getTransform()->setParent(root);




		//Add a controller to the camera object
		camObj->addComponent(new KeyboardController());

		//Add some terrain
		GameObject* terrain = new GameObject(this);
		Terrain* terrainComponent = new Terrain();
		terrain->addComponent(terrainComponent);
		terrainComponent->createFractalTerrain(256, 500, 15, 2.0); // procedurally generate terrain
		terrain->setMaterial(procmat);
		terrain->getTransform()->setLocalPosition(Vector3(0, -20, 0));
		terrain->getTransform()->setParent(root);
		terrain->getTransform()->name = "Terrain";

		//Add a welcome message
		GameObject* billboard = new GameObject(this);
		Billboard* billboardComponent = new Billboard(renderer->camera->gameObject->getTransform(), true);
		billboard->addComponent(billboardComponent);
		billboard->setMaterial(textmat);			// hello world
		billboard->getTransform()->setLocalPosition(Vector3(0, 15, 0));
		billboard->getTransform()->setLocalScale(Vector3(6, 1.5, 1));
		billboard->getTransform()->setParent(root);
		billboard->getTransform()->name = "Billboard";


		{ // 3d clock



			Material* grey = renderer->createMaterial(Renderer::PR_OPAQUE);
			grey->setDiffuse(0.8, 0.8, 0.9, 1);

			GameObject* clock = new GameObject(this);
			clock->setMesh(new Clock(
				10,
				1,
				0.5
			
			));
			clock->setMaterial(grey);

			clock->getTransform()->setParent(root);
			clock->getTransform()->setLocalPosition(Vector3(0, 0, 0));


			clock->getTransform()->name = "clock";
			clock->getTransform()->setLocalRotation(Vector3(180 * Math::DEG2RAD, 0,0));


			// Other 3D techniques
			addTask(new ExamSound(this));

			//em->getTransform()->setLocalRotation(Vector3(0,0,90 * Math::DEG2RAD));
			//em->addComponent(new LookAtBehaviour(camObj->getTransform()));


		}




		return true;
	}
}
