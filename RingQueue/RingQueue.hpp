#pragma once 

#include <iostream>
#include <semaphore.h>
#include <vector>

template <class T>
class RingQueue
{
  private:
        std::vector<T> _v;
        int _cap;
        // 两个信号量
        sem_t c_sem_data;
        sem_t p_sem_blank;
        // 两个下标索引
        
        int c_index;
        int p_index;
  private:
        void P(sem_t &s)
        {
          sem_wait(&s);
        }
        void V(sem_t &s)
        {
          sem_post(&s);
        }

  public:
        RingQueue(int cap)
          :_cap(cap),_v(cap)
        {
           sem_init(&c_sem_data, 0, 0);
           sem_init(&p_sem_blank, 0, cap);
           c_index = p_index = 0;
        }
        
        ~RingQueue()
        {
           sem_destroy(&c_sem_data);
           sem_destroy(&p_sem_blank);
           c_index = p_index = 0;
        }
        void Put(T &in)
        {
            P(p_sem_blank);
            _v[p_index] = in;
            p_index++;
            p_index %= _cap;
            V(c_sem_data);
        }
        void Get(T &out)
        {
          // out 为输出型参数，由调用者传入引用获取内容
          P(c_sem_data);
          out = _v[c_index];
          c_index++;
          c_index %= _cap;
          V(p_sem_blank);
        }
};
