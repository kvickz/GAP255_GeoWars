//AssetManager.h

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <unordered_map>
#include <vector>
#include <string>

#include "Color.h"

class Mesh;
class Material;

typedef std::unordered_map<std::string, Mesh*> MeshContainer;
typedef std::unordered_map<std::string, Material*> MaterialContainer;

class AssetManager
{
private:
    unsigned int m_generatedMeshes;

    MeshContainer m_meshes;
    MaterialContainer m_materials;

    std::vector<Material*> m_materialInstances;

public:
    AssetManager();
    ~AssetManager();

    Mesh* LoadMesh(const char* const pFileName);
    Mesh* GetMesh(const char* const pFileName);

    Material* LoadMaterial(const char* const pMaterialName, const char* const pVertFile, const char* const pFragFile, Color color);
    Material* GetMaterial(const char* const pMaterialName);

    Material* CreateMaterialInstance(std::string pMaterialName);
    Mesh* GenerateQuad(std::string meshKey, std::vector<float> vertices, std::vector<unsigned int> indices);
};

#endif // !ASSETMANAGER_H
