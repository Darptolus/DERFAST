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

  // Set the viewport size - Convert to normalized device coordinates (NDC)
  glViewport( 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT );
  // Set the projection matrix
  glMatrixMode( GL_PROJECTION );
  // Replace the current matrix with the identity matrix
  glLoadIdentity();
  // Set the orthographic projection
  glOrtho( 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
  // Set the default modelview matrix
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  GLfloat pointVertex[] = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
  GLfloat pointVertex2[] = {SCREEN_WIDTH*0.75, SCREEN_HEIGHT*0.75};

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window))
  {
    glClear( GL_COLOR_BUFFER_BIT );
    
    // Render here 
    // glEnable( GL_POINT_SMOOTH ); // Enable point smoothing
    // glEnable( GL_BLEND );
    // glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    // glPointSize( 6.0 );

    // glPointSize( 200.0f );
    // glEnableClientState( GL_VERTEX_ARRAY );
    // glVertexPointer( 2, GL_FLOAT, 0, pointVertex );
    // glDrawArrays( GL_POINTS, 0, 1 );
    // glDisableClientState( GL_VERTEX_ARRAY );
    // glDisable( GL_POINT_SMOOTH ); // Disable point smoothing
    
    glEnable( GL_POINT_SMOOTH ); // make the point circular
    glEnableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're using a vertex array for fixed-function attribute
    glPointSize( 50 ); // must be added before glDrawArrays is called
    glVertexPointer( 2, GL_FLOAT, 0, pointVertex ); // point to the vertices to be used
    glDrawArrays( GL_POINTS, 0, 1 ); // draw the vertixes
    glDisableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're finished using the vertex arrayattribute
    glDisable( GL_POINT_SMOOTH ); // stop the smoothing to make the points circular
        

    glEnableClientState( GL_VERTEX_ARRAY );
    glPointSize( 50.0f );
    glVertexPointer( 2, GL_FLOAT, 0, pointVertex2 );
    glDrawArrays( GL_POINTS, 0, 1 );
    glDisableClientState( GL_VERTEX_ARRAY );
    
    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

// Compile
// PROG=test_2; g++ -pthread -o ${PROG} ${PROG}.cpp -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl            