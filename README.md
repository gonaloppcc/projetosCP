# projetosCP

This repository contains projects developed for the Computação Paralela (Parallel Computing) course.

## Project 1: Matrix Multiplication

**Objective:** Implement a parallel matrix multiplication algorithm using OpenMP to enhance computational efficiency.

**Details:**

- **Input:** Two matrices, A and B.

- **Output:** Matrix C, the product of A and B.

- **Implementation:** Utilize OpenMP directives to parallelize the multiplication process, aiming to reduce execution time compared to a sequential approach.

**Files:**

- `projeto1/`: Contains the source code and related files for Project 1.

- `projeto1/TP1_enunciado.pdf`: Detailed project description and requirements. 

## Project 2: Parallel Sorting Algorithm

**Objective:** Develop a parallel sorting algorithm using MPI (Message Passing Interface) to sort a large dataset efficiently.

**Details:**

- **Input:** An unsorted array of integers.

- **Output:** A sorted array in ascending order.

- **Implementation:** Apply MPI to distribute the sorting task across multiple processors, implementing a parallel version of the merge sort algorithm to achieve improved performance over traditional sorting methods.

**Files:**

- `projeto2/`: Contains the source code and related files for Project 2.

- `projeto2/TP2_enunciado.pdf`: Detailed project description and requirements. 

## Compilation and Execution

**Requirements:**

- GCC compiler with OpenMP support for Project 1.

- MPI library (e.g., MPICH or OpenMPI) for Project 2.

**Instructions:**

1. **Clone the repository:**

   ```bash
   git clone https://github.com/gonaloppcc/projetosCP.git
   ```

2. **Navigate to the project directory:**

   ```bash
   cd projetosCP/projeto1   # For Project 1
   cd projetosCP/projeto2   # For Project 2
   ```

3. **Compile the code:**

   - For Project 1:

     ```bash
     gcc -fopenmp -o matrix_multiplication matrix_multiplication.c
     ```

   - For Project 2:

     ```bash
     mpicc -o parallel_sort parallel_sort.c
     ```

4. **Run the executable:**

   - For Project 1:

     ```bash
     ./matrix_multiplication
     ```

   - For Project 2:

     ```bash
     mpirun -np <number_of_processes> ./parallel_sort
     ```

## License

This repository is licensed under the MIT License.

## Acknowledgments

Special thanks to the Computação Paralela course instructors and TAs for their guidance and support throughout the development of these projects. 
