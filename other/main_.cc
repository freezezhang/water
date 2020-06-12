/*
 * main.cc
 *
 *  Created on: 2012-11-2
 *      Author: zdj
 */

#include "memory_pool.h"
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

timeval start_time() {
	timeval time_value;
	gettimeofday(&time_value, NULL);
	return time_value;
}

timeval end_time(){
	timeval time_value;
	gettimeofday(&time_value, NULL);
	return time_value;
}

timeval run_time(const timeval& start_time, const timeval& end_time) {
	timeval tmp;
	tmp.tv_sec = end_time.tv_sec - start_time.tv_sec;
	tmp.tv_usec = end_time.tv_usec - start_time.tv_usec;
	if (tmp.tv_usec < 0) {
		tmp.tv_sec -= 1;
		tmp.tv_usec += 1000000;
	}
	printf("run time is %lus, %luus\n", tmp.tv_sec, tmp.tv_usec);
	return tmp;
}
/* */
int main(void) {
	MemoryPool mp;
	mp.Init();


	timeval start = start_time();
	for (int j = 0; j < 32; ++j) {
		for (int i = 0; i < 600000; ++i) {
			void* ptr = mp.Allocate(8 * j + 3);
			mp.Deallocate(ptr, 8 * j + 3);
			/*
			if (ptr == nullptr) {
				printf("null, j = %d, i = %d\n", j, i);
				break;
			}
			*/
			//strcpy((char*)ptr, "zdj");
//			printf("i = %d, j = %d, %s\n", i, j, (char*)ptr);
		}
	}
	printf("allocate_size = %lu\n", mp.allocate_size_);

	timeval end = end_time();
	run_time(start, end);
}
/* * /
int main(void) {
	size_t allocate_size = 0;
	timeval start = start_time();
	for (int j = 0; j < 32; ++j) {
		for (int i = 0; i < 600000; ++i) {
			int malloc_size = 8 * j + 3;
			void* ptr = malloc(malloc_size);
			free(ptr);
			allocate_size += malloc_size;
		
			if (ptr == nullptr) {
				printf("null, j = %d, i = %d\n", j, i);
				break;
			}
	

//			strcpy((char*)ptr, "zdj");
//			printf("i = %d, j = %d, %s\n", i, j, (char*)ptr);
		}
	}
	printf("allocate_size = %lu\n", allocate_size);

	timeval end = end_time();
	run_time(start, end);
}
/* */
