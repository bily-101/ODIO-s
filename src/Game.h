//
// Created by bily101 on 6/22/21.
//
#pragma once

#include "libs.h"
#include "Camera.h"


//Enumerations

enum shader_enums{SHADER_CORE_PROGRAM = 0 };
enum texture_enums{TEX_MAX0 = 0, TEX_MAX0_SPECULAR, TEX_WALL, TEX_WALL_SPECULAR };
enum material_enums{ MAT_1 = 0 };
enum mesh_enums { MESH_QUAD = 0 };

class Game {
private:

    //Variables
    GLFWwindow* window;
    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;
    int framebufferWidth;
    int framebufferHeight;

    //OpenGL context
    const int GL_VERSION_MAJOR;
    const int GL_VERSION_MINOR;

    //Delta Time

    float dt;
    float curlTime;
    float lastTime;

    //Mouse Input
    double lastMouseX;
    double lastMouseY;
    double mouseX;
    double mouseY;
    double mouseOffsetX;
    double mouseOffsetY;
    bool firstMouse;

    // Matrices
    glm::mat4 ViewMatrix;
    glm::vec3 camPosition;
    glm::vec3 worldUp;
    glm::vec3 camFront;
    glm::mat4 ProjectionMatrix;
    float fov;
    float nearPlane;
    float farPlane;

    //Shaders
    std::vector<Shader*> shaders;

    //Texutes
    std::vector<Texture*> textures;

    //Materials
    std::vector<Material*> materials;

    //Mesh's
    std::vector<Mesh*> meshes;

    //Lights

    std::vector <glm::vec3*> lights;


    //Private Functions
    void initGLFW();
    void initWindow(const char* title, bool resizable);
    void initGLEW();
    void initOpenGLOptions();
    void initMatrices();
    void initShaders();
    void initTextures();
    void initMaterials();
    void initMeshes();
    void initLights();
    void initUniforms();

    void updateUniforms();

    //Static Vars

public:
    //Constuctors/ Destroctors
    Game(const char *title,
         const int WINDOW_WIDTH,
         const int height,
         const int GL_VERSION_MAJOR,
         const int GL_VERSION_MINOR,
         bool resizable
         );
    virtual ~Game();

    //Accessors
    int getWindowShouldClose();

    //Modifiers

    void setWindowShouldClose();

    //Functions/
    void updateMouseInput();
    void updateKeyboardInput();
    void updateInput();

    void updateDt();
    void update();
    void render();


    //Static Functions
    static void framebuffer_resize_callback(GLFWwindow *window, int fbW, int fbH);
//    static void updateInput(GLFWwindow *window, Mesh &mesh);
//    static void updateInput(GLFWwindow *window);
};


