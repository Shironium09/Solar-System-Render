#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";


struct planet{

    unsigned int VAO = 0;
    unsigned int VBO = 0;
    int vertexCount = 0;

    void generate(float cx, float cy, float r, int num_segments){

        std::vector<float> vertices;
        vertices.push_back(cx);
        vertices.push_back(cy);
        vertices.push_back(0.0f);

        for(int i = 0; i <= num_segments; i++){

            float angle = 2.0f * M_PI * i / num_segments;
            vertices.push_back(cx + cos(angle)*r);
            vertices.push_back(cy + sin(angle)*r);
            vertices.push_back(0.0f);
            
        }
        
        vertexCount = num_segments + 2;

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

    }

    void draw(){

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

    }

};

class Engine{
public:

    struct planet planet;

    Engine(){

        init();

    }

    void run(){

        while (!glfwWindowShouldClose(window)){

            processInput();
            glfwSwapBuffers(window);

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            planet.draw();
            
            glfwPollEvents();

        }

    }

    ~Engine(){

        glfwTerminate();

    }

private:
    GLFWwindow* window = nullptr;

    void init(){

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(800, 600, "OpenGLTesting", nullptr, nullptr);\
        if(!window){
            
            std::cout << "Failed to create GLFW window\n";
            glfwTerminate();
            std::exit(-1);

        }
        
        glfwMakeContextCurrent(window);
        
        // STATIC callback
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            
            std::cout << "Failed to initialize GLAD\n";
            std::exit(-1);
            
        }

        planet.generate(0.0f, 0.0f, 0.5f, 64);
        
        glViewport(0, 0, 800, 600);

        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        
        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

    }

    void processInput(){

        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){

            glfwSetWindowShouldClose(window, true);

        }

    }

    // MUST be static
    static void framebuffer_size_callback(GLFWwindow*, int width, int height){

        glViewport(0, 0, width, height);

    }
    
};

int main(){

    Engine engine;
    engine.run();

return 0;
}