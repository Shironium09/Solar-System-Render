#include "planets.h"
#include "texture_loader.cpp"

Planet sun = Sun();
Planet mercury = Mercury();
Planet venus = Venus();
Planet earth = Earth();
Planet mars = Mars();
Planet jupiter = Jupiter();
Planet saturn = Saturn();
Planet uranus = Uranus();
Planet neptune = Neptune();

int main(){

    GLFWwindow *window = startGLFW();

    sun.generate();
    sun.loadTexture("src/textures/sun.png");

    mercury.generate();
    mercury.loadTexture("src/textures/mercury.png");

    venus.generate();
    venus.loadTexture("src/textures/venus.png");

    earth.generate();
    earth.loadTexture("src/textures/earth.png");

    mars.generate();
    mars.loadTexture("src/textures/mars.png");

    jupiter.generate();
    jupiter.loadTexture("src/textures/jupiter.png");

    saturn.generate();
    saturn.loadTexture("src/textures/saturn.png");

    uranus.generate();
    uranus.loadTexture("src/textures/uranus.png");

    neptune.generate();
    neptune.loadTexture("src/textures/neptune.png");

    while(!glfwWindowShouldClose(window)){

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        sun.draw();
        mercury.draw();
        venus.draw();
        earth.draw();
        mars.draw();
        jupiter.draw();
        saturn.draw();
        uranus.draw();
        neptune.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

glfwTerminate();
return 0;
}
