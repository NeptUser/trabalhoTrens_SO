// Traffic Collision Avoidance System (TCAS)
#ifndef TCAS_H
#define TCAS_H

#include <qmutex.h>

class TCAS
{
public:
    // Mutex para as 9 regiões críticas definidas
    QMutex pontosCriticos[9];
};

#endif // TCAS_H
