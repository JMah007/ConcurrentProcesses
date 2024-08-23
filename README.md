# ConcurrentProcesses

## Description
The assignment involves 1 parent thread which creates 4 child threads to run concurrently. As all
these threads access data from the same one struct, synchronisation techniques must be used to
ensure only one thread is able to access this resource at any given time. To ensure only one thread
can access the resource at a time, this thread must obtain a mutex lock, if the mutex lock is already obtained by
another thread, then the calling thread will have to pause where it is and wait until the lock is
released.

## How to compile and run the program

1. To compile, ensure all files are in the same directory and use the "make" command in the terminal
2. To run, enter "./mssv solution.txt 1" where mssv is program name, solution.txt is file we are reading from and 1 is the sleep delay time
