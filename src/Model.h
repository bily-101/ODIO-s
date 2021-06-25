#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "OBJLoader.h"

class Model
{
private:
    Material* material;
    Texture* overrideTextureDiffuse;
    Texture* overrideTextureSpecular;
    std::vector<Mesh*> meshes;
    glm::vec3 position;


    //Private funs

    void updateUniforms()
    {

    }

public:
    Model(glm::vec3 position,
          Material* material,
          Texture* orTexDif,
          Texture* orTexSpec,
          std::vector<Mesh*>& meshes
          )
    {
        this->position = position;
        this->material = material;
        this->overrideTextureDiffuse = orTexDif;
        this->overrideTextureSpecular = orTexSpec;

        for (auto*i: meshes)
        {
            this->meshes.push_back(new Mesh(*i));
        }
        for (auto& i: this->meshes)
        {
            i->move(this->position);
            i->setOrigin(this->position);
        }


    }
    //OBJ file loaded model
    Model(glm::vec3 position,
          Material* material,
          Texture* orTexDif,
          Texture* orTexSpec,
          const char* obj_file
    )
    {
        this->position = position;
        this->material = material;
        this->overrideTextureDiffuse = orTexDif;
        this->overrideTextureSpecular = orTexSpec;

        std::vector<Vertex> mesh = loadOBJ(obj_file);
        this->meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0, glm::vec3(1.f, 0.f, 0.f),
                                  glm::vec3(0.f),
                                  glm::vec3(0.f),
                                  glm::vec3(1.f)));

        for (auto& i: this->meshes)
        {
            i->move(this->position);
            i->setOrigin(this->position);
        }


    }

    ~Model()
    {
        for (auto*& i : this->meshes)
            delete i;
    }

    //Functions
    void rotate(const glm::vec3 rotation)
    {
        for (auto& i: this->meshes)
        {
            i->rotate(rotation);
        }
    }

    void update()
    {

    }

    void render(Shader* shader)
    {

        this->updateUniforms();

        //Program Use

        this->material->sendToShader(*shader);
        shader->use();


        for (auto& i: this->meshes)
        {
            this->overrideTextureDiffuse->bind(0);
            this->overrideTextureSpecular->bind(1);

            i->render(shader);
        }

    }

};
