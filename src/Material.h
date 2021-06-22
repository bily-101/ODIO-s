#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL2/SOIL2.h>
#include <glm/gtc/matrix_transform.hpp>


#include "Shader.h"

class Material
{
private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    GLint diffuseTex;
    GLint specularTex;

public:
    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex,GLint specularTex)
    {
        this->ambient = ambient;
        this->specular = specular;
        this->diffuse = diffuse;
        this->diffuseTex = diffuseTex;
        this->specularTex = specularTex;

    }
    ~Material() {}

    void sendToShader(Shader& program)
    {
        program.setVec3f(this->ambient, "material.ambient");
        program.setVec3f(this->diffuse, "material.diffuse");
        program.setVec3f(this->specular, "material.specular");
        program.set1i(this->diffuseTex, "material.diffuseTex");
        program.set1i(this->specularTex, "material.specularTex");

    }


};
