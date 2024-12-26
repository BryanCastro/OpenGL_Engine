#include "engine.h"
#include <iostream>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{

  Engine& engine = Engine::GetInstance();
    if (!engine.Init(800, 600, "LearnOpenGL")) {
        return -1;
    }

    engine.Run();
    engine.Shutdown();



    return 0;
}

