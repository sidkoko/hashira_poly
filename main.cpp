#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <gmpxx.h> // GMP C++ interface for integers and rationals
#include "include/nlohmann/json.hpp" // JSON library

// Use nlohmann's json namespace
using json = nlohmann::json;

// The function now uses mpq_class (rational numbers) for all calculations
mpq_class solve_polynomial(const std::vector<mpz_class>& x, std::vector<mpq_class>& y) {
    size_t k = x.size();

    // Step 1: Compute Newton's Divided Differences using rational arithmetic
    for (size_t j = 1; j < k; ++j) {
        for (size_t i = k - 1; i >= j; --i) {
            // The denominator is converted to mpq_class for the division
            mpq_class denominator = mpq_class(x[i] - x[i-j]);
            y[i] = (y[i] - y[i-1]) / denominator;
        }
    }

    // Step 2: Evaluate the polynomial at x=0 using rational arithmetic
    mpq_class result = y[k - 1];
    for (int i = k - 2; i >= 0; --i) {
        // -x[i] is also converted to mpq_class for the multiplication
        result = result * mpq_class(-x[i]) + y[i];
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_json_file>" << std::endl;
        return 1;
    }

    std::ifstream file_stream(argv[1]);
    if (!file_stream.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }
    
    try {
        json data = json::parse(file_stream);
        int k = data["keys"]["k"];

        // x_coords are still integers (mpz_class)
        std::vector<mpz_class> x_coords;
        // y_coords must now be rational (mpq_class) to avoid rounding errors
        std::vector<mpq_class> y_coords;

        // Load data using the corrected numerical loop
        for (int i = 1; i <= k; ++i) {
            std::string key = std::to_string(i);
            if (!data.contains(key)) {
                std::cerr << "Error: JSON file is missing key '" << key << "'" << std::endl;
                return 1;
            }
            
            x_coords.push_back(mpz_class(key));
            
            auto val = data[key];
            // Read the value as a big integer first
            mpz_class y_int(val["value"].get<std::string>(), std::stoi(val["base"].get<std::string>()));
            // Convert the integer to a rational number and add it to the vector
            y_coords.push_back(mpq_class(y_int));
        }

        mpq_class constant_rat = solve_polynomial(x_coords, y_coords);
        
        // The final answer should be an integer, so we extract the numerator.
        // The get_num() method returns the numerator as an mpz_class.
        mpz_class constant_c = constant_rat.get_num();

        std::cout << "The constant c (P(0)) is: " << constant_c << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
