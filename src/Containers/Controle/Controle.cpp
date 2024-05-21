#include "Controle.h"

Controle::Controle()
{
    this->udp = NULL;
    this->serialMotor = NULL;
    this->startActivity();
}

void Controle::startActivity()
{
    cout << "Inicializando a thread de controle" << endl;

    this->udp = new UDP();
    this->serialMotor = new Serial(motorInterrupt, BAUD_RATE, "ttyS1");
    ThreadBase::startActivity();
}

Controle::~Controle()
{
    this->stopActivity();
}

void Controle::stopActivity()
{
    ThreadBase::stopActivity();

    delete this->udp;
    delete this->serialMotor;

    this->udp = NULL;
    serialMotor = NULL;

    cout << "STOPPED THREAD CONTROLE" << endl;
}

int Controle::run()
{

    this->is_running = 1;
    this->is_alive = 1;

    this->tim1.tv_sec = 0;
    this->tim1.tv_nsec = 10000000L;

    while (this->is_alive)
    {
        serialMotor->write(udp->read());
        nanosleep(&this->tim1, &this->tim2);
    }

    this->is_running = 0;
    pthread_exit(NULL);

    return 1;
}
