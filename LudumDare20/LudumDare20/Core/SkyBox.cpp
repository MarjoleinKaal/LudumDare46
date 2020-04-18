#include "SkyBox.h"

SkyBox::SkyBox(const char* path)
{
	Mesh cube = GenMeshCube(1000.0f, 1000.0f, 1000.0f);
	model = LoadModelFromMesh(cube);

	int cubemap[1] = { MAP_CUBEMAP };
	model.materials[0].shader = LoadShader(vsSkyBox, fsSkyBox);
	SetShaderValue(model.materials[0].shader, GetShaderLocation(model.materials[0].shader, "enviromentMap"), cubemap, UNIFORM_INT);

	int value[1] = { 0 };
	Shader shdrCubemap = LoadShader(vsCubeMap, fsCubeMap);
	SetShaderValue(shdrCubemap, GetShaderLocation(shdrCubemap, "equirectangularMap"), value, UNIFORM_INT);

	Texture2D texHDR = LoadTexture(path);
	model.materials[0].maps[MAP_CUBEMAP].texture = GenTextureCubemap(shdrCubemap, texHDR, 512);

	UnloadTexture(texHDR);     
	UnloadShader(shdrCubemap);
}

SkyBox::~SkyBox()
{
}

void SkyBox::DrawSkyBox()
{
	Vector3 position = { 0, 0, 0 };
	DrawModel(model, position, 1.0f, WHITE);
}

void SkyBox::UnloadSkyBox()
{
	UnloadShader(model.materials[0].shader);
	UnloadTexture(model.materials[0].maps[MAP_CUBEMAP].texture);
	UnloadModel(model);
}