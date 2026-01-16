#ifndef INCLUSIONS_H
#define INCLUSIONS_H

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <random>

#define M_PI 3.14159265358979323846
#define SCREEN_WIDTH 1200.0f
#define SCREEN_HEIGHT 1000.0f
#define NUM_STARS 300

typedef unsigned int u_int;
typedef unsigned char u_char;

inline u_int vertex_shader;
inline u_int fragment_shader;
inline u_int shader_program;

inline const float ASPECT_RATIO = SCREEN_WIDTH / SCREEN_HEIGHT; //Aspect Ratio of the screen

inline const float WEIGHT = -0.85f; //The "Weight" of the object, the lower the number, the "heavier" it is

inline const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"out vec2 TexCoord;\n"
"uniform vec3 uPosition;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos + uPosition, 1.0);\n"
"   TexCoord = aTexCoord;\n"
"}\0";

inline const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D ourTexture;\n"
"uniform int uUseTexture;\n"
"uniform vec4 uColor;\n"
"void main()\n"
"{\n"
"   if(uUseTexture == 1) {\n"
"       FragColor = texture(ourTexture, TexCoord);\n"
"   } else {\n"
"       FragColor = uColor;\n"
"   }\n"
"}\0";

#endif