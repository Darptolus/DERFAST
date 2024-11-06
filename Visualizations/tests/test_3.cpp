#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Draw a point using OpenGL

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main( void )
{
  GLFWwindow* window;

  // Initialize the library 
  if (!glfwInit())
    return -1;

  // Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  glViewport( 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
  glMatrixMode( GL_PROJECTION ); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
  glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
  glOrtho( 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1 ); // essentially set coordinate system
  glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
  glLoadIdentity( ); // same as above comment

  GLfloat lineVertices[] =
    {
        200, 100, 0,
        100, 300, 0
    };

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window))
  {
    glClear( GL_COLOR_BUFFER_BIT );

    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_LINE_STIPPLE );
    glPushAttrib( GL_LINE_BIT );
    glLineWidth( 10 );
    glLineStipple( 5, 0x0C0F );
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, lineVertices );
    glDrawArrays( GL_LINES, 0, 2 );
    glDisableClientState( GL_VERTEX_ARRAY );
    glPopAttrib( );
    glDisable( GL_LINE_STIPPLE );
    glDisable( GL_LINE_SMOOTH );
    
    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

// Compile
// PROG=test_3; g++ -pthread -o ${PROG} ${PROG}.cpp -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl 