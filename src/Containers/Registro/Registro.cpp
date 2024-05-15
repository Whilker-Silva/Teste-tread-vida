#include "Registro.h"

Registro::Registro()
{   
    this->serialEncoder = NULL;    
    this->memoriaCompartilhada = NULL;
    this->startActivity();
}

void Registro::startActivity()
{   
    cout << "Inicializando o a thread de registro" << endl;
    
    this->serialEncoder = new Serial(encoderInterrupt, BAUD_RATE, "ttyUSB0");
    this->memoriaCompartilhada = new PosixShMem("memoriaCompartilhada", sizeof(encoderData));
      

    ThreadBase::startActivity();
}

Registro::~Registro()
{
    this->stopActivity();   
}

void Registro::stopActivity()
{       
    delete serialEncoder;
    serialEncoder = NULL;
    
    if (this->memoriaCompartilhada)
        delete this->memoriaCompartilhada;

    this->memoriaCompartilhada = NULL;

    ThreadBase::stopActivity();    
}

int Registro::run(){

    this->is_running = 1;
    this->is_alive = 1;

    this->tim1.tv_sec = 0;
    this->tim1.tv_nsec = 500000;   

    
   
    while (this->is_alive)
    {
        string aux;
        
        aux = serialEncoder->read('\n');
        cout<<aux<<endl;

        nanosleep(&this->tim1, &this->tim2);
        
    }

    this->is_running = 0;
    pthread_exit(NULL);

    return 1;
};