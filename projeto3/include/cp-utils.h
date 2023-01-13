#ifndef CP_UTILS
#define CP_UTILS

void checkCUDAError (const char *msg);
void startKernelTime ();
void stopKernelTime ();

#endif