#pragma once
#include <iostream>
#include <pthread.h>
#include<queue>

class Task {
public:
       int _x;
       int _y;
public:
       Task(){}
       Task(int x, int y):_x(x),_y(y)
       {
          
       }
       int Run()
       {
         return _x + _y;
       }
};

template<class T>
class BlockQueue {
private:
       std::queue<T> _q;
       size_t _cap;
       pthread_mutex_t lock;
       pthread_cond_t  p_cond;
       pthread_cond_t  c_cond;
private:
       void LockQueue()
       {
          pthread_mutex_lock(&lock); 
       }
       void UnlockQueue()
       {
          pthread_mutex_unlock(&lock);
       }
       void ProductorWait()
       {
          std::cout << "productor wait ..." << std::endl;
          pthread_cond_wait(&p_cond, &lock);
       }
       void ConsumerWait()
       {
          std::cout << "consumer wait ..." << std::endl;
          pthread_cond_wait(&c_cond, &lock);
       }
       void WakeupProductor()
       {
          std::cout << "wake up productor ..." << std::endl;
          pthread_cond_signal(&p_cond);
       }
       void WakeupConsumer()
       {
          std::cout <<"wake up consumer ..." << std::endl;
          pthread_cond_signal(&c_cond);
       }
       bool IsFull()
       {
          return _q.size() >= _cap;
       }
       bool IsEmpty()
       {
          return _q.empty();
       }
public:
       BlockQueue(size_t cap = 5)
         :_cap(cap)
       {
           pthread_mutex_init(&lock, nullptr);
           pthread_cond_init(&p_cond, nullptr);
           pthread_cond_init(&c_cond, nullptr);
       }
       ~BlockQueue()
       {
           pthread_mutex_destroy(&lock);
           pthread_cond_destroy(&p_cond);
           pthread_cond_destroy(&c_cond);
       }
       void Put(const T& t)
       {
           // 生产者
           LockQueue();
           while (IsFull())
           {
              WakeupConsumer();
              ProductorWait();
           }
           _q.push(t);
           UnlockQueue();
       }
       void Take(T& t)
       {
           // 消费者
           LockQueue();
           while (IsEmpty())
           {
              WakeupProductor();
              ConsumerWait();
           }
           t = _q.front();
           _q.pop();

           UnlockQueue();
       }
};

