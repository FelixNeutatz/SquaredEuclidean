#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <chrono>
#include <random>

int main() {
    int rows = 10000000;
    int columns = 100;

    // Generate a random matrix
    std::mt19937_64 rng;
    rng.seed(42);
    Eigen::MatrixXf random_matrix = Eigen::MatrixXf::Random(rows, columns);

    auto start = std::chrono::high_resolution_clock::now();

    Eigen::VectorXf row_squared_norms(rows);
    row_squared_norms = random_matrix.rowwise().squaredNorm();


    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Print the duration
    std::cout << "Execution time (s): " << duration << " milliseconds" << std::endl;
    std::cout << row_squared_norms.head(10) << std::endl;
    
    double sum = row_squared_norms.sum();

    // Output the sum
    std::cout << "Sum of all values: " << sum << std::endl;


    


    return 0;
}
