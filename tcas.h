// Traffic colision avoidance system
#ifndef TCAS_H
#define TCAS_H

#include <qmutex.h>

class TCAS
{
public:
    //TCAS();

    QMutex pontosCriticos[9];
};

#endif // TCAS_H
