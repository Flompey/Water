#pragma once
#include "Rendering/Program.h"
#include "Rendering/Camera.h"
#include "Mathematics/Matrix/Matrix.h"

class Cube
{
public:
	Cube(const std::string& programName, const std::string& distortionProgramName, const Vector3& position, float scale);
	~Cube();
	void Render(const Camera& camera, const Matrix4& projectionMatrix) const;
	// Distorts the cube's texture and vertices, as if the cube is seen through a surface of water
	void RenderWaterDistortion(float time, const Camera& camera, 
		const Matrix4& projectionMatrix) const;
private:
	void InitializeVao();
	void InitializeVbo();
	void InitializeTexture();
	std::unique_ptr<unsigned char[]> GetPixels(int width, int height) const;
	void BindUniforms(const Camera& camera, const Matrix4& projectionMatrix) const;
	void BindDistortionUniforms(const float time, const Camera& camera, const Matrix4& projectionMatrix) const;
private:
	Program mProgram;
	// The program used when we want to make the cube look like it is seen through a surface of water
	Program mDistortionProgram;
	GLuint mVao = 0;
	GLuint mVbo = 0;
	GLuint mTexture = 0;

	Vector3 mPosition;
	float mScale = 0.0f;

	// A cube has 6 sides, 2 triangles per side and 3 vertices per triangle
	static constexpr int AMOUNT_OF_VERTICES = 6 * 2 * 3;
};