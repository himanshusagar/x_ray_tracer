#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <camera/camera.h>

#include <objects/triangle.h>
#include <setup/renderengine.h>

#include <setup/scene.h>

#include "setup/world.h"
#include "setup/material.h"
#include "setup/object.h"
#include "objects/sphere.h"
#include "utils/utility.hpp"

//Globals
GLFWwindow * mainWindow = nullptr;
GLuint program;
GLuint quadVao,quadVbo;
int screen_width = 800, screen_height = 600;
float quadVertices[] = {-1, -1,
                        1, -1,
                        1, 1,
                        -1, -1,
                        1, 1,
                        -1, 1};
GLuint texImage;
GLint uniform_texImage;

Scene *scene;

int init_resources()
{

    auto vert(fileToCharArr("./Resources/vshader.vert"));
    auto frag(fileToCharArr("./Resources/fshader.frag"));



    //Create program
    program = makeProgram(compileShader(shDf(GL_VERTEX_SHADER,&vert[0],vert.size())),compileShader(shDf(GL_FRAGMENT_SHADER,&frag[0],frag.size())),true);



    scene = new Scene(screen_width , screen_height);



    glGenVertexArrays(1, &quadVao);


    glGenBuffers(1, &quadVbo);
    glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);



    glBindVertexArray(quadVao);
    glBindBuffer(GL_ARRAY_BUFFER,quadVbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2* sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);



    //Initialise texture
    glGenTextures(1, &texImage);
    glBindTexture(GL_TEXTURE_2D, texImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screen_width, screen_height, 0, GL_RGB, GL_UNSIGNED_BYTE, scene->getBitmap());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    uniform_texImage = glGetUniformLocation(program, "texImage");
    if(uniform_texImage == -1)
    {
        fprintf(stderr, "Could not bind uniform: texImage\n");
        return 0;
    }
    return 1;
}



int main()
{
    using namespace std;

    mainWindow = setupGlfw(screen_width,screen_height,"ZWQWE");


    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        cout << "Failed to initialize OpenGL context" << endl;
        exit(-1);
    }



    if (1 != init_resources())
    {
        exit(-1);
    }

    double last = 0;

    glfwSetTime(last);
    double delta = 0.0f;
    glfwSwapInterval(1);

    bool done = false;

    while (!glfwWindowShouldClose(mainWindow))
    {
        double curr = glfwGetTime();
        delta = curr-last;
        last = curr;
        glfwPollEvents();

        if(glfwGetKey(mainWindow,GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(mainWindow, GLFW_TRUE);
        }



        if(done)
            continue;

        if(scene->isRenderLoopRunning())
        {
            done = true;
            cout << "Rendering complete" << endl;
        }

        //Update texture on GPU
        glBindTexture(GL_TEXTURE_2D, texImage);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, screen_width, screen_height, GL_RGB, GL_UNSIGNED_BYTE, scene->getBitmap());



        glClearColor(0.0, 0.0, 0.0, 0.0);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texImage);
        glUniform1i(uniform_texImage, 0);


        glBindVertexArray(quadVao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        glfwSwapBuffers(mainWindow);

    }


    glDeleteVertexArrays(1,&quadVao);
    glDeleteBuffers(1,&quadVbo);

    glDeleteProgram(program);
    glDeleteTextures(1, &texImage);
    return EXIT_SUCCESS;
}
