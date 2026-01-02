#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void processInput(GLFWwindow*);
void framebuffer_size_callback(GLFWwindow*, int, int);

int main(){

    //Initiating the GLFW window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create the window {glfwCreateWindow(Width, Height, Window Name, Can ignore, Can ignore)}
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLTesting", NULL, NULL);

    //Check if the window failed to initiate / create
    if(window == NULL){

        std::cout<<"Failed to create GLFW window";
        glfwTerminate();
        return -1;

    }

    //Set the current window as the window context (the size, name, etc)
    glfwMakeContextCurrent(window);

    //Set the callback to resize the window ecerytime we resize it
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    //Check if GLAD is initalized
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        
        std::cout<<"Failed to initlize GLAD";
        return -1;
        
    }

    //Tells OpenGL the size of the rendering window
    //glViewport(location of the lower left cornder, location of the lower left corder, width, height)
    glViewport(0, 0, 800, 600);

    //Continuously run the program (so it doesn't close immediately after opening)
    while(!glfwWindowShouldClose(window)){

        processInput(window);

        //This changes the color of the background from black to something green-ish
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
glfwTerminate();
return 0;
}


void processInput(GLFWwindow* window){

    //Check if escape is entered, if entered, close the window
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){

        glfwSetWindowShouldClose(window, true);

    }

}

//This function makes it so that it will resize when resizing the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height){

    glViewport(0, 0, width, height);

}