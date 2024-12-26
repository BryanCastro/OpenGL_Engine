#include "engine.h"
#include <iostream>
#include "logs.h"
#include "shadermanager.h"
#include "texturemanager.h"
#include "cube.h"
#include "camera.h"
#include "pointlight.h"
#include "directionallight.h"
#include "spotlight.h"

Engine Engine::instance;

Engine::Engine() : window(nullptr) {

}

Engine::~Engine() {
    Shutdown();
}

Engine& Engine::GetInstance() {
    return instance;
}

void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    GetInstance().m_scr_width = width;
    GetInstance().m_scr_height = height;
    GetInstance().m_camera->UpdateProjectionMatrix(width, height);
}

void Engine::processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

        
    bool isF1Pressed =  glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS;
    
    if(isF1Pressed && !GetInstance().m_bWireFramePressed){
        GetInstance().m_bWireframe = !GetInstance().m_bWireframe;
        if(GetInstance().m_bWireframe)            
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    GetInstance().m_bWireFramePressed = isF1Pressed;
    GetInstance().m_camera->Input(window, GetInstance().GetDeltaTime());  
}

void Engine::mouse_callback(GLFWwindow* window, double xpos, double ypos){
    GetInstance().m_camera->MouseInput(xpos, ypos);
}

void Engine::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    GetInstance().m_camera->MouseScroll(xoffset, yoffset);
}


bool Engine::Init(int width, int height, const char* title){
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    m_scr_width=width;
    m_scr_height=height;
    window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        Logs::log("Engine.cpp: Failed to create GLFW window", Logs::LogType::Error);
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(window, mouse_callback);  
    glfwSetScrollCallback(window, scroll_callback); 


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logs::log("Engine.cpp: Failed to initialize GLAD", Logs::LogType::Error);
        return -1;
    }

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);  

    m_camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), m_scr_width, m_scr_height);

    TextureManager::CreateTexture("Container", "../../../assets/textures/wall.jpg", Texture::TextureType::DIFFUSE);
    TextureManager::CreateTexture("MarioBlock", "../../../assets/textures/MarioBlock.png", Texture::TextureType::DIFFUSE);
    TextureManager::CreateTexture("Container2", "../../../assets/textures/container2.png", Texture::TextureType::DIFFUSE);
    TextureManager::CreateTexture("Container2Specular", "../../../assets/textures/Container2Specular.png", Texture::TextureType::SPECULAR);
    ShaderManager::CreateShader("CubePointLight", "../../../src/shaders/cube_pointlight.vert", "../../../src/shaders/cube_pointlight.frag");
    ShaderManager::CreateShader("PointLight", "../../../src/shaders/pointlight.vert", "../../../src/shaders/pointlight.frag");
    ShaderManager::CreateShader("CubeDirectionalLight", "../../../src/shaders/cube_directionallight.vert", "../../../src/shaders/cube_directionallight.frag");
    ShaderManager::CreateShader("CubeSpotLight", "../../../src/shaders/cube_spotlight.vert", "../../../src/shaders/cube_spotlight.frag");
    ShaderManager::CreateShader("Cube", "../../../src/shaders/cube.vert", "../../../src/shaders/cube.frag");

    for(int i=0;i<NUM_CUBES;i++){
        m_cubes[i] = new Cube(m_cubePositions[i]);
    }

    for(int i=0;i<NUM_POINT_LIGHTS;i++){
        m_pointLights[i] = new PointLight(pointLightPositions[i], glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);

    }

    m_directionalLight = new DirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);
    m_spotlight = new SpotLight(glm::vec3(1.2f, 1.0f, 2.0f), m_camera->GetForward(), 12.5f, 17.5f, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);

    return true;
}
void Engine::Run(){

    m_deltaTime =0.0f;
    m_lastFrame = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        m_deltaTime = currentFrame - m_lastFrame;
        m_lastFrame = currentFrame;
        processInput(window);
        Update();
        Render();

    }

}

void Engine::Update(){
    m_camera->Update();
    for(int i=0;i<NUM_POINT_LIGHTS;i++){
        m_pointLights[i]->Update();
    }
    //m_directionalLight->Update();
    m_spotlight->Update(m_camera);
    for(int i=0;i<NUM_CUBES;i++){
        m_cubes[i]->Update();
    }
 
}   

void Engine::Render(){

    glClearColor(202.0f/255.0f, 141.0f/255.0f, 22.0f/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_camera->Render();
    for(int i=0;i<NUM_POINT_LIGHTS;i++){
        m_pointLights[i]->Render(m_camera);
    }
    //m_pointLight->Render(m_camera->GetView(), m_camera->GetProjection()); 
    //m_directionalLight->Render();
    m_spotlight->Render(m_camera);
    for(int i=0;i<NUM_CUBES;i++){
        m_cubes[i]->Render(m_camera, m_pointLights, m_directionalLight, m_spotlight);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();

}   

void Engine::Shutdown(){
    Logs::log("Engine.cpp: Shutting down engine", Logs::LogType::Info);
    glfwTerminate();
}

GLFWwindow* Engine::GetWindow() const{
    return window;
}

float  Engine::GetDeltaTime(){
    return m_deltaTime;
}
