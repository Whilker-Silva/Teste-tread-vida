#include "Aquisicao.h"

Aquisicao::Aquisicao()
{
    this->serialSensors = NULL;
    this->memoriaCompartilhada = NULL;

    this->startActivity();
}

void Aquisicao::startActivity()
{

    this->serialSensors = new Serial(encoderInterrupt, BAUD_RATE, "ttyUSB0");
    this->memoriaCompartilhada = new PosixShMem("memoriaCompartilhada", sizeof(Sensors));
    cout << "Inicializando o a thread de aquisicao" << endl;

    ThreadBase::startActivity();
}

Aquisicao::~Aquisicao()
{
    this->stopActivity();
}

void Aquisicao::stopActivity()
{

    ThreadBase::stopActivity();

    if (this->memoriaCompartilhada)
    {
        delete this->memoriaCompartilhada;
    }
    delete serialSensors;

    this->memoriaCompartilhada = NULL;
    this->serialSensors = NULL;

    cout << "STOPPED THREAD AQUISICAO" << endl;
}

int Aquisicao::run()
{

    this->is_running = 1;
    this->is_alive = 1;

    this->tim1.tv_sec = 1;
    this->tim1.tv_nsec = 0;

    while (this->is_alive)
    {
        string buffer;
        buffer = serialSensors->read('\n');

        istringstream stream(buffer);
        stream >> sensorsData.pulsosEsquerda;
        stream >> sensorsData.pulsosDireita;
        stream >> sensorsData.pulsosTras;
        stream >> sensorsData.estercamento;

        memoriaCompartilhada->write(&sensorsData, sizeof(Sensors));

        nanosleep(&this->tim1, NULL);
    }

    this->is_running = 0;
    pthread_exit(NULL);

    return 1;
}