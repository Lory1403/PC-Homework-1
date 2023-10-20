#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <map>
#include <fstream>
#include <string>

using namespace std;

// Calculate the size of the matrices
long int dimension = pow(2, 12);;
vector<vector<float>> M(dimension, vector<float>(dimension));
vector<vector<float>> O(dimension, vector<float>(dimension));
// Variables for block size and for test function performance
long int b;
double elapsed_time;

// Function to matrix initialization with size n
void matrixInitialization() {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            M[i][j] = static_cast<float>(rand()) / RAND_MAX;;
        }
    }
}

// Function to calculate powers of two
void sequentialB(int power) {
    b = pow(2, power);
}

// Function to perform reverse order
void routine1() {
    // Take start time
    clock_t start_time = clock();

    // Swapping blocks
    for (int i = 0; i < dimension / 2; i+=b) {
        for (int j = 0; j < dimension; j+=b) {
            for (int bi = 0; bi < b; bi++) {
                for (int bj = 0; bj < b; bj++) {
                    O[i+bi][j+bj] = M[dimension - i - b + bi][dimension - j - b + bj];
                    O[dimension - i - b + bi][dimension - j - b + bj] = M[i+bi][j+bj];
                }
            }
        }
    }

    // Take end time
    clock_t end_time = clock();
    // Calculate the time elapsed between start and end
    elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000;
}

// Function to print the matrices
void printMatrix() {
    // Print M matrix
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Print O matrix
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            cout << O[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char const *argv[])
{
    // Map for flags and arguments
    map<string, string> flagMap;

    // Start at index 1 to skip the program name (argv[0])
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        
        // Check for recognized flags
        if (arg == "-f" || arg == "--file" || arg == "-p" || arg == "--print") {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                // Check if there is a non-flag argument following the flag
                flagMap[arg] = argv[i+1];
                // Skip next argument
                i++;
            } else {
                // No argument following the flag, set it to an empty string
                flagMap[arg] = "";
            }
        }
    }

    // Process the flags and their arguments
    string filename = "not_required";   // Variable for the name of the output file
    bool printRequired = false;         // Variable for print enabled
    bool outputFileEnabled = false;     // Variable for output file enabled

    for (const auto& entry : flagMap) {
        const std::string& flag = entry.first;  
        const std::string& value = entry.second;

        if (flag == "-f" || flag == "--file")   // Flag for output file
        {
            filename = value;           // Name of the output file
            if (!filename.empty() && 
                filename.size() > 4 && 
                filename.substr(filename.size() - 4) == ".csv") 
            {   // If the output file required and the format is correct 
                outputFileEnabled = true;
            }
        } 
        else if (flag == "-p" || flag == "--print") // Flag for print enable
        {
            printRequired = true;           // Print enabled
        }
    }
    
    ofstream outputFile(filename);          // Create output file
    if (!outputFile.is_open() && !outputFileEnabled) 
    {   // File close but not required or incorrect
        remove(filename.c_str());       // Delete output file
    } else if (outputFile.is_open() && !outputFileEnabled)
    {   // File open but and not required or incorrect
        outputFile.close();             // Close output file
        remove(filename.c_str());       // Delete output file
    }
    
    // Matrix initialization
    matrixInitialization();
    for (int i = 2; i <= 8; i++) {
        // Calculation of sequantial block size
        sequentialB(i);
        // Print block size b
        if (printRequired) cout << "Block size 2^" << i << endl;
        // Save block size b in the file
        if (outputFileEnabled) outputFile << b;
        // Calculate three times the performance for reliable results
        for (int i = 0; i < 3; i++) {
            // Call the routine
            routine1();
            // Print the results
            if (printRequired) cout << "Routine 1 take " << elapsed_time << " milliseconds" << endl;
            // Save the results in the file
            if (outputFileEnabled) outputFile << "," << elapsed_time; 
        }
        // Endl for print and file formatting
        if (printRequired) cout << endl;
        if (outputFileEnabled) outputFile << endl;
    }
    // Close output file
    if (outputFileEnabled) outputFile.close();

    return 0;
}

