#include "BlockQueue.hpp"
#include <unistd.h>
using namespace std;
pthread_mutex_t c_lock;
pthread_mutex_t p_lock;
void* consumer_run(void* arg)
{
    BlockQueue<Task>* pbq = (BlockQueue<Task>*)arg;
    
    while (true)
    {
        //int t = 0;
        pthread_mutex_lock(&c_lock);
        Task t;
        pbq->Take(t);
        sleep(1);
        //cout << "consume data :" << t << endl;
        cout<<"编号 "<< pthread_self()<<" 消费者" <<" consume task is "  <<  t._x <<  " + " << t._y << " = " << t.Run() << endl;
        pthread_mutex_unlock(&c_lock);
    }
}
void* productor_run(void* arg)
{
    sleep(1);
    BlockQueue<Task>* pbq = (BlockQueue<Task>*)arg;

    while (true)
    {
        pthread_mutex_lock(&p_lock);
        int x = rand()%10 + 1;
        int y = rand()%100 +1;
        Task t(x,y);
        pbq->Put(t);
       // cout << "product data :" << t << endl;
        cout <<"编号 " <<pthread_self()<< " 生产者" <<" product Task is : " << x  << " + " << y << " = ?" << endl;
        pthread_mutex_unlock(&p_lock);
        sleep(1);

    }
}
int main()
{
    BlockQueue<Task> bq;
    pthread_t c1,c2,c3,p1,p2,p3;
    
    pthread_mutex_init(&c_lock, nullptr);
    pthread_mutex_init(&p_lock,nullptr);

    pthread_create(&c1, nullptr, consumer_run, (void*)&bq);
    pthread_create(&c2, nullptr, consumer_run, (void*)&bq);
    pthread_create(&c3, nullptr, consumer_run, (void*)&bq);
    pthread_create(&p1, nullptr, productor_run, (void*)&bq);
    pthread_create(&p2, nullptr, productor_run, (void*)&bq);
    pthread_create(&p3, nullptr, productor_run, (void*)&bq);

    pthread_join(c1,nullptr);
    pthread_join(c2,nullptr);
    pthread_join(c3,nullptr);
    pthread_join(p1,nullptr);
    pthread_join(p2,nullptr);
    pthread_join(p3,nullptr);

    pthread_mutex_destroy(&c_lock);
    pthread_mutex_destroy(&p_lock);
    return 0;
}
