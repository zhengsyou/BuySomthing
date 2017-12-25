#ifndef CZWORKTHREAD_H
#define CZWORKTHREAD_H
#include <QThread>
#include "cznetworkaccessmanager.h"
#include "czorgnerve.h"

class CZWorkThread : public QThread
{
public:
    CZWorkThread();
    virtual void run();


private:
    CZOrgnerve m_orgnerve;
};

#endif // CZWORKTHREAD_H
