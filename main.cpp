#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include <iomanip>



long long baseToDecimal(const std::string& value, int base) {
    long long result = 0;
    long long power = 1;

    for (int i = value.length() - 1; i >= 0; i--) {
        int digit_val;
        if (value[i] >= '0' && value[i] <= '9') {
            digit_val = value[i] - '0';
        } else if (value[i] >= 'a' && value[i] <= 'f') {
            digit_val = value[i] - 'a' + 10;
        } else if (value[i] >= 'A' && value[i] <= 'F') {
            digit_val = value[i] - 'A' + 10;
        } else {
            throw std::invalid_argument("Invalid character in number string");
        }

        if (digit_val >= base) {
            throw std::invalid_argument("Digit value out of range for the given base");
        }
        
        if (i < value.length() - 1) {
            power *= base;
        }
        result += digit_val * power;
    }
    return result;
}


std::vector<double> solveLinearSystem(std::vector<std::vector<double>>& A, std::vector<double>& b) {
    int n = A.size();

    for (int i = 0; i < n; i++) {
        // Find pivot
        int max_row = i;
        for (int k = i + 1; k < n; k++) {
            if (std::abs(A[k][i]) > std::abs(A[max_row][i])) {
                max_row = k;
            }
        }
        std::swap(A[i], A[max_row]);
        std::swap(b[i], b[max_row]);

       
        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i] / A[i][i];
            b[k] -= factor * b[i];
            for (int j = i; j < n; j++) {
                A[k][j] -= factor * A[i][j];
            }
        }
    }

 
    std::vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];
    }

    return x;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <json_file>" << std::endl;
        return 1;
    }

    std::ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    json data;
    try {
        input_file >> data;
    } catch (json::parse_error& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return 1;
    }

    int n = data["keys"]["n"];
    int k = data["keys"]["k"];
    int degree = k - 1;

    std::cout << "--- Solving for: " << argv[1] << " ---" << std::endl;
    std::cout << "Total roots provided (n): " << n << std::endl;
    std::cout << "Required roots (k): " << k << std::endl;
    std::cout << "Polynomial degree (m = k - 1): " << degree << std::endl;
    std::cout << std::endl;

   
    if (n > degree) {
        std::cout << "Insight: The number of provided roots (" << n << ") is greater than the degree of the polynomial (" << degree << ")." << std::endl;
        std::cout << "A non-zero polynomial can have at most 'm' roots, where 'm' is its degree." << std::endl;
        std::cout << "Therefore, the only possible solution is the zero polynomial." << std::endl;
        std::cout << "\nCalculated Coefficients:" << std::endl;
        for (int i = 0; i <= degree; ++i) {
            std::cout << "c" << (degree - i) << ": 0" << std::endl;
        }
        return 0;
    }

    
    std::cout << "Insight: The number of roots is not greater than the degree. Proceeding with calculation." << std::endl;
    
    std::vector<long long> roots;
    
    for (int i = 1; i <= degree; ++i) {
        std::string key = std::to_string(i);
        if (data.contains(key)) {
            int base = std::stoi(data[key]["base"].get<std::string>());
            std::string value = data[key]["value"];
            roots.push_back(baseToDecimal(value, base));
        }
    }
    
    std::cout << "\nUsing the first " << degree << " roots for calculation:" << std::endl;
    for(size_t i = 0; i < roots.size(); ++i) {
        std::cout << "Root " << i+1 << " (decimal): " << roots[i] << std::endl;
    }


   
    std::vector<std::vector<double>> A(degree, std::vector<double>(degree));
    std::vector<double> b(degree);

    for (int i = 0; i < degree; ++i) {
        long long current_root = roots[i];
        b[i] = -std::pow(static_cast<double>(current_root), degree);
        for (int j = 0; j < degree; ++j) {
            A[i][j] = std::pow(static_cast<double>(current_root), degree - 1 - j);
        }
    }

   
    std::vector<double> coefficients_solved = solveLinearSystem(A, b);

    
    std::cout << "\nCalculated Coefficients (assuming leading coefficient is 1):" << std::endl;
    std::cout << "c" << degree << ": 1" << std::endl;
    for (int i = 0; i < degree; ++i) {
        
        long long rounded_coeff = static_cast<long long>(std::round(coefficients_solved[i]));
        std::cout << "c" << (degree - 1 - i) << ": " << rounded_coeff << std::endl;
    }

    return 0;
}