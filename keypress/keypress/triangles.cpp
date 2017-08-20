//////////////////////////////////////////////////////////////////////////////
//
//  Triangles.cpp
//
//////////////////////////////////////////////////////////////////////////////

#include "vgl.h"
#include "LoadShaders.h"

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];

const GLuint  NumVertices = 6;

//----------------------------------------------------------------------------
//
// init
//
// 用glut的时候使用的shader 不能使#version 450 core, 试了下400是可以的
void
init( void )
{
    
    glGenVertexArrays( NumVAOs, VAOs );
    glBindVertexArray( VAOs[Triangles] );

    GLfloat  vertices[NumVertices][2] = {
        { -0.90f, -0.90f }, {  0.85f, -0.90f }, { -0.90f,  0.85f },  // Triangle 1
        {  0.90f, -0.85f }, {  0.90f,  0.90f }, { -0.85f,  0.90f }   // Triangle 2
    };


    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
//    glCreateBuffers(NumBuffers, Buffers);
    //    glBufferStorage( GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    ShaderInfo  shaders[] =
    {
        { GL_VERTEX_SHADER, "/Users/shuailongcheng/Documents/MyGitHub/TestOpenGL/bin/media/shaders/triangles/triangles.vert" },
        { GL_FRAGMENT_SHADER, "/Users/shuailongcheng/Documents/MyGitHub/TestOpenGL/bin/media/shaders/triangles/triangles.frag" },
        { GL_NONE, NULL }
    };

    GLuint program = LoadShaders( shaders );
    glUseProgram( program );

    glVertexAttribPointer( vPosition, 2, GL_FLOAT,
                           GL_FALSE, 0, BUFFER_OFFSET(0) );
    glEnableVertexAttribArray( vPosition );
}

//----------------------------------------------------------------------------
//
// display
//

void
display( void )
{
    static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    glClearBufferfv(GL_COLOR, 0, black);

    glBindVertexArray( VAOs[Triangles] );
    
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    glFlush();
}

//----------------------------------------------------------------------------
//
// main
//

// glfw 还是有点问题
//#include <assert.h>
//#include <stdio.h>
//int
//main( int argc, char** argv )
//{
//    glfwInit();
//
//    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangles", NULL, NULL);
//
//    glfwMakeContextCurrent(window);
////    int version = gl3wInit();
//    glewExperimental = GL_TRUE;
//    GLenum ret = glewInit();
//    assert (ret ==GLEW_OK);
//   
//
//    init();
//
//    while (!glfwWindowShouldClose(window))
//    {
//        display();
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glfwDestroyWindow(window);
//
//    glfwTerminate();
//}

#include <GLUT/GLUT.h>
#include <iostream>
int main(int argc, const char * argv[])
{
    glutInit(&argc, (char**)argv);
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA);
    glutInitWindowSize(700, 512);
    glutCreateWindow(argv[0]);
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    
    if (GLEW_VERSION_4_1) {
        std::cout << "Yay~~! OpenGL 4.1 is supported!" << std::endl;
    }
    
    init();
    
    glutDisplayFunc(display);
    
    glutMainLoop();
    
}
