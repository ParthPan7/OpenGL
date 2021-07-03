

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;
using namespace std;
int main(int argc, const char * argv[])
{
    glfwInit();
    
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR , 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR , 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE);
    
   
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Engine",nullptr, nullptr);
     int screenWidth,screenHeight;
     glfwGetFramebufferSize( window, &screenWidth, &screenHeight);
    
    if (window  == nullptr)
    {
        cout << "Failed to create window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent( window );
    glewExperimental = GL_TRUE;
    
    if (GLEW_OK != glewInit())
    {
        cout << "failed to intialize GLFW" << endl;
        return -1;
    }
    glViewport(0, 0, screenWidth, screenHeight);
    
    while (!glfwWindowShouldClose( window ))
    {
        glfwPollEvents();
        glClearColor( 0.2f, 0.2f, 0.3f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT );
        
        glfwSwapBuffers( window );
    }
    
    glfwTerminate();
    return 0;
}
