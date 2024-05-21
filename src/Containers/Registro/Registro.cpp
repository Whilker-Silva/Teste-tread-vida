#include "Registro.h"

Registro::Registro()
{
    this->serialSensors = NULL;
    this->memoriaCompartilhada = NULL;

    this->startActivity();
}

void Registro::startActivity()
{

    this->serialSensors = new Serial(encoderInterrupt, BAUD_RATE, "ttyUSB0");
    this->memoriaCompartilhada = new PosixShMem("memoriaCompartilhada", sizeof(encoderData));
    cout << "Inicializando o a thread de registro" << endl;

    ThreadBase::startActivity();
}

Registro::~Registro()
{
    this->stopActivity();
}

void Registro::stopActivity()
{

    ThreadBase::stopActivity();

    if (this->memoriaCompartilhada)
    {
        delete this->memoriaCompartilhada;
    }
    delete serialSensors;

    this->memoriaCompartilhada = NULL;
    this->serialSensors = NULL;
}

int Registro::run()
{

    this->is_running = 1;
    this->is_alive = 1;

    this->tim1.tv_sec = 1;
    this->tim1.tv_nsec = 0;

    

    while (this->is_alive)
    {
        cout << serialSensors->read('\n') << endl;
        nanosleep(&this->tim1, NULL);
    }

    this->is_running = 0;
    pthread_exit(NULL);

    return 1;
}