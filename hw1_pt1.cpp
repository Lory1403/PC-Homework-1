#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <map>
#include <fstream>
#include <string>

using namespace std;

// Create arrays A, B, and C
float* A;
float* B;
float* C;
// Variables for arrays lenght and for test function performance
long int n;
double elapsed_time;

// Function to arrays initialization with n length
void arrayInitialization() {
    A = new float[n];
    B = new float[n];
    C = new float[n];

    // Initialize arrays A and B with random float values
    for (int i = 0; i < n; i++) {
        A[i] = static_cast<float>(rand()) / RAND_MAX;
        B[i] = static_cast<float>(rand()) / RAND_MAX;
    }
}

// Function to calculate powers of two
void sequentialN(int power) {
    n = pow(2, power);
}

// Function to perform element-wise addition
void routine1() {
    // Take start time
    clock_t start_time = clock();

    // Arrays addition
    for (int i = 0; i < n; i++) {
        C[i] = A[i] + B[i];
    }
    
    // Take end time
    clock_t end_time = clock();
    // Calculate the time elapsed between start and end
    elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000;
}

int main(int argc, char const *argv[]) {
    // Set the random number generator’s seed value
    srand (time(NULL));
    
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

    // Output file initialization
    if (outputFileEnabled) outputFile << "ArraySize,Test1,Test2,Test3" << endl;
    // For loop
    for (int i = 4; i <= 22; i++) {
        // Calculation of sequential lenght n
        sequentialN(i);
        // Array initialization with new lenght n
        arrayInitialization();
        // Print length n
        if (printRequired) cout << "Array size 2^" << i << endl;
        // Save lenght n in the file
        if (outputFileEnabled) outputFile << n;
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

    // Clean up memory
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}