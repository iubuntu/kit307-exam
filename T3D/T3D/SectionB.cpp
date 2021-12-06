
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
#include "Clock.h"
#include "ExamSound.h"
#include "Terrain.h"
#include "Billboard.h"
#include "ParticleEmitter.h"
#include "ParticleGravity.h"
#include "LookAtBehaviour.h"
#include "Cube.h"
#include "ClockAnimation.h"
#include "DrawTask.h"
namespace T3D {

	SectionB::SectionB(void)
	{
		drawTask = nullptr;
		drawArea = new Texture(1024, 640, false);
		drawArea->clear(Colour(255, 255, 255, 255));
	}


	SectionB::~SectionB(void)
	{
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
		lightObj->getTransform()->name = "light";
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
		camObj->getTransform()->name = "camobj";
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


		{ // 3d moon and cow

			/*
			[x] Sweeps
			[x] Custom meshes
			[x] Compound objects
			[x] Textured objects
			[ ] Shaders
			[x] Transparency effects
			[x] Keyframe and other animation techniques
			[x] Other 3D techniques
			*/

			Material* grey = renderer->createMaterial(Renderer::PR_OPAQUE);
			grey->setDiffuse(0.8, 0.8, 0.9, 1);

			Material* transparencyMaterial = renderer->createMaterial(Renderer::PR_TRANSPARENT);
			transparencyMaterial->setDiffuse(0.8, 0.8, 0.9, 1);

			// Transparency effects

			GLShader* transparencyShader = new GLShader("Resources/transparencyVector.shader", "Resources/transparencyFrag.shader");
			transparencyShader->compileShader();
			transparencyMaterial->setShader(transparencyShader);


			// Shader
			/*
			
			Material* changeMaterial = renderer->createMaterial(Renderer::PR_TRANSPARENT);
			changeMaterial->setDiffuse(0.8, 0.8, 0.9, 1);

			GLShader* changeShader = new GLShader("Resources/changeVert.shader", "Resources/changeFrag.shader");
			changeShader->compileShader();
			changeMaterial->setShader(changeShader);
			
			*/




			// clock

			// sweeps 			==> Clock.cpp
			// Custom meshes	==> ClockBase.cpp
			// Compound objects ==> Clock.cpp

			float size = 10;
			int clockMaxSize = sqrt(size * size * 2)+1;

			Clock* clock = new Clock(this,size);
			clock->getTransform()->setLocalPosition(Vector3(0, size, 0));
			clock->getTransform()->setParent(root);
			clock->getTransform()->name = "clock";

			clock->setTransparencyEffect(transparencyMaterial);

			// texture obj	1
			Texture* clockTexture = new Texture("Resources/clockFace.png", true, true);
			renderer->loadTexture(clockTexture);
			Material* faceMaterial = renderer->createMaterial(Renderer::PR_OPAQUE);
			faceMaterial->setTexture(clockTexture);

			// texture obj	2
			Texture* mouseTexture = new Texture("Resources/mouse.png", true, true);
			renderer->loadTexture(mouseTexture);
			Material* mouseMaterial = renderer->createMaterial(Renderer::PR_OPAQUE);
			mouseMaterial->setTexture(mouseTexture);



			int mouseSize = 2;
			GameObject* mouse = new GameObject(this);
			mouse->setMesh(new Cube(mouseSize));

			mouse->getTransform()->setParent(root);
			mouse->getTransform()->setLocalPosition(Vector3(0, 0, 0));


			mouse->getTransform()->setLocalRotation(Vector3(90 *Math::DEG2RAD,0, 0));
			mouse->getTransform()->name = "mouse";
			mouse->setMaterial(mouseMaterial);
			Animation* anim = new Animation(15.0);
			mouse->addComponent(anim);



			clock->setMaterials(grey);
			clock->setFace(faceMaterial);


			//Add a cube to act as a source for particle system


			// A simple fireworks fountain using the particle system
			ParticleEmitter* particleSys = new ParticleEmitter(10.0f, 1.0f, 20.0f, 2.0f, 3.0f, 3.0f);
			mouse->addComponent(particleSys);			// make cube source of particles



			// Keyframe and	 other animation techniques
			
			anim->addKey("mouse", 0, Quaternion(Vector3(90 * Math::DEG2RAD, 0, 0)), Vector3(-clockMaxSize - mouseSize, size, 0));
			anim->addKey("mouse", 3, Quaternion(Vector3(90 * Math::DEG2RAD, 0, 0)), Vector3(-clockMaxSize - mouseSize, 2*size, 0));
			anim->addKey("mouse", 6, Quaternion(Vector3(90 * Math::DEG2RAD, 0, -45 * Math::DEG2RAD)), Vector3(-0, 3* size, 0));
			anim->addKey("mouse", 9, Quaternion(Vector3(90 * Math::DEG2RAD, 0, -90 * Math::DEG2RAD)), Vector3(clockMaxSize + mouseSize, 2*size, 0));
			anim->addKey("mouse", 12, Quaternion(Vector3(90 * Math::DEG2RAD, 0, -180 * Math::DEG2RAD)), Vector3(clockMaxSize + mouseSize, size, 0));
			anim->addKey("mouse", 15, Quaternion(Vector3(90 * Math::DEG2RAD, 0, -270 * Math::DEG2RAD)), Vector3(3*clockMaxSize, size, 0));


			clock->addComponent(new LookAtBehaviour(camObj->getTransform()));

			anim->loop(false);
			anim->play();

			// and	 other animation techniques
			ClockAnimation* animTask = new ClockAnimation(this);
			animTask->obj = clock->getMinuteHand();
			addTask(animTask);

			// Other 3D techniques
			addTask(new ExamSound(this));

			//em->getTransform()->setLocalRotation(Vector3(0,0,90 * Math::DEG2RAD));
			//em->addComponent(new LookAtBehaviour(camObj->getTransform()));


		}




		return true;
	}
}
