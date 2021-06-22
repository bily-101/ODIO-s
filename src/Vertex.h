//
// Created by bily101 on 6/21/21.
//

#ifndef LOL_VERTEX_H
#define LOL_VERTEX_H

#include <glm/glm.hpp>
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
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "Vertex.h"


struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texcoord;
    glm::vec3 normal;
};

#endif //LOL_VERTEX_H
