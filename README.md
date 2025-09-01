# hashira_poly
Polynomial Constant Solver
This project is a C++ implementation to solve for the constant term (c) of a polynomial defined by a set of points. The program is designed to fulfill a coding challenge, parsing input from JSON files and using Newton's Divided Difference method for interpolation.

A key feature of this implementation is its ability to handle arbitrarily large numbers and values specified in various number bases (e.g., binary, hex, etc.) by leveraging the GNU Multiple Precision Arithmetic Library (GMP).

Features
Polynomial Interpolation: Implements Newton's Divided Difference method to find the unique polynomial of degree k−1 that passes through k given points.

Large Number Support: Uses the GMP library (mpz_class and mpq_class) to perform all calculations with arbitrary-precision arithmetic, preventing overflow and precision errors.

JSON Parsing: Reads input points and parameters from .json files using the nlohmann/json library.

Multi-Base Value Conversion: Correctly interprets y-coordinates provided as strings in different number bases (from 2 to 62).

Robust Math: All intermediate calculations are performed using rational numbers (mpq_class) to ensure mathematical correctness, as the divided differences are not guaranteed to be integers.
