#include "planets.h"
#include "functions.h"
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
Starfield stars;

int main(){

    GLFWwindow *window = startGLFW();

    sun.generate();
    sun.loadTexture("textures/sun.png");

    mercury.generate();
    mercury.loadTexture("textures/mercury.png");
    mercury.initOrbit();

    venus.generate();
    venus.loadTexture("textures/venus.png");
    venus.initOrbit();

    earth.generate();
    earth.loadTexture("textures/earth.png");
    earth.initOrbit();

    mars.generate();
    mars.loadTexture("textures/mars.png");
    mars.initOrbit();

    jupiter.generate();
    jupiter.loadTexture("textures/jupiter.png");
    jupiter.initOrbit();

    saturn.generate();
    saturn.loadTexture("textures/saturn.png");
    saturn.initOrbit();

    uranus.generate();
    uranus.loadTexture("textures/uranus.png");
    uranus.initOrbit();

    neptune.generate();
    neptune.loadTexture("textures/neptune.png");
    neptune.initOrbit();

    stars.initStars(shader_program);

    while(!glfwWindowShouldClose(window)){

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        stars.draw(shader_program);

        mercury.drawOrbit();
        venus.drawOrbit();
        earth.drawOrbit();
        mars.drawOrbit();
        jupiter.drawOrbit();
        saturn.drawOrbit();
        uranus.drawOrbit();
        neptune.drawOrbit();

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
