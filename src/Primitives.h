#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Vertex.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Primitive
{
private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

public:
    Primitive() {}
    virtual ~Primitive() {}

    void set(const Vertex* vertices,
             const unsigned nrOfVertices,
             const GLuint* indices,
             const unsigned  nrOfIndices)
    {
        for (size_t i = 0; i < nrOfVertices; i++) {
           this->vertices.push_back(vertices[i]);
        }

        for (size_t i = 0; i < nrOfIndices; i++) {
            this->indices.push_back(indices[i]);
        }
    }

    inline Vertex* getVertices() { return this->vertices.data(); }
    inline GLuint* getIndices() { return this->indices.data(); }
    inline const unsigned getNrOfVertices() {return this->vertices.size(); }
    inline const unsigned getNrOfIndices() {return this->indices.size(); }

};

class Quad : public Primitive
{
public:
    Quad()
        : Primitive()
    {
        Vertex vertices[] =
                {       //Position                               //COLOR                             //TexCoords                  Normal/Lighting
                        glm::vec3(-0.5f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 0.f, 1.f),
                        glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 1.f),
                        glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, 1.f),
                        //Triangles
                        glm::vec3(0.5f, 0.5f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, 1.f)
                };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

        GLuint indices[] =
                {
                        0, 1, 2, //Triangle one
                        0, 2, 3 // Triangle two
                };

        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

        this->set(vertices, nrOfVertices, indices, nrOfIndices);

    }
};

class Triangle : public Primitive
{
public:
    Triangle()
            : Primitive()
    {
        Vertex vertices[] =
                {       //Position                               //COLOR                             //TexCoords                  Normal/Lighting
                        glm::vec3(-0.5f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 0.f, 1.f),
                        glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 1.f),
                        glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, 1.f),
                        //Triangles
                        glm::vec3(0.5f, 0.5f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, 1.f)
                };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

        GLuint indices[] =
                {
                        0, 1, 2 //Triangle one
                };

        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

        this->set(vertices, nrOfVertices, indices, nrOfIndices);

    }
};