#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <mpi.h>
#include <omp.h>
#include <GLFW/glfw3.h>
#include <unistd.h>

const int window_width = 800;
const int window_height = 800;

GLFWwindow* initGLFW(int grid_width, int grid_height) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return nullptr;
    }

    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Game of Life - MPI & OpenMP", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glViewport(0, 0, window_width, window_height);
    glOrtho(0, grid_width, grid_height, 0, -1, 1);
    
    return window;
}

void draw_grid(const std::vector<std::vector<int>>& grid, int width, int height) {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (grid[i][j] == 1) {
                glColor3f(1.0, 1.0, 1.0);
            } else {
                glColor3f(0.0, 0.0, 0.0);
            }
            glBegin(GL_QUADS);
            glVertex2f(j, i);
            glVertex2f(j + 1, i);
            glVertex2f(j + 1, i + 1);
            glVertex2f(j, i + 1);
            glEnd();
        }
    }

    glfwSwapBuffers(glfwGetCurrentContext());
    glfwPollEvents();
}

int count_alive_neighbors(const std::vector<std::vector<int>>& grid, int x, int y, int width, int height) {
    int alive_neighbors = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int ni = x + i, nj = y + j;
            if (ni >= 0 && ni < height && nj >= 0 && nj < width) {
                alive_neighbors += grid[ni][nj];
            }
        }
    }
    return alive_neighbors;
}

void game_of_life_step(std::vector<std::vector<int>>& grid, int width, int height) {
    std::vector<std::vector<int>> new_grid = grid;

    #pragma omp parallel for
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 0; j < width; ++j) {
            int alive_neighbors = count_alive_neighbors(grid, i, j, width, height);
            if (grid[i][j] == 1) {
                if (alive_neighbors < 2 || alive_neighbors > 3) {
                    new_grid[i][j] = 0;
                }
            } else {
                if (alive_neighbors == 3) {
                    new_grid[i][j] = 1;
                }
            }
        }
    }

    grid = new_grid;
}

void generate_random_grid(std::vector<std::vector<int>>& grid, int width, int height) {
    srand(time(0));
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 0; j < width; ++j) {
            grid[i][j] = rand() % 2;
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc < 4) {
        if (rank == 0) {
            std::cerr << "Usage: " << argv[0] << " <iterations> <width> <height>\n";
        }
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    int iterations = std::stoi(argv[1]);
    int width = std::stoi(argv[2]);
    int height = std::stoi(argv[3]);

    int local_height = height / size + 2;
    std::vector<std::vector<int>> grid(local_height, std::vector<int>(width, 0));

    std::vector<int> global_grid(height * width, 0);

    generate_random_grid(grid, width, local_height);

    GLFWwindow* window = nullptr;
    if (rank == 0) {
        window = initGLFW(width, height);
        if (!window) {
            MPI_Finalize();
            return EXIT_FAILURE;
        }
    }

    for (int iter = 0; iter < iterations; ++iter) {
        if (rank > 0) {
            MPI_Send(grid[1].data(), width, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
            MPI_Recv(grid[0].data(), width, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        if (rank < size - 1) {
            MPI_Send(grid[local_height - 2].data(), width, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            MPI_Recv(grid[local_height - 1].data(), width, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        game_of_life_step(grid, width, local_height);

        std::vector<int> flattened_grid(local_height * width);
        for (int i = 1; i < local_height - 1; ++i) {
            std::copy(grid[i].begin(), grid[i].end(), flattened_grid.begin() + (i - 1) * width);
        }

        MPI_Gather(flattened_grid.data(), (local_height - 2) * width, MPI_INT, global_grid.data(), (local_height - 2) * width, MPI_INT, 0, MPI_COMM_WORLD);

        if (rank == 0 && window) {
            std::vector<std::vector<int>> global_grid_2D(height, std::vector<int>(width));
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    global_grid_2D[i][j] = global_grid[i * width + j];
                }
            }
            draw_grid(global_grid_2D, width, height);
            if (glfwWindowShouldClose(window)) break;
        }
        // usleep(500000);
    }

    if (rank == 0) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    MPI_Finalize();
    return 0;
}

// Compile
// PROG=gameoflife_2; mpicxx -fopenmp -pthread -o ${PROG} ${PROG}.cpp -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -fopenmp


// Run
// PROG=gameoflife_2; mpirun -np 4 --map-by core --bind-to core ./${PROG} 10 100 100