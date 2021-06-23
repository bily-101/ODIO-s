#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

//TODO: Read more into camera so u can fix features


class Camera
{
private:
    glm::vec3 worldUp;
    glm::mat4 ViewMatrix;

    GLfloat movementSpeed;
    GLfloat sensitivity;


    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    GLfloat yaw;
    GLfloat pitch;
    GLfloat row;

    void updateCameraVectors()
    {

    }


public:
    Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
    {

    }

    ~Camera()
    {


    }
    //Accessors

    const glm::mat4 getViewMatrix()
    {
        this->updateCameraVectors();

        this->ViewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);

        return this->ViewMatrix;
    }

    const glm::vec3 getPosition() const
    {
        return this->position;
    }

    //Functions
    void updateKeyBoardInput(const float& dt, const int direction)
    {

    }

    void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY)
    {
        //TODO: Update pitch yaw and roll


    }

    void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY)
    {
        this->updateKeyBoardInput(dt, direction);
        this->updateMouseInput(dt, offsetX, offsetY);
    }

};