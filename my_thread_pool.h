#ifndef MY_THREAD_POOL_H
#define MY_THREAD_POOL_H

#include <QThreadPool>

class my_thread_pool : public QThreadPool
{
public:
    my_thread_pool();
};

#endif // MY_THREAD_POOL_H
