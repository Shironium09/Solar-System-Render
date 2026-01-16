#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <random>
#include "inclusions.h"
#include "stb_image.h"

typedef struct Starfield{

    u_int VAO;
    u_int VBO;

    int total_vertex_count = 0;

    void initStars(u_int shaderProgram){

        std::vector<float>batch_vertices;

        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_real_distribution<float> position_dist(-1.0f, 1.0f);
        std::uniform_real_distribution<float> radius_dist(0.002f, 0.005f);

        for(int i = 0; i < NUM_STARS; i++){

            float cx = position_dist(gen);
            float cy = position_dist(gen);
            float z = 0.0f;
            float radius = radius_dist(gen);
            int segments = 8;

            for(int j = 0; j < segments; j++){

                float angle1 = 2.0f*M_PI*j/segments;
                float angle2 = 2.0f*M_PI*(j+1)/segments;

                batch_vertices.push_back(cx);
                batch_vertices.push_back(cy);
                batch_vertices.push_back(z);

                batch_vertices.push_back(cx + cos(angle1) * radius);
                batch_vertices.push_back(cy + sin(angle1) * radius);
                batch_vertices.push_back(z);

                batch_vertices.push_back(cx + cos(angle2) * radius);
                batch_vertices.push_back(cy + sin(angle2) * radius);
                batch_vertices.push_back(z);

            }

        }

        total_vertex_count = batch_vertices.size() / 3;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, batch_vertices.size() * sizeof(float), batch_vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);

    }

    void draw(u_int shaderProgram){

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glUniform1i(glGetUniformLocation(shaderProgram, "uUseTexture"), 0);

        glUniform4f(glGetUniformLocation(shaderProgram, "uColor"), 0.5f, 0.5f, 0.5f, 0.35f);

        int posLoc = glGetUniformLocation(shaderProgram, "uPosition");
        
        if(posLoc != -1){

            glUniform3f(posLoc, 0.0f, 0.0f, 0.0f);
        
        }

        glDrawArrays(GL_TRIANGLES, 0, total_vertex_count);
        
        glBindVertexArray(0);
    }

} Starfield;

typedef struct Object{

    u_int VAO;
    u_int VBO;
    u_int texture;
    u_int orbitVAO;
    u_int orbitVBO;

    std::vector<float>orbitVertices;
    std::vector<float>vertices;
    std::vector<float>position = {0.0, 0.7, 0.0};   //x = center, y = slightly above, z = center (since 2d)
    std::vector<float>velocity = {0.0, 0.0};        //velocity for x and y are initially 0
    float cx = 0.0f;                                //Center X
    float cy = 0.0f;                                //Center Y
    float cz = 0.0f;                                //Center Z
    float radius = 0.02;     
    int num_segments = 64;                          //Number of segments / points around the circle
    int vertex_count = num_segments + 2;

    float last_time = glfwGetTime();
    float orbit_angle = 0.0f;
    float orbit_radius = 0.5f;
    float orbit_speed = 2.0f;

    void loadTexture(const char *path){

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        u_char *data = stbi_load(path, &width, &height, &nrChannels, 0);

        if(data){

            GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, format,width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

        }else{

            std::cout<<"Failed to load texture"<<std::endl;

        }
        stbi_image_free(data);

    }

    void generate(){

        vertices.push_back(cx);     
        vertices.push_back(cy);
        vertices.push_back(cz);
        vertices.push_back(0.5f);
        vertices.push_back(0.5f);

        for(int i = 0; i <= num_segments; i++){

            float angle = 2.0f * M_PI * i / num_segments;
            float tempX = cx + cos(angle)*radius;
            vertices.push_back(tempX / ASPECT_RATIO);
            vertices.push_back(cy + sin(angle)*radius);
            vertices.push_back(cz);

            float u = (cos(angle)*0.5f)+0.5f;
            float v = (sin(angle)*0.5f)+0.5f;

            vertices.push_back(u);
            vertices.push_back(v);

        }

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);

    }

    void rotate(){

        float current_time = glfwGetTime();
        float delta_time = current_time - last_time;
        last_time = current_time;

        orbit_angle += orbit_speed * delta_time;

        position[0] = (cos(orbit_angle) * orbit_radius) / ASPECT_RATIO;
        position[1] = sin(orbit_angle) * orbit_radius;

    }

    void draw(){

        glUniform1i(glGetUniformLocation(shader_program, "uUseTexture"), 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(VAO);

        glUniform1i(glGetUniformLocation(shader_program, "ourTexture"), 0);

        glUniform3f(glGetUniformLocation(shader_program, "uPosition"), position[0], position[1], position[2]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertex_count);

        rotate();
        glBindVertexArray(0);

    }

    void initOrbit(){

        if(orbit_radius > 0.0f){

            float line_segments = 128;

            for(int i = 0; i < line_segments; i++){

                float theta = 2.0f*M_PI*float(i)/line_segments;

                float x = orbit_radius*cos(theta);
                float y = orbit_radius*sin(theta);

                orbitVertices.push_back(x/ASPECT_RATIO);
                orbitVertices.push_back(y);
                orbitVertices.push_back(0.0f);
                

            }
 
            glGenVertexArrays(1, &orbitVAO);
            glGenBuffers(1, &orbitVBO);

            glBindVertexArray(orbitVAO);
            glBindBuffer(GL_ARRAY_BUFFER, orbitVAO);
            glBufferData(GL_ARRAY_BUFFER, orbitVertices.size() * sizeof(float), orbitVertices.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

        }

    }

    void drawOrbit(){

        if(orbit_radius > 0.0f){

            glUniform1i(glGetUniformLocation(shader_program, "uUseTexture"), 0);
            glUniform4f(glGetUniformLocation(shader_program, "uColor"), 0.5f, 0.5f, 0.5f, 0.35f);
            glUniform3f(glGetUniformLocation(shader_program, "uPosition"), 0.0f, 0.0f, 0.0f);

            glBindVertexArray(orbitVAO);
            glLineWidth(1.0f);

            glDrawArrays(GL_LINE_LOOP, 0, 128);
            glBindVertexArray(0);

        }

    }

} Planet;

#endif