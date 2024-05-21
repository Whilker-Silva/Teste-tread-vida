#include "Registro.h"

Registro::Registro()
{
    this->memoriaCompartilhada = NULL;

    // inicializa valor de leitura da memoria compartilhada
    this->sensorsData.pulsosEsquerda = 0;
    this->sensorsData.pulsosDireita = 0;
    this->sensorsData.pulsosTras = 0;
    this->sensorsData.estercamento = 0;

    // inicializa ultimo valor de leitura da memoria compartilhada
    this->lastData.pulsosEsquerda = 0;
    this->lastData.pulsosDireita = 0;
    this->lastData.pulsosTras = 0;
    this->lastData.estercamento = 0;

    this->startActivity();
}

void Registro::startActivity()
{
    this->memoriaCompartilhada = new PosixShMem("memoriaCompartilhada", sizeof(Sensors));
    cout << "Inicializando o a thread de resgistro" << endl;

    ThreadBase::startActivity();
}

Registro::~Registro()
{
    salvar();
    this->stopActivity();
}

void Registro::stopActivity()
{   
    ThreadBase::stopActivity();
    
    if (this->memoriaCompartilhada != NULL)
    {        
        delete this->memoriaCompartilhada;
    }

    this->memoriaCompartilhada = NULL;

    cout << "STOPPED THREAD REGISTRO" << endl;
}

int Registro::run()
{
    this->is_running = 1;
    this->is_alive = 1;

    this->tim1.tv_sec = 0;
    this->tim1.tv_nsec = 10000000L;

    while (this->is_alive)
    {
        this->memoriaCompartilhada->read(&sensorsData, sizeof(Sensors));

        if (sensorsData.time != lastData.time)
        {

            lastData.time = sensorsData.time;

            buffer << lastData.time << ";"
                   << lastData.pulsosEsquerda << ";"
                   << lastData.pulsosDireita << ";"
                   << lastData.pulsosTras << ";"
                   << lastData.estercamento << ";" << endl;
            
        }
        ++count;

        if ((count % 100) == 0)
        {
            salvar();
            buffer.str("");
        }

        nanosleep(&this->tim1, NULL);
    }

    this->is_running = 0;
    pthread_exit(NULL);

    return 1;
}

void Registro::salvar()
{
    saida.open("../DataRecorder.txt", ios_base::out | ios_base::app);
    saida << buffer.str();
    saida.close();
}