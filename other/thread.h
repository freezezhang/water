#ifndef THREAD_H_
#define THREAD_H_

//#include <pthread.h>

class Thread {
 public:
	 void Start();
	 void End();

 private:
	 pthread_t pid_;
};

#endif // THREAD_H_
