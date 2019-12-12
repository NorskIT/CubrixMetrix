
#ifndef MIKECRAFT_FLYCAMERA_H
#define MIKECRAFT_FLYCAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class FlyCamera {



public:

    enum Direction {
        FORWARD,
        BACKWARD,
        RIGHT,
        LEFT,
        ASCEND,
        DESCEND
    };

    //Camera position
    glm::vec3 position;
    //Position to face the camera
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    //Original up vector
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    //Camera up vector
    glm::vec3 up;
    //Vector for correct side movement with camera.
    glm::vec3 right;

    float flightSpeed = 1.01f;

    //Rotation value, Y
    float yRot = 0.0f;
    //Rotation value, X
    float xRot = 0.0f;

    /**
     * Constructur for camera
     * @param pos , spawn position of camera
     */
    FlyCamera(glm::vec3 pos)
    {
        position = pos;
        right   = glm::normalize(glm::cross(front, worldUp));
        up      = glm::normalize(glm::cross(right, front));
    }

    /**
     * Return the view mat4
     * @return
     */
    glm::mat4 GetView()
    {
        return glm::lookAt(position, position + front, up);
    }

    /**
     * Updates the camera position in said direction
     * @param dir, direction to move
     */
    void UpdateCamera(Direction dir)
    {

        switch(dir)
        {
            case FORWARD:
                position += front * flightSpeed;
                break;
            case BACKWARD:
                position -= front * flightSpeed;
                break;
            case LEFT:
                position -= right * flightSpeed;
                break;
            case RIGHT:
                position += right * flightSpeed;
                break;
            case ASCEND:
                position += glm::vec3(0,1,0);
                break;
            case DESCEND:
                position += glm::vec3(0,-1,0);;
                break;
        }
    }

    /*
     * https://upload.wikimedia.org/wikipedia/commons/b/b8/Roll_Pitch_Yaw.JPG
     */
    void mouseDirectionChange(float x, float y)
    {

        xRot += x*0.1;
        yRot += y*0.1;

        if (yRot > 89.0f)
            yRot = 89.0f;
        if (yRot < -89.0f)
            yRot = -89.0f;

        glm::vec3 newFront;
        newFront.x = cos(glm::radians(xRot)) * cos(glm::radians(yRot));
        newFront.y = sin(glm::radians(yRot));
        newFront.z = sin(glm::radians(xRot)) * cos(glm::radians(yRot));
        front   = glm::normalize(newFront);
        right   = glm::normalize(glm::cross(front, worldUp));
        up      = glm::normalize(glm::cross(right, front));
    }
};


#endif //MIKECRAFT_FLYCAMERA_H
