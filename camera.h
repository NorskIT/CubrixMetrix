#ifndef MIKECRAFT_CAMERA_H
#define MIKECRAFT_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

/*
 * Class fetches from LearnOpenGl, modified for my own needs.
 */


//Which direction to move the camera model
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    ASCEND,
    DESCEND
};

class Camera
{
public:

    glm::vec3 Position;
    glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up;
    glm::vec3 Right;

    float Yaw;
    float Pitch;

    // Camera options
    float MovementSpeed = 1.0f;
    float MouseSensitivity = 0.1f;
    float Zoom = 45.0f;

    // Constructor with vectors
    Camera(glm::vec3 position)
    {
        Position = position;
        updateCameraVectors();
    }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // Which direction to move multiplied by time since last updated frame
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
    }

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
    }

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
    }

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        Right   = glm::normalize(glm::cross(Front, WorldUp));
        Up      = glm::normalize(glm::cross(Right, Front));
    }
};
#endif //MIKECRAFT_CAMERA_H
