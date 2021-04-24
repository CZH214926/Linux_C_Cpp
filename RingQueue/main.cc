#include "RingQueue.hpp"
#include <unistd.h>

using namespace std;

void *consumer(void *arg)
{
  RingQueue<int>* rq = (RingQueue<int>*)arg;

  while (true)
  {
      sleep(1);
      int t;
      rq->Get(t);
      cout << "consumer done ..." << t << endl;
  }

}
void *productor(void* arg)
{
  RingQueue<int>* rq = (RingQueue<int>*)arg;
  int count = 100;
  while (true)
  {
    rq->Put(count);
    count++;
    if (count > 110)
    {
        count = 100;
    }
    cout << "productor done" << endl;
  }
}
int main()
{
    pthread_t c,p;
    RingQueue<int> rq(5);
    
    pthread_create(&c, nullptr, consumer, &rq);
    pthread_create(&p, nullptr, productor,&rq);

    pthread_join(c,nullptr);
    pthread_join(p,nullptr);
    return 0;
}
