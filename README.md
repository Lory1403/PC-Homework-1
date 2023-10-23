# PC-Homework-1
This repository containes the solutions I have developed for the first assignment of the course ***"Introduction to Parallel Computing [146209] - Prof. Vella"*** about ***"Implicit parallelism techniques and performance models"*** 

# Execution Guide

This guide provides instructions on how to personalize and run the provided C++ code to accomplish the task. The code is designed to be executed on a Linux system. If you are using a Windows system, you can use the Windows Subsystem for Linux (WSL) to run the code.

- [Prerequisites](#prerequisites)
- [Execution](#execution)
- [Usage](#usage)
- [Example Usages](#example-usages)
- [Output](#output)

## Prerequisites
> [!IMPORTANT] 
> **C++ Compiler**: You need a C++ compiler installed on your system.

## Execution
To execute the code, follow these steps:  
1. Open your terminal.

2. Navigate to the directory containing the ce code file and your terminal.

3. *(Optional)* Personalize the code by changing the values of the arguments in the `script.sh` file.
   
4. Run the following command to run the script: `./script.sh`

## Usage
Accessing the `./script.sh` file, you can run the programs with various options. The programs accept command-line arguments to customize its behavior. Here are the available options:

* **`-f`** or **`--file`**: Specify the name of the output file (optional). The output file is required to be in *.CSV* format.

* **`-p`** or **`--print`**: Enable this flag to display array sizes and routine execution times in the terminal.

* **`-s`** or **`--size`**: Specify a fixed array size (optional). This disables the default array size loop.

## Example Usages
**Basic Usage**  
To run the program with default settings and no file output:
```bash
./hw1_pt*
```

**Specifying Output File**  
To run the program and save results to a file named "output.csv":

```bash
./hw1_pt* -f output.csv
```
**Enabling Printing**  
To run the program and display results in the terminal:

```bash
./hw1_pt* -p
```
**Specifying Array Size**  
To run the program with a specific array size (e.g., 1024):

```bash
./hw1_pt* -s 1024
```

## Output
If you specify an output file using the **\`-f\`** or **\`--file\`** option, the results will be saved in a *.CSV* file with the following format:

```python
ArraySize/BlockSize,Test1,Test2,Test3
n1,elapsed_time_1,elapsed_time_2,elapsed_time_3
n2,elapsed_time_1,elapsed_time_2,elapsed_time_3
...
```
* **\`ArraySize/BlockSize\`**: The size of the array.
* **\`Test1\`**, **\`Test2\`**, **\`Test3\`**: Execution times of the routine for three test runs.