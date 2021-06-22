#include "libs.h"


void updateInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

}


void framebuffer_resize_callback(GLFWwindow *window, int fbW, int fbH) {

    glViewport(0, 0, fbW, fbH);

}

void updateInput(GLFWwindow *window, Mesh &mesh) {
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

    //Rotation

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        mesh.rotate(glm::vec3(0.f, -1.f, 0.f));
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        mesh.rotate(glm::vec3(0.f, 1.f, 0.f));
    }
}

int main() {

    glfwInit();

    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    int framebufferWidth = 0;
    int framebufferHeight = 0;
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ODIO", NULL, NULL);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    //glViewport(0,0,framebufferWidth, framebufferHeight);

    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
    glfwMakeContextCurrent(window);


    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Erro::MAIN.CPP::GLEW_INIT_FAILED" << "/n";
        glfwTerminate();
    }

    //SHADERS


    //OpenGL options

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    Shader core_program(4.0, 3.0, "shaders/vertex_core.glsl", "shaders/fragment_core.glsl");

    //MESH
    Quad tempQuad = Quad();
    Triangle tempTriangle = Triangle();
    Mesh max(&tempQuad,
            glm::vec3(0.f),
            glm::vec3(0.f),
            glm::vec3(2.0)
            );
    //TETURES

    //Texture0
    Texture texture0("Images/Helo.png", GL_TEXTURE_2D, 0);
    //Texture1
    Texture texture1("Images/maxWall.png", GL_TEXTURE_2D, 1);

    Material material0(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(2.f), texture0.getTextureUnit(), texture1.getTextureUnit());

    glm::vec3 camPosition(0.f, 0.f, 1.f);
    glm::vec3 worldUp(0.f, 1.f, 0.f);
    glm::vec3 camFront(0.f, 0.f, -1.f);
    glm::mat4 ViewMatrix(1.f);
    ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

    float fov = 90.f;
    float nearPlane = 0.1f;
    float farPlane = 1000.f;
    glm::mat4 ProjectionMatrix(1.f);
    ProjectionMatrix = glm::perspective(
            glm::radians(fov),
            static_cast<float>(framebufferWidth) / framebufferHeight,
            nearPlane,
            farPlane
    );

    //lights

    glm::vec3 lightPos0(0.f, 0.f, 2.f);

    //INIT UNIFORMS

    core_program.setMat4fv(ViewMatrix, "ViewMatrix", false);
    core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix", false);

    core_program.setVec3f(lightPos0, "lightPos0");
    core_program.setVec3f(camPosition, "cameraPos");

    while (!glfwWindowShouldClose(window)) {
        // Update Input
        glfwPollEvents();
        updateInput(window, max);

        //Clear
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        //Program Use


        core_program.set1i(texture0.getTextureUnit(), "texture0");
        core_program.set1i(texture1.getTextureUnit(), "texture1");
        material0.sendToShader(core_program);

        ProjectionMatrix = glm::perspective(
                glm::radians(fov),
                static_cast<float>(framebufferWidth) / framebufferHeight,
                nearPlane,
                farPlane
        );

        core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix", false);

        core_program.use();

        texture0.bind();
        texture1.bind();

        //Draw
        max.render(&core_program);

        glfwSwapBuffers(window);
        glFlush();
        glUseProgram(0);
        glBindVertexArray(0);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
