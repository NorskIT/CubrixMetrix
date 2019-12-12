#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Cube.h"
#include "Shader.h"
#include "ChunkManager.h"
#include "FlyCamera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void VertexAttribArray(std::vector<float> vertices, unsigned int vertexBuffer, unsigned int vertexArray);
unsigned int loadTexture(const char *path);
void RenderWorld();
void renderChunks(unsigned int diff, unsigned int VertexArray);

// settings
#define SCR_WIDTH 1280
#define SCR_HEIGHT 720

/*
 * We need 2 vertex arrays/objects to store our generated vertices
 *  1. World 1
 *  2. Water (possible more)
 */
unsigned int VBO[2]; //11 chunks to render
unsigned int cubeVAO[2], lightVAO;

//DEBUG
bool mouseIsDisabled = true;

// Create camera, set it to the center of first chunk
//Camera camera(glm::vec3((CHUNK_WIDTH/2), CHUNK_HEIGHT, (CHUNK_WIDTH/2)));

FlyCamera flyCamera(glm::vec3((CHUNK_WIDTH/2), CHUNK_HEIGHT, (CHUNK_WIDTH/2)));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float zoomVariable = 1;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Stores all vertices for our world
ChunkManager chunkManager;

bool showWater = true;

int main()
{
    //Initialize glfw
    glfwInit();
    //Create window.
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "X Y Z", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "ERROR: Coult not create GLFW window" << std::endl;
        std::cout << "Terminates program..." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    /*
     * Listeners
     */
    //if window frame changes
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //If cursor position changes
    glfwSetCursorPosCallback(window, mouse_callback);
    //If mouse scroll changes
    glfwSetScrollCallback(window, scroll_callback);


    //Load Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Enable depth, without everything draws on top of eachother
    glEnable(GL_DEPTH_TEST);

    //Create shader
    Shader shader("../shaders/shader.vert", "../shaders/shader.frag");

    //Generate vertex and buffers.
    glGenVertexArrays(3, cubeVAO);
    glGenBuffers(3, VBO);

    //Create chunkManager, use player pos as start pos.
    chunkManager = ChunkManager(flyCamera.position);
    RenderWorld();

    //Create pointers for textures.
    unsigned int grass = loadTexture("../images/grassWide.jpg");
    unsigned int water = loadTexture("../images/water.png");

    //Use our shader program
    glUseProgram(shader.ID);
    glUniform1i(glGetUniformLocation(shader.ID, "diffuseMaterial"), 0);


    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.4f, 0.4f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Check if player position is outside of current chunk-system.
        chunkManager.checkPlayerPosition(flyCamera.position);

        //Build title string, showing player position
        std::string title = "X: " + std::to_string(flyCamera.position.x-0.5) +
                " Y: " + std::to_string(flyCamera.position.y-0.5) +
                " Z: " + std::to_string(flyCamera.position.z-0.5);
        //Set string to window title.
        glfwSetWindowTitle(window, title.c_str());

        // Create projection mat
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 400.0f);
        glm::mat4 view = flyCamera.GetView();

        //Enable our shader program
        glUseProgram(shader.ID);
        glUniform3f(glGetUniformLocation(shader.ID, "ViewPos"), flyCamera.position.x, flyCamera.position.y, flyCamera.position.z);
        //Set sets projection as our camera projection
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);
        //Set sets projection as our camera view
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, &view[0][0]);
        //Set model as identity model
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, &glm::mat4(1.0f)[0][0]);

        //Draw all our vertices
        renderChunks(grass, cubeVAO[0]);
        renderChunks(water, cubeVAO[1]);


        //If player has moved, then we need to add and render the new vertices which has been added.
        if(chunkManager.hasPlayerMoved)
        {
            RenderWorld();
            chunkManager.hasPlayerMoved = false;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //Release vertex and buffers
    glDeleteVertexArrays(2, cubeVAO);
    glDeleteBuffers(2, VBO);
    glfwTerminate();
    return 0;
}

/**
 * Activates, binds and draws the vertex array
 * @param texture, texture to draw on the vertices
 * @param VertexArray, reference to which vertex array to use
 */
void renderChunks(unsigned int texture, unsigned int VertexArray)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VertexArray);
    glDrawArrays(GL_TRIANGLES, 0, chunkManager.world.size());
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    /*
     * Camera movement listeners
     */
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        flyCamera.UpdateCamera(FlyCamera::FORWARD);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        flyCamera.UpdateCamera(FlyCamera::BACKWARD);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        flyCamera.UpdateCamera(FlyCamera::LEFT);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        flyCamera.UpdateCamera(FlyCamera::RIGHT);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        flyCamera.UpdateCamera(FlyCamera::ASCEND);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        flyCamera.UpdateCamera(FlyCamera::DESCEND);


}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //Makes the scene scaleable
    glViewport(0, 0, width, height);

}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    if(mouseIsDisabled) return;
    float xoffset = xPos - lastX;
    float yoffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;
    flyCamera.mouseDirectionChange(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    /*
     * Scroll inputs.
     *      alt+forward scroll locks cursor.
     *      alt+backward scroll unlocks cursor
     *
     *      forward scroll increased movement speed
     *      forward scroll decreases resets movement speed
     */
    if(yoffset > 0) {
        if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            mouseIsDisabled = false;
        } else {
            flyCamera.flightSpeed += 0.1;
        }
    } else {
        if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            mouseIsDisabled = true;
        } else {
            flyCamera.flightSpeed = 0.1f;
        }
    }
}

/**
 * Starts process of rendering all vertex attrib arrays
 */
void RenderWorld()
{

    //VBO[0] contains all terrain vertices. VBO[1] contains all water vertices.
    VertexAttribArray(chunkManager.world, VBO[0], cubeVAO[0]);
    if(showWater)
    {
        VertexAttribArray(chunkManager.water, VBO[1], cubeVAO[1]);
    }

}

/**
 * Binds the vertices data to our vertex buffer
 * @param vertices, vertices to add.
 * @param vertexBuffer, which buffer to add vertices to.
 * @param vertexArray, which vertex array to bind to.
 */
void VertexAttribArray(std::vector<float> vertices, unsigned int vertexBuffer, unsigned int vertexArray)
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindVertexArray(vertexArray);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

/**
 * Loads and binds texture into TexImage2D
 * @param path, path to texture
 * @return unsigned int reference to texture
 */
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}