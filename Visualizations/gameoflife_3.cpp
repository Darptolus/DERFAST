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

// struct color
// {
//   float 
// }
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

void get_rank_color(int rank, int size, int& color_r, int& color_g, int& color_b) {
  // Generate color based on rank
    
}

void draw_grid(const std::vector<std::vector<int>>& grid, const std::vector<std::vector<int>>& rank_grid, int width, int height) {
  glClear(GL_COLOR_BUFFER_BIT);

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (grid[i][j] == 1) {
        // Replace for specific coloring based on rank
        int rank = rank_grid[i][j];
        switch (rank) {
          case 0: glColor3f(0.149, 0.3294, 0.4863); break;  // Blue for rank 0
          case 1: glColor3f(0.9373, 0.2784, 0.4353); break;  // Red for rank 1
          case 2: glColor3f(1.0, 0.8196, 0.4); break;  // Yellow for rank 2
          case 3: glColor3f(0.0235, 0.8392, 0.6275); break;  // Green for rank 3
          case 4: glColor3f(0.5725, 0.3686, 0.6588); break;  // Purple for rank 4
          case 5: glColor3f(1.0, 0.6431, 0.3922); break;  // Orange for rank 5
          case 6: glColor3f(0.3843, 0.7647, 0.9804); break;  // Light Blue for rank 6
          case 7: glColor3f(0.302, 0.6863, 0.2902); break;  // Dark Green for rank 7
          case 8: glColor3f(0.8392, 0.1569, 0.1569); break;  // Dark Red for rank 8
          case 9: glColor3f(1.0, 0.9216, 0.2314); break;  // Light Yellow for rank 9
          case 10: glColor3f(0.2157, 0.2157, 0.2157); break;  // Dark Gray for rank 10
          case 11: glColor3f(0.6784, 0.8471, 0.902); break;  // Sky Blue for rank 11
          case 12: glColor3f(0.7294, 0.3333, 0.8275); break;  // Violet for rank 12
          case 13: glColor3f(0.902, 0.4902, 0.1961); break;  // Burnt Orange for rank 13
          case 14: glColor3f(0.2, 0.6, 0.8); break;  // Cyan for rank 14
          case 15: glColor3f(0.0, 0.5, 0.0); break;  // Forest Green for rank 15
          case 16: glColor3f(0.5765, 0.4392, 0.8588); break;  // Medium Purple for rank 16
          case 17: glColor3f(1.0, 0.498, 0.3137); break;  // Coral for rank 17
          case 18: glColor3f(0.9412, 0.902, 0.549); break;  // Light Goldenrod for rank 18
          case 19: glColor3f(0.3686, 0.3098, 0.6353); break;  // Indigo for rank 19
          case 20: glColor3f(0.7529, 0.7529, 0.7529); break;  // Light Gray for rank 20
          case 21: glColor3f(0.9804, 0.502, 0.4471); break;  // Salmon for rank 21
          case 22: glColor3f(0.0, 0.749, 1.0); break;  // Deep Sky Blue for rank 22
          case 23: glColor3f(0.5294, 0.8078, 0.9216); break;  // Light Sky Blue for rank 23
          case 24: glColor3f(0.5451, 0.2706, 0.0745); break;  // Saddle Brown for rank 24
          // case 0: glColor3f(0.149, 0.3294, 0.4863); break;  // Blue for rank 0
          // case 1: glColor3f(0.9373, 0.2784, 0.4353); break;  // Red for rank 1
          // case 2: glColor3f(1.0, 0.8196, 0.4); break;  // Yellow for rank 2
          // case 3: glColor3f(0.0235, 0.8392, 0.6275); break;  // Green for rank 3
          default: glColor3f(1.0, 1.0, 1.0); break;  // White for others
          // case 0: glColor3f(1.0, 0.0, 0.0); break;  // Red for rank 0
          // case 1: glColor3f(0.0, 1.0, 0.0); break;  // Green for rank 1
          // case 2: glColor3f(0.0, 0.0, 1.0); break;  // Blue for rank 2
          // case 3: glColor3f(1.0, 1.0, 0.0); break;  // Yellow for rank 3
          // default: glColor3f(1.0, 1.0, 1.0); break;  // White for others
        }
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

// Function to generate a random initial grid
void generate_random_grid(std::vector<std::vector<int>>& grid, int width, int height) {
  srand(time(0));
  for (int i = 1; i < height - 1; ++i) {
    for (int j = 0; j < width; ++j) {
      grid[i][j] = rand() % 2; // Randomly assign 0 (dead) or 1 (alive)
    }
  }
}

// Function to load the initial grid from a file
// bool load_grid_from_file(const std::string& filename, std::vector<std::vector<int>>& grid, int width, int height) {
//     std::ifstream file(filename);
//     if (!file.is_open()) {
//         std::cerr << "Error: Could not open file " << filename << "\n";
//         return false;
//     }

//     for (int i = 0; i < height; ++i) {
//         for (int j = 0; j < width; ++j) {
//             file >> grid[i][j];
//             if (file.fail()) {
//                 std::cerr << "Error: File format is incorrect\n";
//                 return false;
//             }
//         }
//     }

//     file.close();
//     return true;
// }

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Validate the number of arguments
  if (argc < 4 || argc > 5) {
    if (rank == 0) {
        std::cerr << "Usage: " << argv[0] << " <iterations> <width> <height> [input_file]\n";
    }
    MPI_Finalize();
    return EXIT_FAILURE;
  }

  // Initialize parameters
  int iterations = std::stoi(argv[1]);
  int width = std::stoi(argv[2]);
  int height = std::stoi(argv[3]);

  // Set up stripped stencil and halo regions
  int local_height = height / size + 2;
  std::vector<std::vector<int>> grid(local_height, std::vector<int>(width, 0));
  std::vector<std::vector<int>> rank_grid(local_height, std::vector<int>(width, rank));

  std::vector<int> global_grid(height * width, 0);
  std::vector<int> global_rank_grid(height * width, 0);

  if (argc == 5) {
    std::string input_file = argv[4];
    // if (rank == 0){
      // Load grid from input file
      // if (!load_grid_from_file(input_file, grid, width, height)) {
      //     return EXIT_FAILURE;
      // }
      printf("Unable to load");
    // }
    // Scatter initial grid
    // int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
              //  void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
              //  MPI_Comm comm)
  } else {
    // Generate Random Grid
    generate_random_grid(grid, width, local_height);
  }

  // generate_random_grid(grid, width, local_height);

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
    std::vector<int> flattened_rank_grid(local_height * width);
    for (int i = 1; i < local_height - 1; ++i) {
      std::copy(grid[i].begin(), grid[i].end(), flattened_grid.begin() + (i - 1) * width);
      std::copy(rank_grid[i].begin(), rank_grid[i].end(), flattened_rank_grid.begin() + (i - 1) * width);
    }

    MPI_Gather(flattened_grid.data(), (local_height - 2) * width, MPI_INT, global_grid.data(), (local_height - 2) * width, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Gather(flattened_rank_grid.data(), (local_height - 2) * width, MPI_INT, global_rank_grid.data(), (local_height - 2) * width, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0 && window) {
      std::vector<std::vector<int>> global_grid_2D(height, std::vector<int>(width));
      std::vector<std::vector<int>> global_rank_grid_2D(height, std::vector<int>(width));
      for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
          global_grid_2D[i][j] = global_grid[i * width + j];
          global_rank_grid_2D[i][j] = global_rank_grid[i * width + j];
        }
      }
      draw_grid(global_grid_2D, global_rank_grid_2D, width, height);
      if (glfwWindowShouldClose(window)) break;
    }
    // usleep(1000000);
  }

  if (rank == 0) {
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  MPI_Finalize();
  return 0;
}

// Compile
// PROG=gameoflife_3; g++ -o ${PROG} ${PROG}.cpp 
// PROG=gameoflife_3; mpicxx -fopenmp -pthread -o ${PROG} ${PROG}.cpp -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -fopenmp

// Run
// PROG=gameoflife_3; mpirun -np 4 --map-by core --bind-to core ./${PROG} 10 100 100
// PROG=gameoflife_3; mpirun -np 8 --map-by core --bind-to core ./${PROG} 10000 500 500
// PROG=gameoflife_3; mpirun -np 8 --map-by core --bind-to core ./${PROG} 100 500 500
// PROG=gameoflife_3; mpirun --use-hwthread-cpus ./${PROG} 100 500 500