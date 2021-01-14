#include "Water.h"
#include "Rendering/GlMacro.h"
#include "Noise/PermutationTable.h"

Water::Water(const std::string& programName, const std::string& variableFilename,
    const std::string& texture, const std::string& normalMap)
    :
    mProgram(programName),
    mWaterFactors(variableFilename),
    mTexture(texture),
    mNormalMap(normalMap)
{
    // One patch consists of 4 vertices
    GL(glPatchParameteri(GL_PATCH_VERTICES, 4));

    auto permutationTable = std::make_shared<BasicPermutationTable<unsigned char, PERMUTATION_SIZE>>();
    // Pass in the permutation table as a one-dimensional texture
    GL(glCreateTextures(GL_TEXTURE_1D, 1, &mPermutationTexture));
    GL(glTextureStorage1D(mPermutationTexture, 1, GL_R8UI, (GLsizei)permutationTable->Size()));
    GL(glTextureSubImage1D(mPermutationTexture, 0, 0, (GLsizei)permutationTable->Size(), GL_RED_INTEGER, 
        GL_UNSIGNED_BYTE, permutationTable->GetPointerToData()));
}

Water::~Water()
{
    // We do not want to throw an exception inside a destructor. Hence, we do not use the macro "GL".
    glDeleteTextures(1, &mPermutationTexture);
}

void Water::Update(float deltaTime)
{
    mWaterFactors.UpdateValueKeyboard(deltaTime);
}

void Water::Render(float time, const Camera& camera, const Matrix4& projectionMatrix)
{
    mProgram.Bind();

    BindTextures();
    BindUniforms(time, camera, projectionMatrix);

    // Disable the culling, so that the water can be seen from underneath
    GL(glDisable(GL_CULL_FACE));
    // Render "PATCH_WIDTH * PATCH_HEIGHT" amount of patches, where each path
    // consists of 4 vertices
    GL(glDrawArraysInstanced(GL_PATCHES, 0, 4, WIDTH * HEIGHT));
    GL(glEnable(GL_CULL_FACE));
}

bool Water::IsPointInside(const Vector3& point) const
{
    // The lower left corner of the water is located at (0, 0, 0)
    return (point.x > 0.0f && point.x < (float)WIDTH * PATCH_LENGTH &&
            point.y < WATER_AMPLITUDE &&
            point.z < 0.0f && point.z > -(float)HEIGHT * PATCH_LENGTH);
}

void Water::BindTextures() const
{
    GL(glBindTextureUnit(0, mPermutationTexture));
    mTexture.Bind(1);
    mNormalMap.Bind(2);
}

void Water::BindUniforms(float time, const Camera& camera, const Matrix4& projectionMatrix)
{
    GL(glUniform3fv(0, 1, camera.GetPosition().GetPointerToData()));

    Matrix4 rotationMatrix = (Matrix4)matrix::GetRotation(-camera.GetXRotation(), -camera.GetYRotation(), 0.0f);
    GL(glUniformMatrix4fv(1, 1, GL_FALSE, rotationMatrix.GetPointerToData()));

    GL(glUniformMatrix4fv(2, 1, GL_FALSE, projectionMatrix.GetPointerToData()));

    GL(glUniform1ui(3, WIDTH));
    GL(glUniform1f(4, PATCH_LENGTH));

    mWaterFactors.UseVariables(
        [](const float* waterFactors, size_t size)
        {
            // Bind the dynamic variable array
            GL(glUniform1fv(5, (int)size, waterFactors));
        });

    GL(glUniform1f(13, time));
}