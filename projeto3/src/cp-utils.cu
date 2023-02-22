#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <sys/time.h>
#include <cuda.h>
#include <chrono>
#include "../include/cp-utils.h"

using namespace std;

void checkCUDAError (const char *msg) {
	cudaError_t err = cudaGetLastError();
	if( cudaSuccess != err) {
		cerr << "Cuda error: " << msg << ", " << cudaGetErrorString( err) << endl;
		exit(-1);
	}
}

// These are specific to measure the execution of only the kernel execution - might be useful
void startKernelTime (cudaEvent_t *start, cudaEvent_t *stop) {
	cudaEventCreate(start);
	cudaEventCreate(stop);

	cudaEventRecord(*start);
}

float stopKernelTime (cudaEvent_t *start, cudaEvent_t *stop) {
	cudaEventRecord(*stop);

	cudaEventSynchronize(*stop);
	float milliseconds = 0;
	cudaEventElapsedTime(&milliseconds, *start, *stop);

	return milliseconds;
}