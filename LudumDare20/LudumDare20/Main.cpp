// LudumDare20.cpp : Defines the entry point for the application.
//

#include "Main.h"
#include "raylib.h"
#include "reactphysics3d.h"
#include "Core/HeightMap.h"
#include "Core/SkyBox.h"
#include "Water/WaterGrid.h"

#include <vector>
#include <filesystem>

using namespace std;

rp3d::RigidBody* CreateCube(rp3d::DynamicsWorld& world, rp3d::Vector3 pos, rp3d::CollisionShape* shape, std::vector<rp3d::ProxyShape*> proxyShapes)
{
	
	rp3d::Quaternion initOrientation = rp3d::Quaternion::identity();
	rp3d::Transform transform(pos, initOrientation);

	rp3d::RigidBody* body;
	body = world.createRigidBody(transform);

	body->setType(rp3d::BodyType::STATIC);
	rp3d::Transform transform_ = rp3d::Transform::identity();

	rp3d::ProxyShape* proxyShape;
	proxyShape = body->addCollisionShape(shape, transform_, 0.0f);

	proxyShapes.push_back(proxyShape);

	return body;
}



int main()
{
	std::cout << "Running from: " << std::filesystem::current_path() << "\n\n";

	
	const int screenWidth = 1600;
	const int screenHeight = 900;

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "yeeh its a window");

	Camera camera = { { 0.0f, 5.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };


	rp3d::Vector3 gravity(0.0, -9.81, 0.0);
	rp3d::DynamicsWorld world(gravity);
	world.setNbIterationsPositionSolver(8);
	world.setNbIterationsVelocitySolver(15);

	SkyBox* skybox = new SkyBox("resources/dresden_square.hdr");

	SetCameraMode(camera, CAMERA_FIRST_PERSON);  // Set an orbital camera mode
	SetTargetFPS(60);

	Grid3d<WaterCell> waterGrid{ 8, 8, 8 };

	std::vector<std::pair<rp3d::RigidBody*,rp3d::Vector3>> rigidBodiesStatic;
	std::vector<rp3d::ProxyShape*> proxyShapes;

	//floor
	rp3d::Vector3 extent{ 5, 1, 5 };
	rp3d::BoxShape shape1(extent);
	rigidBodiesStatic.push_back(std::make_pair(CreateCube(world,rp3d::Vector3(0,0,0),&shape1,proxyShapes),extent));
	/////////
	rp3d::BoxShape shape2(extent);
	rigidBodiesStatic.push_back(std::make_pair(CreateCube(world, rp3d::Vector3(10, -.5, 0), &shape2, proxyShapes), extent));
	rp3d::BoxShape shape3(extent);
	rigidBodiesStatic.push_back(std::make_pair(CreateCube(world, rp3d::Vector3(-10, -.5, 0), &shape2, proxyShapes), extent));
	rp3d::BoxShape shape4(extent);
	rigidBodiesStatic.push_back(std::make_pair(CreateCube(world, rp3d::Vector3(0, -.5, 10), &shape2, proxyShapes), extent));
	rp3d::BoxShape shape5(extent);
	rigidBodiesStatic.push_back(std::make_pair(CreateCube(world, rp3d::Vector3(0, -.5, -10), &shape2, proxyShapes), extent));


	// Create a rigid body in the world
	rp3d::Vector3 initPosition(0.0, 10.0, 0.0);
	rp3d::Quaternion initOrientation = rp3d::Quaternion ::
		identity();
	rp3d::Transform transform(initPosition, initOrientation);
	
	rp3d::RigidBody* body;
	body = world.createRigidBody(transform);

	rp3d::decimal radius = rp3d::decimal(1.0);
	rp3d::CapsuleShape shape(1.0f,1.0f);
	
	rp3d::Transform transform_ = rp3d::Transform::identity();
	rp3d::decimal mass = rp3d::decimal(4.0);

	rp3d::ProxyShape* proxyShape;
	proxyShape = body->addCollisionShape(&shape, transform_, mass);
	//

	/*WATERGUN*//*
	rp3d::RigidBody* waterGun;
	waterGun = world.createRigidBody(transform);


	rp3d::SphereShape shape_(.1f);
	waterGun->setType(rp3d::BodyType::KINEMATIC);
	rp3d::Transform transform_1 = rp3d::Transform::identity();

	rp3d::ProxyShape* proxyShape1;
	proxyShape1 = waterGun->addCollisionShape(&shape_, transform_1, mass);
	/////////////////*/

	float accumulator = 0;
	long double previousFrameTime = 0;

	while (!WindowShouldClose())
	{

		const float timeStep = 1.0 / 60.0f;

		long double currentFrameTime = GetFrameTime();
		long double deltaTime = currentFrameTime - previousFrameTime;
		previousFrameTime = currentFrameTime;
		accumulator = currentFrameTime;

		{
			world.update(timeStep);
			accumulator -= timeStep;
		}


		rp3d::Vector3 position{ camera.position.x,body->getTransform().getPosition().y,camera.position.z };
		rp3d::Transform transform(position, body->getTransform().getOrientation());
		body->setTransform(transform);

		UpdateCamera(&camera);
		camera.position = Vector3{ camera.position.x, body->getTransform().getPosition().y ,camera.position.z };

		BeginDrawing();

			ClearBackground(RAYWHITE);

			BeginMode3D(camera);

				DrawGrid(20, 1.0f);


				for (int i = 0; i < rigidBodiesStatic.size(); ++i)
				{
					DrawCube(ConvertVector3(rigidBodiesStatic[i].first->getTransform().getPosition()), rigidBodiesStatic[i].second.x * 2.0f, rigidBodiesStatic[i].second.y * 2.0f, rigidBodiesStatic[i].second.z * 2.0f, BLUE);
				}

				DebugDrawWaterGrid(waterGrid);
				skybox->DrawSkyBox();
			EndMode3D();

			DrawFPS(10, 10);
		EndDrawing();
	}

	skybox->UnloadSkyBox();
	delete skybox;

	CloseWindow();

	return 0;
}


