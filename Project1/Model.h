#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

using namespace std;

class Model
{
public:

    vector<Mesh> meshes;
    string directory;

    Model(const string& path)
    {
        loadModel(path);
    }

    void Draw()
    {
        for (unsigned int i = 0; i < meshes.size(); ++i)
        {
            meshes[i].Draw();
        }
    }

private:

    void loadModel(const string& path)
    {
        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(
            path,
            aiProcess_Triangulate |
            aiProcess_FlipUVs |
            aiProcess_GenNormals
        );

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            cerr << "ASSIMP ERROR: "
                << importer.GetErrorString()
                << endl;

            return;
        }

        directory = path.substr(0, path.find_last_of('/'));

        processNode(scene->mRootNode, scene);
    }

    void processNode(aiNode* node, const aiScene* scene)
    {
        // обработка мешей текущего узла
        for (unsigned int i = 0; i < node->mNumMeshes; ++i)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

            meshes.push_back(processMesh(mesh, scene));
        }

        // обработка дочерних узлов
        for (unsigned int i = 0; i < node->mNumChildren; ++i)
        {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh processMesh(aiMesh* mesh, const aiScene* scene)
    {
        vector<Vertex> vertices;
        vector<unsigned int> indices;

        // вершины
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
        {
            Vertex vertex;

            // position
            vertex.Position.x = mesh->mVertices[i].x;
            vertex.Position.y = mesh->mVertices[i].y;
            vertex.Position.z = mesh->mVertices[i].z;

            // normal
            if (mesh->HasNormals())
            {
                vertex.Normal.x = mesh->mNormals[i].x;
                vertex.Normal.y = mesh->mNormals[i].y;
                vertex.Normal.z = mesh->mNormals[i].z;
            }

            vertices.push_back(vertex);
        }

        // индексы
        for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
        {
            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < face.mNumIndices; ++j)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        return Mesh(vertices, indices);
    }
};

#endif