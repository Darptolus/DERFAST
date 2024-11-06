#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

// Matrix size (grid size)
const int gridWidth = 10;
const int gridHeight = 10;

// Example matrix to set colors (values between 0 and 1)
float matrix[gridWidth][gridHeight] = {
    {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f},
    {0.9f, 0.8f, 0.7f, 0.6f, 0.5f, 0.4f, 0.3f, 0.2f, 0.1f, 0.0f},
    // ...fill in the rest of the matrix...
};

void drawGrid() {
    // Set the size of each cell in the grid
    float cellWidth = 2.0f / gridWidth;   // Normalized coordinates [-1, 1]
    float cellHeight = 2.0f / gridHeight;

    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            // Set color based on matrix value (for simplicity, we map it to a grayscale)
            float color = matrix[i][j];
            glColor3f(color, color, color);  // Grayscale color

            // Compute the corner positions of the cell
            float x0 = -1.0f + i * cellWidth;
            float y0 = -1.0f + j * cellHeight;
            float x1 = x0 + cellWidth;
            float y1 = y0 + cellHeight;

            // Draw a quad for each cell
            glBegin(GL_QUADS);
            glVertex2f(x0, y0);
            glVertex2f(x1, y0);
            glVertex2f(x1, y1);
            glVertex2f(x0, y1);
            glEnd();
        }
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Grid", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW (after creating OpenGL context)
    // if (glewInit() != GLEW_OK) {
    //     std::cerr << "Failed to initialize GLEW" << std::endl;
    //     return -1;
    // }

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the grid
        drawGrid();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Compile
// PROG=test_matrix_0; g++ -pthread -o ${PROG} ${PROG}.cpp -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl 