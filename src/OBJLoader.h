#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstring>
//Glew

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//OpenGL Math Libs
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Own Libs


#include "Vertex.h"

static std::vector<Vertex> loadOBJ(const char* file_name)
{
    //Vertex Portions
    std::vector<glm::fvec3> vertex_positions;
    std::vector<glm::fvec2> vertex_texcoords;
    std::vector<glm::fvec3> vertex_normals;

    //Face Vectors
    std::vector<GLint> vertex_position_indicies;
    std::vector<GLint> vertex_texcoord_indicies;
    std::vector<GLint> vertex_normal_indicies;

    // Vertex array

    std::vector<Vertex> vertices;

    std::stringstream ss;
    std::ifstream in_file(file_name);
    std::string line = "";
    std::string prefix = "";

    glm::vec3 temp_vec3;
    glm::vec2 temp_vec2;
    GLint temp_glint = 0;

    // File open error check
    if(!in_file.is_open())
    {
        throw "ERROR::OBJLOADER::could not open file.";
    }

    while (std::getline(in_file, line))
    {
        //Get the prefix
        ss.clear();
        ss.str(line);
        ss >> prefix;

        if(prefix == "#") {}
        else if(prefix == "o") {}
        else if(prefix == "s") {}
        //Vertex POS
        else if(prefix == "v")
        {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            vertex_positions.push_back(temp_vec3);
        }
        else if(prefix == "usemtl")
        {}
        else if(prefix == "vt")
        {
            ss >> temp_vec2.x >> temp_vec2.y;
            vertex_texcoords.push_back(temp_vec2);
        }
        else if(prefix == "vn")
        {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            vertex_normals.push_back(temp_vec3);
        }
        else if(prefix == "f")
        {
            int counter = 0;
            while(ss >> temp_glint)
            {

                // Pushing indices into correct arrays
                if(counter==0)
                    vertex_position_indicies.push_back(temp_glint);
                else if(counter == 1)
                    vertex_texcoord_indicies.push_back(temp_glint);
                else if(counter == 2)
                    vertex_normal_indicies.push_back(temp_glint);
                // Handling Characters

                if(ss.peek() == '/')
                {
                    std::cout << "hapedn" << "\n";
                    ++counter;
                    ss.ignore(1, '/');
                }
                else if(ss.peek() == ' ')
                {
                    ++counter;
                    ss.ignore(1, ' ');
                }
                if (counter > 2)
                    counter = 0;

            }

        }else{

        }
    }

    // Build final vertex array (mesh)
    vertices.resize(vertex_position_indicies.size(), Vertex());

    //Load in all indicies
    for (size_t i = 0; i< vertices.size(); ++i)
    {
        vertices[i].position = vertex_positions[vertex_position_indicies[i]- 1];
        vertices[i].texcoord = vertex_texcoords[vertex_texcoord_indicies[i]- 1];
        vertices[i].normal = vertex_normals[vertex_normal_indicies[i]- 1];
        vertices[i].color = glm::vec3(1.f, 1.f, 1.f);
    }

    //Debug

    std::cout << "Nr of vertices" << vertex_position_indicies.size()<< "\n";
    std::cout << "file:" << vertex_positions.size()<<"\n";


    //loading is a success
    return vertices;
}


