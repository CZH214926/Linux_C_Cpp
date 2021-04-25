#pragma once

#include <iostream>
#include <queue>
#include <unistd.h>
#include <math.h>

#define NUM 5

class Task{
    public:
        int base;
    public:
        Task(){}
        Task(int _b):base(_b){}

        void Run()
        {
            std::cout <<"thread is[" << pthread_self() << "] task run ... done: base# "<< base << " pow is# "<< pow(base,2) << std::endl;
        }
        ~Task(){}
};

class ThreadPool{
    private:
        std::queue<Task*> q;
        int max_num;
        pthread_mutex_t lock;
        pthread_cond_t cond; //only consumer, thread pool thread;
    public:
        void LockQueue()
        {
            pthread_mutex_lock(&lock);
        }
        void UnlockQueue()
        {
            pthread_mutex_unlock(&lock);
        }
        bool IsEmpty()
        {
            return q.size() == 0;
        }
        void ThreadWait()
        {
            pthread_cond_wait(&cond, &lock);
        }
        void ThreadWakeup()
        {
            //if(low_water > 30){
            //    pthread_cond_broadcast(&cond);
            //}
			// 只唤醒一个线程  避免  惊群效应
            pthread_cond_signal(&cond);
        }
        void ThreadsWakeup()
        {
            pthread_cond_broadcast(&cond);
        }
    public:
	    // 构造函数里尽量不要做有风险的事情
        ThreadPool(int _max=NUM):max_num(_max)
        {}
		
		//设计线程的例程是静态的为了解决成员函数默认的this形参带来的错误
        static void* Routine(void *arg) 
        {
			//线程分离
		          	pthread_detach(pthread_self());
			 
                ThreadPool *this_p = (ThreadPool*)arg;
			
                this_p->LockQueue();
				
				// 用 while 避免线程被假唤醒，不能用 if 
                while(this_p->IsEmpty()){
                    this_p->ThreadWait(); 
                }

                Task t;
                if(!this_p->IsEmpty()){
                    this_p->Get(t);
                }
                this_p->UnlockQueue();
                t.Run();
                return (void*)0;
        }
        void ThreadPoolInit()
        {
            pthread_mutex_init(&lock, nullptr);
            pthread_cond_init(&cond, nullptr);
			//不关心线程id
            pthread_t t;
            for(int i = 0; i < max_num; i++){
                pthread_create(&t, nullptr, Routine, this);
            }
        }
        //server
        void Put(Task &in)
        {
            LockQueue();
            q.push(&in);
            UnlockQueue();

            ThreadWakeup();
        }
        //Thread pool t;
        void Get(Task &out)
        {
            Task*t = q.front();
            q.pop();
            out = *t;
        }
        ~ThreadPool()
        {
            pthread_mutex_destroy(&lock);
            pthread_cond_destroy(&cond);
        }

};

