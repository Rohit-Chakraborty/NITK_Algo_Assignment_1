import matplotlib.pyplot as plt
import numpy as np

# Read timing data from the file
def read_timing_data(filename):
    sizes = []
    times = []
    with open(filename, 'r') as file:
        for line in file:
            # Assuming the format is "filename time"
            parts = line.split()
            if len(parts) == 2:
                # Extract the input size from the filename if needed, or use the file index
                file_name = parts[0]
                time_taken = float(parts[1])
                
                # If filenames are meaningful, parse the size, otherwise just use the index
                try:
                    # Assuming filename format like "input1000.txt", extract "1000"
                    size = int(''.join(filter(str.isdigit, file_name)))
                except ValueError:
                    size = len(sizes) + 1  # Use a sequence number if the filename doesn't contain a size
                
                sizes.append(size)
                times.append(time_taken)

    return sizes, times

# Plot the data with connecting lines only
def plot_multiple_files(filepaths, labels, colors):
    plt.figure()

    for i, filepath in enumerate(filepaths):
        sizes, times = read_timing_data(filepath)
        
        # Plot the data with connecting lines only
        plt.plot(sizes, times, color=colors[i], label=labels[i])

    plt.title('Average Case of 6 sorting algorithms')
    plt.xlabel('Input Size')
    plt.ylabel('Time (seconds)')
    plt.grid(True)
    plt.xticks([])  # Hide x-axis ticks and labels
    plt.legend()
    plt.show()

# Main function
def main():
    # List of file paths for different sorting algorithms
    filepaths = [
        #  'C:/Users/91907/OneDrive/Desktop/Algo Assgn 1/Outputs/Timing/Quick_Sort.txt',
        #  'C:/Users/91907/OneDrive/Desktop/Algo Assgn 1/Outputs/Timing/Bubble_Sort.txt',
        #  'C:/Users/91907/OneDrive/Desktop/Algo Assgn 1/Outputs/Timing/Radix_Sort.txt',
        #  'C:/Users/91907/OneDrive/Desktop/Algo Assgn 1/Outputs/Timing/Merge_Sort.txt',
        'C:/Users/91907/OneDrive/Desktop/Algo Assgn 1/Timing/Avg/Bubble.txt',
        'C:/Users/91907/OneDrive/Desktop/Algo Assgn 1/Timing/Avg/Insertion.txt',
        'C:/Users/91907/OneDrive/Desktop/Algo Assgn 1/Timing/Avg/Quick.txt',
        'C:/Users/91907/OneDrive/Desktop/Algo Assgn 1/Timing/Avg/Merge.txt',
        'C:/Users/91907/OneDrive/Desktop/Algo Assgn 1/Timing/Avg/Heap.txt',
        'C:/Users/91907/OneDrive/Desktop/Algo Assgn 1/Timing/Avg/Radix.txt'
    ]

    # Corresponding labels for each file
    labels = ['Bubble Sort', 'Insertion Sort', 'Merge Sort ', 'Quick Sort', 'Heap Sort', 'Radix Sort']

    # Colors for each algorithm's plot
    colors = ['blue', 'green', 'red', 'yellow', 'purple', 'cyan']

    plot_multiple_files(filepaths, labels, colors)

if __name__ == "__main__":
    main()
