//Material.h

#ifndef MATERIAL_H
#define MATERIAL_H

#include <unordered_map>

#include "Enums.h"
#include "Color.h"

class ShaderFile;

typedef unsigned int GLuint;
typedef std::pair<ShaderFile, GLuint> ShaderPair;

class Material
{
private:
    std::unordered_map<ShaderType, ShaderPair> m_shaders;
    Color m_color;

public:
    Material();
    Material(const char* const pVertexFilePath, const char* const pFragmentFilePath, Color color);
    ~Material();

    void LoadShader(const char* const fileName, ShaderType type);
    const GLuint GetShaderGLPointer(const ShaderType type);
    void SetColor(float r, float g, float b);
    void SetColor(Color color);
    Color GetColor() const { return m_color; }
};

#endif // !MATERIAL_H
