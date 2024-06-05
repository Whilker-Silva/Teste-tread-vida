#ifndef RECORD_H
#define RECORD_H

#include "../../Utils/ThreadBase/ThreadBase.h"
#include "../../Utils/PosixShMem/PosixShMem.h"
#include "../../Files/Struct_sensors.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Record : public ThreadBase
{
private:
    void startActivity() override;
    void stopActivity() override;
    int run() override;
    void salvar();

    PosixShMem *memorySharedEncoder;
    PosixShMem *memorySharedSteering;

    Encoder_data encoderData;
    Encoder_data lastData;

    ostringstream buffer;
    ofstream saida;
    long long unsigned int count;

public:
    Record();
    ~Record();
};

#endif