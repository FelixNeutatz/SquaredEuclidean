#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <chrono>

int main() {
    int rows = 10000000;
    int columns = 100;

    // Generate a random matrix
    Eigen::MatrixXd random_matrix = Eigen::MatrixXd::Random(rows, columns);

    auto start = std::chrono::high_resolution_clock::now();

    Eigen::VectorXd row_squared_norms(rows);

    int batch_size = rows / 8;

    #pragma omp parallel for
    for (int i = 0; i < rows; i += batch_size) {
        int end_row = std::min(i + batch_size, rows);

        Eigen::MatrixXd batch = random_matrix.block(i, 0, end_row - i, columns);
        Eigen::VectorXd norms = batch.rowwise().squaredNorm();

        //row_squared_norms.segment(i, end_row - i) = norms;
    }


    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    // Print the duration
    std::cout << "Execution time (s): " << duration << " seconds" << std::endl;


    


    return 0;
}