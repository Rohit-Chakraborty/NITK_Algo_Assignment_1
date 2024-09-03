#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <dirent.h> // For directory handling on POSIX systems
#include <cstring>
#include <chrono>   // For timing the sorting process

// Function to partition the array on the basis of the last element as pivot
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Pivot is the last element
    int i = (low - 1);     // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // Increment index of smaller element
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]); // Place the pivot element at its correct position
    return (i + 1);
}

// Function to perform quicksort using the last element as the pivot
void quickSortLastPivot(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        // Partition the array and get the pivot index
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition
        quickSortLastPivot(arr, low, pi - 1);
        quickSortLastPivot(arr, pi + 1, high);
    }
}

// Function to read integers from a file
std::vector<int> readFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    std::vector<int> data;
    int value;

    if (inFile.is_open()) {
        while (inFile >> value) { // Read integers separated by new lines or spaces
            data.push_back(value);
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }

    return data;
}

// Function to save integers to a file
void saveToFile(const std::vector<int>& data, const std::string& filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const int& num : data) {
            outFile << num << "\n";
        }
        outFile.close();
        std::cout << "File saved: " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

// Function to list files in a directory (POSIX)
std::vector<std::string> listFilesInDirectory(const std::string& directory) {
    std::vector<std::string> files;
    DIR* dir = opendir(directory.c_str());
    if (dir != nullptr) {
        struct dirent* entity;
        while ((entity = readdir(dir)) != nullptr) {
            // Ignore "." and ".."
            if (entity->d_type == DT_REG) {  // Only regular files
                files.push_back(entity->d_name);
            }
        }
        closedir(dir);
    } else {
        std::cerr << "Unable to open directory: " << directory << std::endl;
    }
    return files;
}

int main() {
    std::string inputDirectory = "C:/Users/91907/OneDrive/Desktop/Algo Assgn 1/Input/increasing/";  // Directory containing the input files
    std::string outputDirectory = "C:/Users/91907/OneDrive/Desktop/Algo Assgn 1/Outputs/Quick_Sort"; // Directory for the sorted output files
    std::string timingFile = "C:/Users/91907/OneDrive/Desktop/Algo Assgn 1/Outputs/Timing/Quick_Sort_Avg/Last_Pivot.txt";

    std::ofstream timingOutFile(timingFile);
    if (!timingOutFile.is_open()) {
        std::cerr << "Unable to open timing file: " << timingFile << std::endl;
        return 1;
    }
    
    // Get the list of files in the input directory
    std::vector<std::string> files = listFilesInDirectory(inputDirectory);

    // Iterate over each file
    for (const auto& filename : files) {
        std::string inputFilename = inputDirectory + "/" + filename; // Full path to the input file
        std::string outputFilename = outputDirectory + "/" + filename; // Full path to the output file

        // Read data from the input file
        std::vector<int> data = readFromFile(inputFilename);

        if (data.empty()) {
            std::cerr << "No data found in the file or the file is empty: " << inputFilename << std::endl;
            continue;
        }

        // Measure the start time
        auto start = std::chrono::high_resolution_clock::now();

        // Perform quicksort with the last element as the pivot
        quickSortLastPivot(data, 0, data.size() - 1);

        // Measure the end time
        auto end = std::chrono::high_resolution_clock::now();

        // Calculate the duration
        std::chrono::duration<double> duration = end - start;
        std::cout << "Time taken to sort " << filename << ": " << duration.count() << " seconds." << std::endl;

        // Save the sorted data to the output file
        saveToFile(data, outputFilename);
        timingOutFile << filename << " " << duration.count() << std::endl;
    }
    timingOutFile.close();
    std::cout << "All files sorted successfully!" << std::endl;

    return 0;
}
