//
// Created by mike on 12.12.2019.
//

#ifndef MIKECRAFT_FLYCAMERA_H
#define MIKECRAFT_FLYCAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

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

    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;


    FlyCamera(glm::vec3 pos)
    {
        position = pos;
        normaliseCamera();
    }

    glm::mat4 GetView()
    {
        return glm::lookAt(position, position + front, up);
    }

    void UpdateCamera(Direction dir)
    {

        switch(dir)
        {
            case FORWARD:
                position.z++;
                break;
            case BACKWARD:
                break;
            case LEFT:
                break;
            case RIGHT:
                break;
            case ASCEND:
                break;
            case DESCEND:
                break;
        }
        normaliseCamera();
    }

    void normaliseCamera()
    {
        right   = glm::normalize(glm::cross(front, worldUp));
        up      = glm::normalize(glm::cross(right, front));
    }


};


#endif //MIKECRAFT_FLYCAMERA_H
