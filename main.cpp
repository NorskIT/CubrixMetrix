#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Cube.h"
#include "ChunkManager.h"

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

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

unsigned int VBO[9]; //9 chunks to render
unsigned int cubeVAO[9], lightVAO;

std::vector<float> vertices1;
std::vector<float> vertices2;

// Stores all vertices for our world
ChunkManager chunkManager = ChunkManager();

//DEBUG
int i = 0;
double lastTime = glfwGetTime();
bool CanMoveMouse = true;

// camera
Camera camera(glm::vec3((CHUNK_WIDTH), CHUNK_HEIGHT, (CHUNK_WIDTH)));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float zoomVariable = 1;

bool startup = true;

int SwitchChunk = 0;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //Listeners
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);


    //Load Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    glEnable(GL_DEPTH_TEST);

    Shader lightingShader("../shaders/model.vert", "../shaders/model.frag");
    //Shader lampShader("../shaders/default.vert", "./shaders/default.frag");

    //Crating ChunkManager





    glGenVertexArrays(9, cubeVAO);
    glGenBuffers(9, VBO);

    chunkManager.generateChunk(camera.Position);
    chunkManager.generateChunk(camera.Position);
    RenderWorld();

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    unsigned int diffuseMap = loadTexture("../grassWide.jpg");
    unsigned int containerMap = loadTexture("../container.jpg");
    unsigned int specularMap = loadTexture("../grassWide.jpg");

    // shader configuration
    // --------------------
    lightingShader.use();
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);
        // render
        // ------
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        chunkManager.CheckWherePlayerPosition(camera.Position);

        std::string title = "X: " + std::to_string(camera.Position.x-0.5);
        title += " Y: " + std::to_string(camera.Position.y-0.5);
        title += " Z: " + std::to_string(camera.Position.z-0.5);
        glfwSetWindowTitle(window, title.c_str());

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);
        lightingShader.setVec3("viewPos", camera.Position);
        // light properties
        lightingShader.setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        // material properties
        lightingShader.setFloat("material.shininess", 32.0f);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom*zoomVariable), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 400.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);


        // calculate the model matrix for each object and pass it to shader before drawing
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1));
        float angle = 0.0f;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        lightingShader.setMat4("model", model);

        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);

        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);

        glBindVertexArray(cubeVAO[0]);



        glDrawArrays(GL_TRIANGLES, 0, chunkManager.world1.size());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, containerMap);
        glBindVertexArray(cubeVAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, chunkManager.world2.size());



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(9, cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(9, VBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        chunkManager.generateChunk(camera.Position);
        RenderWorld();
    }


}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(CanMoveMouse) return;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //camera.ProcessMouseScroll(yoffset);


    if(yoffset > 0) {
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            zoomVariable += 0.2;
        }
        else if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            CanMoveMouse = false;
        } else {
            camera.MovementSpeed += 20;
        }
    } else {
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            zoomVariable -= 0.2;
        }
        else if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            CanMoveMouse = true;
        } else {
            camera.MovementSpeed = 2;
        }
    }
}

void RenderWorld()
{
    vertices1 = chunkManager.world1;
    vertices2 = chunkManager.world2;


    VertexAttribArray(chunkManager.world1, VBO[0], cubeVAO[0]);
    VertexAttribArray(chunkManager.world2, VBO[1], cubeVAO[1]);
}


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