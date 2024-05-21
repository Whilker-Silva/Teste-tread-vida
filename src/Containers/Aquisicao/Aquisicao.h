#ifndef AQUISICAO_H
#define AQUISICAO_H

#include "../../Utils/PosixShMem/PosixShMem.h"
#include "../../Utils/ThreadBase/ThreadBase.h"
#include "../../Utils/Serial/Serial.h"
#include "../../Files/Struct_sensors.h"
#include "../../Files/DefinePin.h"
#include <iostream>
#include <sstream>   

using namespace std;

class Aquisicao : public ThreadBase
{
private:
        
    void startActivity() override;
    void stopActivity() override;
    int run() override;   

    PosixShMem *memoriaCompartilhada;   
    Sensors sensorsData; 

    Serial *serialSensors;

public:
    Aquisicao();
    ~Aquisicao();
};


#endif