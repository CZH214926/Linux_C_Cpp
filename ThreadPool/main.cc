#include "ThreadPool.hpp"

int main()
{
    ThreadPool *tp = new ThreadPool();
    tp->ThreadPoolInit();

    //server
    int count = 20;
    while(count){
        int x = rand()%10+1;
        Task t(x);
        tp->Put(t);
        sleep(1);
        count--;
    }

	
	delete tp;
	
    return 0;
}
