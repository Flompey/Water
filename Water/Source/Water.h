#pragma once
#include "Rendering/Program.h"
#include "DynamicVariableManager.h"
#include "Rendering/Camera.h"
#include "Mathematics/Matrix/Matrix.h"
#include "Rendering/Texture.h"

class Water
{
public:
	Water(const std::string& programName, const std::string& variableFilename, 
		const std::string& texture, const std::string& normalMap);
	~Water();
	void Update(float deltaTime);
	void Render(float time, const Camera& camera, const Matrix4& projectionMatrix);
	bool IsPointInside(const Vector3& point) const;
private:
	void BindTextures() const;
	void BindUniforms(float time, const Camera& camera, const Matrix4& projectionMatrix);
private:
	Program mProgram;
	// Dynamic variables that are used inside the shaders. It enables the user to change
	// the result of the rendering at runtime.
	DynamicVariableManager<float> mWaterFactors;
	Texture mTexture;
	Texture mNormalMap;
	// A texture that stores permutation table data, used inside the shaders 
	GLuint mPermutationTexture = 0;
	// The size of the permutation table
	static constexpr int PERMUTATION_SIZE = 256;

	// The width of the water, in amount of patches
	static constexpr unsigned int WIDTH = 50;
	// The height of the water, in amount of patches
	static constexpr unsigned int HEIGHT = 50;
	static constexpr float PATCH_LENGTH = 25.0f;
	static constexpr float WATER_AMPLITUDE = 2.0f;
};