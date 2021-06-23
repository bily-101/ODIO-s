//
// Created by bily101 on 6/22/21.
//

#include "Game.h"



//Private Functions


void Game::initMatrices()
{
    this->ViewMatrix = glm::mat4(1.f);
    this-> ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

    this->ProjectionMatrix =  glm::mat4(1.f);
    this->ProjectionMatrix = glm::perspective(
            glm::radians(this->fov),
            static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
            this->nearPlane,
            this->farPlane
    );
}

void Game::initOpenGLOptions()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // mouse/input
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::initGLFW()
{
    //INIT GLFW
    if(glfwInit() == GLFW_FALSE)
    {
        std::cout << "ERROR::GLFW_INIT_FAILED" << "\n";
        glfwTerminate();
    }
}

void Game::initGLEW()
{
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << "/n";
        glfwTerminate();
    }
}

void Game::initShaders()
{
    this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MAJOR,
                                       "shaders/vertex_core.glsl", "shaders/fragment_core.glsl"));
}

void Game::initTextures()
{
    this->textures.push_back(new Texture("Images/Helo.png",
                                         GL_TEXTURE_2D));

    this->textures.push_back(new Texture("Images/max_specular.png",
                                         GL_TEXTURE_2D));

    //Texture1
    this->textures.push_back(new Texture("Images/maxWall.png",
                                         GL_TEXTURE_2D));

    this->textures.push_back(new Texture("Images/maxWall_specular.png",
                                         GL_TEXTURE_2D));
}

void Game::initMaterials()
{
    this->materials.push_back(new Material(glm::vec3(0.1f),
                                           glm::vec3(1.f),
                                           glm::vec3(2.f),
                                           0,
                                           1));
}

void Game::initMeshes()
{

    this->meshes.push_back(new Mesh(
            &Pyramid(),
             glm::vec3(0.f),
             glm::vec3(0.f),
             glm::vec3(2.0)
    ));


}

void Game::initLights()
{
    this->lights.push_back(new glm::vec3(0.f, 0.f, 2.f));
}

void Game::initUniforms()
{
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix", false);
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix", false);
    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(camPosition, "cameraPos");



}

void Game::updateUniforms()

{
    this->materials[MAT_1]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);

    //Update view matrix (camera)

    this->ViewMatrix = glm::lookAt(
            this->camPosition,
            this->camPosition + this->camFront,
            this->worldUp
    );
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix,"ViewMatrix");
    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(camPosition, "cameraPos");


    glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);


    this->ProjectionMatrix = glm::perspective(
            glm::radians(this->fov),
            static_cast<float>(framebufferWidth) / framebufferHeight,
            this->nearPlane,
            this->farPlane
    );

    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix,"ProjectionMatrix");

}

//General Functions




void Game::initWindow(const char *title, bool resizable) {

    this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);
    //IMPORTANT KEEP WINDOW ABOVE THIS COMMENT
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    if(this->window == nullptr)
    {
        std::cout << "ERROR::GLFW_WINDOW_INIT_FAILED" << "\n";
        glfwTerminate();
    }


    glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

    glfwSetFramebufferSizeCallback(window, Game::framebuffer_resize_callback);
    glfwMakeContextCurrent(this->window);

}


Game::Game(const char *title,
           const int WINDOW_WIDTH,
           const int WINDOW_HEIGHT,
           const int GL_VERSION_MAJOR,
           const int GL_VERSION_MINOR,
           bool resizable
           )
        : WINDOW_WIDTH(WINDOW_WIDTH), WINDOW_HEIGHT(WINDOW_HEIGHT),
          GL_VERSION_MAJOR(GL_VERSION_MAJOR), GL_VERSION_MINOR(GL_VERSION_MINOR
          )
{
    //INIT VARIABLES
    this->window = nullptr;
    this->framebufferHeight = this->WINDOW_HEIGHT;
    this->framebufferWidth = this->WINDOW_WIDTH;

    //Matrices INIT
    this->camPosition = glm::vec3 (0.f, 0.f, 1.f);
    this->worldUp = glm::vec3(0.f, 1.f, 0.f);
    this->camFront = glm::vec3(0.f, 0.f, -1.f);

    this-> fov = 90.f;
    this-> nearPlane = 0.1f;
    this-> farPlane = 1000.f;

    this->dt = 0.f;
    this->curlTime = 0.f;
    this->lastTime = 0.f;

    this->lastMouseX = 0.0;
    this->lastMouseY = 0.0;
    this->mouseX = 0.0;
    this->mouseY = 0.0;
    this->mouseOffsetX = 0.0;
    this->mouseOffsetY = 0.0;
    this->firstMouse = true;

    this->initGLFW();
    this->initWindow(title, resizable);
    this->initGLEW();
    this->initOpenGLOptions();

    this->initMatrices();
    this->initShaders();
    this->initTextures();
    this->initMaterials();
    this->initMeshes();
    this->initLights();
    this->initUniforms();
}


Game::~Game() {
    glfwDestroyWindow(this->window);
    glfwTerminate();

    for (size_t i = 0; i < this->shaders.size(); i++)
        delete this->shaders[i];

    for (size_t i = 0; i < this->textures.size(); i++)
        delete this->textures[i];

    for (size_t i = 0; i < this->materials.size(); i++)
        delete this->materials[i];

    for (size_t i = 0; i < this->meshes.size(); i++)
        delete this->meshes[i];

    for (size_t i = 0; i < this->lights.size(); i++)
        delete this->lights[i];
}

//Accessor

int Game::getWindowShouldClose()
{
    return glfwWindowShouldClose(this->window);
}

//Modifiers
void Game::setWindowShouldClose()
{
    glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

// Functions

void Game::updateKeyboardInput()
{

    // PROGRAM
    if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        setWindowShouldClose();
    }

    //CAMERA

    if(glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
    {
        this->camPosition.z -= 0.05f;
    }

    if(glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
    {
        this->camPosition.z += 0.05f;
    }
    if(glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
    {
        this->camPosition.x -= 0.05f;
    }
    if(glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
    {
        this->camPosition.x += 0.05f;
    }
    if(glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        this->camPosition.y += 0.05f;
    }
    if(glfwGetKey(this->window, GLFW_KEY_C) == GLFW_PRESS)
    {
        this->camPosition.y -= 0.05f;
      //  this->camPosition.rotate += 0.05f;
    }


    // Y movement

}

void Game::updateMouseInput()
{

    glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);
    if(this->firstMouse)
    {
        this->lastMouseX = this->mouseX;
        this->lastMouseY = this->mouseY;
        this->firstMouse = false;
    }
    this->mouseOffsetX = this->mouseX - this->lastMouseX;
    this->mouseOffsetY = this->mouseY - this->lastMouseY;

    this->lastMouseX = this->mouseX;
    this->lastMouseY = this->lastMouseY;


}

void Game::updateDt()
{
    this->curlTime = static_cast<float >(glfwGetTime());
    this->dt = this->curlTime - this->lastTime;
    this->lastTime = this->curlTime;

}


void Game::updateInput()
{
    glfwPollEvents();

    this->updateKeyboardInput();
    this->updateMouseInput();
}

void Game::update()
{
    this->updateInput();
    this->updateDt();

//    std::cout << "DT: " << this->dt << "\n";
//    std::cout << "MouseOffset: " << this->mouseX << "\n";

    //Update input
}

void Game::render()
{

    //Clear
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //Update the uniforms
    this->updateUniforms();

    //Program Use

    this->shaders[SHADER_CORE_PROGRAM]->use();

    this->textures[TEX_MAX0]->bind(0);
    this->textures[TEX_MAX0_SPECULAR]->bind(1);

    this->meshes[MESH_QUAD]->render(this->shaders[SHADER_CORE_PROGRAM]);

    //Draw

    glBindVertexArray(0);
    glfwSwapBuffers(this->window);
    glFlush();
    glUseProgram(0);
}

//STATIC FUNCTIONS



void Game::framebuffer_resize_callback(GLFWwindow *window, int fbW, int fbH) {

    glViewport(0, 0, fbW, fbH);

}














/*

void Game::updateInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

}



void Game::updateInput(GLFWwindow *window, Mesh &mesh) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        mesh.move(glm::vec3(0.f, 0.f, 0.01f));
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

        mesh.move(glm::vec3(0.f, 0.f, -0.01f));
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {

        mesh.move(glm::vec3(0.01f, 0.f, 0.f));
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        mesh.move(glm::vec3(-0.01f, 0.f, 0.f));
    }

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        mesh.move(glm::vec3(0.f, 0.01f, 0.f));
    }

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        mesh.move(glm::vec3(0.f, -0.01f, 0.f));
    }

    //Rotation

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        mesh.rotate(glm::vec3(0.f, -1.f, 0.f));
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        mesh.rotate(glm::vec3(0.f, 1.f, 0.f));
    }
}

*/


