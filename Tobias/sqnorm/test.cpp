
#include <array>
#include <algorithm>
#include <random>
#include <chrono>
#include <new>
#include <execution>
#include <memory>
#include <iostream>
#include <fstream>

int main()
{
    constexpr std::size_t rows{10000000};
    constexpr std::size_t cols{100};

    using Payload = float;
    using Vector = std::array<Payload, cols>;
    using Matrix = std::array<Vector, rows>;
    using Result = std::array<Payload, rows>;

    std::ofstream myfile{"result.txt", std::ios::out | std::ios::trunc};

    // Allocate memory
    std::cout << "Allocating...\n";
    auto matrix_ptr = std::make_unique<Matrix>();
    auto &matrix = *matrix_ptr;

    auto reuslt_ptr = std::make_unique<Result>();
    auto &result = *reuslt_ptr;

    std::cout << "Generating...\n";
    std::mt19937_64 rng;

    rng.seed(42);

    std::uniform_real_distribution<Payload> dist;

    for (auto &e : matrix)
    {
        std::generate(std::begin(e), std::end(e), [&rng, &dist]()
                      { return dist(rng); }); // rng only produces ints
    }

    std::cout << "Running...\n";
    {
        auto const begin{std::chrono::high_resolution_clock::now()};

        std::transform(
            std::execution::par_unseq, std::cbegin(matrix), std::cend(matrix), std::begin(result),
            [](const auto &v) noexcept -> auto
            {
                return std::accumulate(std::cbegin(v), std::cend(v), Payload{}, [](const auto &acc, const auto &e) noexcept -> auto
                                       { return acc + e * e; }); // actual work: square and accumulate
            });

        auto const end{std::chrono::high_resolution_clock::now()};

        std::cout << "Duration: " << end - begin << "\n";
    }

    std::cout << "Write to file...\n";
    for (auto const &e : result)
    {
        myfile << e << " ";
    }
    myfile.close();

    return 0;
}
