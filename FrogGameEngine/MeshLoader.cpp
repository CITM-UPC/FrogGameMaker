#include "MeshLoader.h"

#include <GL/glew.h>
#include <span>

#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>

#include <filesystem>

#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

using namespace std;

struct aiMeshExt : aiMesh {
    auto verts() const { return span((vec3f*)mVertices, mNumVertices); }
    auto texCoords() const { return span((vec3f*)mTextureCoords[0], mNumVertices); }
    auto faces() const { return span(mFaces, mNumFaces); }
};

struct aiSceneExt : aiScene {
    auto materials() const { return span(mMaterials, mNumMaterials); }
    auto meshes() const { return span((aiMeshExt**)mMeshes, mNumMeshes); }
};


std::string MeshLoader::loadFromFile(const std::string& path)
{
    const auto scene_ptr = aiImportFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_ForceGenNormals);
    const aiSceneExt& scene = *(aiSceneExt*)scene_ptr;

    fs::path pathPath(path.c_str());
    fs::path customPath(""); //to library

    customPath = customPath.parent_path() / pathPath.filename();

    scene_ptr->mName.C_Str();
    
    ofstream oFile(customPath.string(), ios::binary);

    //load textures
   /* vector<Texture2D::Ptr> texture_ptrs;
    for (const auto& material : scene.materials()) {
        aiString aiPath;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &aiPath);
        fs::path texPath = fs::path(path).parent_path() / fs::path(aiPath.C_Str()).filename();
        auto texture_ptr = make_shared<Texture2D>(texPath.string());
        texture_ptrs.push_back(texture_ptr);
    }*/

    //load meshes
    //vector<MeshLoader> mesh_ptrs;
    for (const auto& mesh_ptr : scene.meshes()) {

        const auto& mesh = *mesh_ptr;

        vector<VertexV3T2> vertex_data;
        for (size_t i = 0; i < mesh.verts().size(); ++i) {
            VertexV3T2 v = { {mesh.verts()[i].x, mesh.verts()[i].y, mesh.verts()[i].z}, {mesh.texCoords()[i].x, mesh.texCoords()[i].y} };
            vertex_data.push_back(v);
        }

        vector<unsigned int> index_data;
        for (const auto& face : mesh.faces()) {
            index_data.push_back(face.mIndices[0]);
            index_data.push_back(face.mIndices[1]);
            index_data.push_back(face.mIndices[2]);

        }

        MeshLoader mesh_sptr;

        mesh_sptr.vertex_data = vertex_data;
        mesh_sptr.index_data = index_data;
        //mesh_sptr->path = path;

        for (size_t i = 0; i < mesh.mNumVertices; i++) {
            aiVector3D normal = mesh.mNormals[i];
            vec3f glmNormal(normal.x, normal.y, normal.z);
            mesh_sptr.meshNorms.push_back(glmNormal);
        }

        for (size_t i = 0; i < mesh.mNumVertices; i++) {
            aiVector3D vert = mesh.mVertices[i];
            vec3f glmNormal(vert.x, vert.y, vert.z);
            mesh_sptr.meshVerts.push_back(glmNormal);
        }

        for (size_t i = 0; i < mesh.mNumFaces; i++) {
            aiFace face = mesh.mFaces[i];

            vec3f v0(mesh.mVertices[face.mIndices[0]].x, mesh.mVertices[face.mIndices[0]].y, mesh.mVertices[face.mIndices[0]].z);
            vec3f v1(mesh.mVertices[face.mIndices[1]].x, mesh.mVertices[face.mIndices[1]].y, mesh.mVertices[face.mIndices[1]].z);
            vec3f v2(mesh.mVertices[face.mIndices[2]].x, mesh.mVertices[face.mIndices[2]].y, mesh.mVertices[face.mIndices[2]].z);

            vec3f faceNormal = glm::cross(v1 - v0, v2 - v0);
            faceNormal = glm::normalize(faceNormal);
            mesh_sptr.meshFaceNorms.push_back(faceNormal);

            vec3f faceCenter = (v0 + v1 + v2) / 3.0f;
            mesh_sptr.meshFaceCenters.push_back(faceCenter);
        }

        oFile << mesh_sptr;
        //mesh_ptrs.push_back(mesh_sptr);
    }

    aiReleaseImport(scene_ptr);
    oFile.close();

    return customPath.generic_string();
}

std::ostream& MeshLoader::serialize(std::ostream& os) const
{
    size_t vLength = vertex_data.size();
    os.write((char*)&vLength, sizeof(vLength));
    os.write((char*)vertex_data.data(), vertex_data.size() * sizeof(VertexV3T2));

    vLength = index_data.size();
    os.write((char*)&vLength, sizeof(vLength));
    os.write((char*)index_data.data(), index_data.size() * sizeof(unsigned int));

    return os;
}

std::istream& MeshLoader::deserialize(std::istream& is)
{
    size_t vLength = 0;
    is.read((char*)&vLength, sizeof(vLength));
    vertex_data.resize(vLength);
    is.read((char*)vertex_data.data(), vLength * sizeof(VertexV3T2));

    is.read((char*)&vLength, sizeof(vLength));
    index_data.resize(vLength);
    is.read((char*)index_data.data(), vLength * sizeof(unsigned int));

    return is;
}