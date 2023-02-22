#ifndef CP_UTILS
#define CP_UTILS

void checkCUDAError (const char *msg);
void startKernelTime (cudaEvent_t *start, cudaEvent_t *stop);
float stopKernelTime (cudaEvent_t *start, cudaEvent_t *stop);

#endif