#ifndef REGISTRO_H
#define RESISTRO_H

#include "../../Utils/ThreadBase/ThreadBase.h"
#include "../../Utils/PosixShMem/PosixShMem.h"
#include "../../Files/Struct_sensors.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Registro : public ThreadBase
{
private:
    void startActivity() override;
    void stopActivity() override;
    int run() override;
    void salvar();

    PosixShMem *memoriaCompartilhada;
    Sensors sensorsData;
    Sensors lastData;

    ostringstream buffer;
    ofstream saida;
    long long unsigned int count;

public:
    Registro();
    ~Registro();
};

#endif