#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>  // for rand and srand
#include <ctime>    // for time to seed random generator

// Function to print the current state of the grid
void print_grid(const std::vector<std::vector<int>>& grid, int width, int height) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << (grid[i][j] ? "#" : ".") << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Function to count the number of alive neighbors for a given cell
int count_alive_neighbors(const std::vector<std::vector<int>>& grid, int x, int y, int width, int height) {
    int alive_neighbors = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; // Skip the current cell
            int ni = x + i, nj = y + j;
            if (ni >= 0 && ni < height && nj >= 0 && nj < width) {
                alive_neighbors += grid[ni][nj];
            }
        }
    }
    return alive_neighbors;
}

// Function to simulate one step of the Game of Life
void game_of_life_step(std::vector<std::vector<int>>& grid, int width, int height) {
    std::vector<std::vector<int>> new_grid = grid;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int alive_neighbors = count_alive_neighbors(grid, i, j, width, height);
            if (grid[i][j] == 1) {
                // Cell is alive
                if (alive_neighbors < 2 || alive_neighbors > 3) {
                    new_grid[i][j] = 0;  // Dies
                }
            } else {
                // Cell is dead
                if (alive_neighbors == 3) {
                    new_grid[i][j] = 1;  // Becomes alive
                }
            }
        }
    }

    grid = new_grid;
}

// Function to generate a random initial grid
void generate_random_grid(std::vector<std::vector<int>>& grid, int width, int height) {
    srand(time(0));  // Seed random generator with current time
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            grid[i][j] = rand() % 2;  // Randomly assign 0 (dead) or 1 (alive)
        }
    }
}

// Function to load the initial grid from a file
bool load_grid_from_file(const std::string& filename, std::vector<std::vector<int>>& grid, int width, int height) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return false;
    }

    for (int i = 0; i < height; ++i) {
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
    if (argc < 4 || argc > 5) {
        std::cerr << "Usage: " << argv[0] << " <iterations> <width> <height> [input_file]\n";
        return EXIT_FAILURE;
    }

    int iterations = std::stoi(argv[1]);
    int width = std::stoi(argv[2]);
    int height = std::stoi(argv[3]);
    std::vector<std::vector<int>> grid(height, std::vector<int>(width, 0));

    if (argc == 5) {
        std::string input_file = argv[4];
        if (!load_grid_from_file(input_file, grid, width, height)) {
            return EXIT_FAILURE;
        }
    } else {
        generate_random_grid(grid, width, height);
    }

    std::cout << "Initial state:\n";
    print_grid(grid, width, height);

    // Run the simulation for the specified number of iterations
    for (int iter = 0; iter < iterations; ++iter) {
        game_of_life_step(grid, width, height);
        std::cout << "Iteration " << iter + 1 << ":\n";
        print_grid(grid, width, height);
    }

    return 0;
}

// Compile
// PROG=gameoflife_0; g++ -o ${PROG} ${PROG}.cpp 

// Run
// PROG=gameoflife_0; ./${PROG} 10 100 100