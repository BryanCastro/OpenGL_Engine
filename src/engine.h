#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

const unsigned int NUM_CUBES=10;
const unsigned int NUM_POINT_LIGHTS=4;

class Cube;
class Camera;
class PointLight;
class DirectionalLight;
class SpotLight;

class Engine{
    public:
    // Public method to get the instance of the class
    static Engine& GetInstance();
    bool Init(int width, int height, const char* title);
    void Run();
    void Update();
    void Render();
    void Shutdown();
    float GetDeltaTime();

    // Public method to get the window
    GLFWwindow* GetWindow() const;
    
    private:
    
    // settings
    unsigned int m_scr_width = 800;
    unsigned int m_scr_height = 600;

    private:
    // Private constructor to prevent instantiation
    Engine();
    ~Engine();

    // Delete copy constructor and assignment operator
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    // Static instance of the class
    static Engine instance;

    // Pointer to the GLFW window
    GLFWwindow* window;
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow *window);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    Cube* m_cubes[NUM_CUBES];

    glm::vec3 m_cubePositions[NUM_CUBES] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    bool m_bWireFramePressed = false;
    bool m_bWireframe = false;

    float m_deltaTime = 0.0f;
    float m_lastFrame = 0.0f;
    Camera* m_camera;
    PointLight* m_pointLights[NUM_POINT_LIGHTS];
    DirectionalLight* m_directionalLight;  
    SpotLight* m_spotlight;

    glm::vec3 pointLightPositions[NUM_POINT_LIGHTS] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

};