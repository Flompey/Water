#include "Cube.h"
#include "Rendering/GlMacro.h"
#include "Rendering/Vertex.h"

Cube::Cube(const std::string& programName, const std::string& distortionProgramName, const Vector3& position, const float scale)
	:
	mProgram(programName),
	mDistortionProgram(distortionProgramName),
	mPosition(position),
	mScale(scale)

{
	InitializeVbo();
	InitializeVao();
	InitializeTexture();
}

Cube::~Cube()
{
	// We do not want to throw an exception inside a destructor. Hence, we do not use the macro "GL"
	glDeleteVertexArrays(1, &mVao);
	glDeleteBuffers(1, &mVbo);
	glDeleteTextures(1, &mTexture);
}

void Cube::Render(const Camera& camera, const Matrix4& projectionMatrix) const
{
	mProgram.Bind();

	GL(glBindVertexArray(mVao));
	GL(glBindTextureUnit(1, mTexture));

	BindUniforms(camera, projectionMatrix);

	glDrawArrays(GL_TRIANGLES, 0, AMOUNT_OF_VERTICES);
}

void Cube::RenderWaterDistortion(const float time, const Camera& camera, const Matrix4& projectionMatrix) const
{
	mDistortionProgram.Bind();

	GL(glBindVertexArray(mVao));
	GL(glBindTextureUnit(1, mTexture));

	BindDistortionUniforms(time, camera, projectionMatrix);

	glDrawArrays(GL_TRIANGLES, 0, AMOUNT_OF_VERTICES);
}

void Cube::InitializeVao()
{
	GL(glCreateVertexArrays(1, &mVao));
	GL(glBindVertexArray(mVao));

	GL(glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position)));
	GL(glVertexAttribFormat(1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, uv)));
	GL(glVertexAttribFormat(2, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normal)));

	GL(glVertexArrayAttribBinding(mVao, 0, 0));
	GL(glVertexArrayAttribBinding(mVao, 1, 0));
	GL(glVertexArrayAttribBinding(mVao, 2, 0));

	GL(glEnableVertexAttribArray(0));
	GL(glEnableVertexAttribArray(1));
	GL(glEnableVertexAttribArray(2));

	GL(glVertexArrayVertexBuffer(mVao, 0, mVbo, NULL, sizeof(Vertex)));
}

void Cube::InitializeVbo()
{
	Vertex vertices[AMOUNT_OF_VERTICES] =
	{
		// Front face
		{{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
		{{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
		{{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},

		{{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
		{{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
		{{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},

		// Back face
		{{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
		{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
		{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},

		{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
		{{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
		{{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},

		// Left face
		{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
		{{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
		{{-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},

		{{-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
		{{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
		{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},

		// Right face
		{{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},

		{{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},

		// Top face
		{{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
		{{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
		{{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},

		{{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
		{{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
		{{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},

		// Bottom face
		{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
		{{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
		{{0.5f, -0.5f, 0.5f}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},

		{{0.5f, -0.5f, 0.5f}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
		{{-0.5f, -0.5f, 0.5f}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
		{ {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}}
	};

	GL(glCreateBuffers(1, &mVbo));
	GL(glNamedBufferData(mVbo, sizeof(Vertex) * AMOUNT_OF_VERTICES, vertices, GL_STATIC_DRAW));
}

void Cube::InitializeTexture()
{
	const int width = 512;
	const int height = 512;
	auto pixels = GetPixels(width, height);

	GL(glCreateTextures(GL_TEXTURE_2D, 1, &mTexture));
	GL(glTextureStorage2D(mTexture, 1, GL_RGBA8, width, height));
	GL(glTextureSubImage2D(mTexture, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.get()));
}

std::unique_ptr<unsigned char[]> Cube::GetPixels(int width, int height) const
{
	// The size of a pixel, in bytes
	const int pixelSize = 4;
	auto pixels = std::make_unique<unsigned char[]>(width * height * pixelSize);

	// We will generate a black and white checkered pattern
	const int squareLength = 64;
	unsigned char black[pixelSize] = { 0, 0, 0, 255 };
	unsigned char white[pixelSize] = { 255, 255, 255, 255 };

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			// Alternates between squareLength and 0 for every "squareLength"
			// we go in the y-direction
			int offset = y % (squareLength * 2) < squareLength ? squareLength : 0;

			// Alternates between true and false for every "squareLength" we go in
			// the x-direction. We apply the offset, in order to make the first
			// square of each row alternate in colour.
			bool isWhite = (x + offset) % (squareLength * 2) < squareLength ? true : false;
			
			memcpy(&pixels[y * width * pixelSize + x * pixelSize], isWhite ? white : black, pixelSize);
		}
	}

	return pixels;
}

void Cube::BindUniforms(const Camera& camera, const Matrix4& projectionMatrix) const
{
	GL(glUniform3fv(4, 1, mPosition.GetPointerToData()));
	GL(glUniform1f(5, mScale));
	GL(glUniform3fv(0, 1, camera.GetPosition().GetPointerToData()));
	GL(glUniformMatrix4fv(2, 1, GL_FALSE, projectionMatrix.GetPointerToData()));

	Matrix4 rotationMatrix = (Matrix4)matrix::GetRotation(-camera.GetXRotation(), -camera.GetYRotation(), 0.0f);
	GL(glUniformMatrix4fv(1, 1, GL_FALSE, rotationMatrix.GetPointerToData()));
}

void Cube::BindDistortionUniforms(const float time, const Camera& camera, const Matrix4& projectionMatrix) const
{
	GL(glUniform1f(3, time));
	BindUniforms(camera, projectionMatrix);
}
