//Mesh.cpp

#include "Mesh.h"

#include "FileLoader.h"

#include "Macros.h"

//Creating a mesh from a file
Mesh::Mesh(const char* const fileName)
    :m_vertexBufferObject(0)
    , m_elementBufferObject(0)
    , m_vertexArrayObject(0)
{
    m_pObjFile = new ObjFile;
    m_pObjFile->Load(fileName);

    //Allocate memory
    m_verts = m_pObjFile->GetVerticesAsFloats();
    m_indices = m_pObjFile->GetFacesAsIndices();

    CreateObject();
}

//Creating a mesh from an array
Mesh::Mesh(std::vector<float> pVertices, std::vector<unsigned int> pIndices)
    :m_vertexBufferObject(0)
    , m_elementBufferObject(0)
    , m_vertexArrayObject(0)
    , m_pObjFile(nullptr)
    , m_verts(pVertices)
    , m_indices(pIndices)
{
    CreateObject();
}

Mesh::~Mesh()
{
    SAFE_DELETE(m_pObjFile);
}

void Mesh::CreateObject()
{
    //VBO
    glGenBuffers(1, &m_vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, m_verts.size() * sizeof(float), &m_verts[0], GL_DYNAMIC_DRAW);
    
    //EBO
    glGenBuffers(1, &m_elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size(), &m_indices[0], GL_DYNAMIC_DRAW);

    //VAO
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);
}