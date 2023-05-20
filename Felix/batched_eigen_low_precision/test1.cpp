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

    int batch_size = rows / 8;

    #pragma omp parallel for
    for (int i = 0; i < rows; i += batch_size) {
        int end_row = std::min(i + batch_size, rows);

        Eigen::MatrixXf batch = random_matrix.block(i, 0, end_row - i, columns);
        Eigen::VectorXf norms = batch.rowwise().squaredNorm();

        row_squared_norms.segment(i, end_row - i) = norms;
    }


    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    // Print the duration
    std::cout << "Execution time (s): " << duration << " seconds" << std::endl;
    std::cout << row_squared_norms.head(10) << std::endl;


    


    return 0;
}
