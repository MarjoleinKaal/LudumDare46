#include "Raylib.h"

class SkyBox
{
public:
	SkyBox(const char* path);
	~SkyBox();

	void DrawSkyBox();
	void UnloadSkyBox();

private:

	Model model = Model();

	const char* vsSkyBox = "resources/glsl330/skybox.vs";
	const char* fsSkyBox = "resources/glsl330/skybox.fs";
	const char* vsCubeMap = "resources/glsl330/cubemap.vs";
	const char* fsCubeMap = "resources/glsl330/cubemap.fs";
};
