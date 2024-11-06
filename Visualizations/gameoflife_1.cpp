#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <mpi.h>
#include <omp.h>

void print_grid(const std::vector<std::vector<int>>& grid, int width, int height, int rank) {
    std::cout << "Rank " << rank << " grid:\n";
    for (int i = 1; i < height - 1; ++i) {  // Skip ghost rows
        for (int j = 0; j < width; ++j) {
            std::cout << (grid[i][j] ? "#" : ".") << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int count_alive_neighbors(const std::vector<std::vector<int>>& grid, int x, int y, int width, int height) {
    int alive_neighbors = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;  // Skip the current cell
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
    for (int i = 1; i < height - 1; ++i) {  // Skip ghost rows
        for (int j = 0; j < width; ++j) {
            int alive_neighbors = count_alive_neighbors(grid, i, j, width, height);
            if (grid[i][j] == 1) {
                if (alive_neighbors < 2 || alive_neighbors > 3) {
                    new_grid[i][j] = 0;  // Dies
                }
            } else {
                if (alive_neighbors == 3) {
                    new_grid[i][j] = 1;  // Becomes alive
                }
            }
        }
    }

    grid = new_grid;
}

void generate_random_grid(std::vector<std::vector<int>>& grid, int width, int height) {
    srand(time(0));
    for (int i = 1; i < height - 1; ++i) {  // Avoid ghost rows
        for (int j = 0; j < width; ++j) {
            grid[i][j] = rand() % 2;
        }
    }
}

bool load_grid_from_file(const std::string& filename, std::vector<std::vector<int>>& grid, int width, int height) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return false;
    }

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 0; j < width; ++j) {
            file >> grid[i][j];
            if (file.fail()) {
                std::cerr << "Error: File format is incorrect\n";
                return false;
            }
        }
    }

    file.close();
    return true;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc < 4 || argc > 5) {
        if (rank == 0) {
            std::cerr << "Usage: " << argv[0] << " <iterations> <width> <height> [input_file]\n";
        }
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    int iterations = std::stoi(argv[1]);
    int width = std::stoi(argv[2]);
    int height = std::stoi(argv[3]);

    int local_height = height / size + 2;  // Each process handles a chunk with 2 extra rows (ghost rows)
    std::vector<std::vector<int>> grid(local_height, std::vector<int>(width, 0));

    // Initialize the grid
    if (argc == 5) {
        std::string input_file = argv[4];
        if (rank == 0) {
            // Master process loads the grid and distributes it
            std::vector<std::vector<int>> global_grid(height, std::vector<int>(width, 0));
            if (!load_grid_from_file(input_file, global_grid, width, height)) {
                MPI_Finalize();
                return EXIT_FAILURE;
            }
            // Scatter the grid to all processes
            for (int i = 0; i < size; ++i) {
                int start_row = i * (height / size);
                for (int j = 0; j < local_height - 2; ++j) {
                    if (i == rank) {
                        grid[j + 1] = global_grid[start_row + j];
                    }
                    MPI_Bcast(global_grid[start_row + j].data(), width, MPI_INT, i, MPI_COMM_WORLD);
                }
            }
        } else {
            for (int j = 1; j < local_height - 1; ++j) {
                MPI_Bcast(grid[j].data(), width, MPI_INT, 0, MPI_COMM_WORLD);
            }
        }
    } else {
        generate_random_grid(grid, width, local_height);
    }

    for (int iter = 0; iter < iterations; ++iter) {
        // Exchange ghost rows with neighboring processes
        if (rank > 0) {
            MPI_Send(grid[1].data(), width, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
            MPI_Recv(grid[0].data(), width, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        if (rank < size - 1) {
            MPI_Send(grid[local_height - 2].data(), width, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            MPI_Recv(grid[local_height - 1].data(), width, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        // Perform the simulation step with OpenMP parallelization
        game_of_life_step(grid, width, local_height);

        // Optionally print grid for debugging
        if (rank == 0) {
            print_grid(grid, width, local_height, rank);
        }
    }

    MPI_Finalize();
    return 0;
}

// Compile
// PROG=gameoflife_1; g++ -pthread -o ${PROG} ${PROG}.cpp -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -fopenmp
// PROG=gameoflife_1; mpicxx -fopenmp -o ${PROG} ${PROG}.cpp 