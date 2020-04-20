#include "HeightMap.h"
#include "raylib.h"


HeightMap::HeightMap(const char* path, Vector3 position, Vector3 size,rp3d::DynamicsWorld& world)
{
	Image image = LoadImage(path);
	if (image.data == NULL) return;
	texture = LoadTextureFromImage(image);

	Mesh mesh = GenMeshHeightmap(image, size);
	model = LoadModelFromMesh(mesh);

	model.materials[0].maps[MAP_DIFFUSE].texture = texture;
	mapPosition = position;


	const int rows = 40;
	const int columns = 50;

	Color* data = GetImageData(image);
	
	for (int i = 0; i < (rows*columns); ++i)
	{
		heightValues[i] = data[i].r / 255.0f;
	}

	shape = new rp3d::HeightFieldShape(columns, rows, minHeight, maxHeight, heightValues, rp3d::HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE, 1, 1.0f, rp3d::Vector3(size.x,size.y,size.z));

	rp3d::Vector3 initPosition(position.x,position.y,position.z);
	rp3d::Quaternion initOrientation = rp3d::Quaternion::identity();
	rp3d::Transform transform(initPosition, initOrientation);
	// Create a collision body in the world
	body = world.createRigidBody(transform);
	body->setType(rp3d::BodyType::STATIC);
	rp3d::Transform transform_ = rp3d::Transform::identity();
	proxyShape = body->addCollisionShape(shape, transform_,0.0f);


	mapPosition = {  body->getTransform().getPosition().x , ((-(maxHeight - minHeight) * rp3d::decimal(0.5)) - minHeight) +  body->getTransform().getPosition().y -1, body->getTransform().getPosition().z };

	UnloadImage(image);


	
}

HeightMap::~HeightMap()
{
}


Vector3 HeightMap::GetPosition()
{
	return mapPosition;
}

void HeightMap::DrawHeightMap()
{
	DrawModel(model, mapPosition,1.0f, RED);
}

void HeightMap::UnloadHeightMap()
{
	UnloadTexture(texture);
	UnloadModel(model);
}
