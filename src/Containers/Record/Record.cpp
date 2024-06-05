#include "Record.h"

Record::Record()
{
    this->memorySharedEncoder = NULL;

    // inicializa valor de leitura da memoria compartilhada
    this->encoderData.leftPulses = 0;
    this->encoderData.rigthPulses = 0;
    this->encoderData.backPulses = 0;

    // inicializa ultimo valor de leitura da memoria compartilhada
    this->lastData.leftPulses = 0;
    this->lastData.rigthPulses = 0;
    this->lastData.backPulses = 0;

    this->startActivity();
}

void Record::startActivity()
{
    this->memorySharedEncoder = new PosixShMem("sharedMemoryEncoder", sizeof(Encoder_data));

    cout << "Start the thread Record" << endl;
    ThreadBase::startActivity();
}

Record::~Record()
{
    salvar();
    this->stopActivity();
}

void Record::stopActivity()
{
    ThreadBase::stopActivity();

    if (memorySharedEncoder != NULL)
    {
        delete memorySharedEncoder;
    }

    memorySharedEncoder = NULL;

    cout << "Stopped Thread Record" << endl;
}

int Record::run()
{
    this->is_running = 1;
    this->is_alive = 1;

    this->tim1.tv_sec = 0;
    this->tim1.tv_nsec = 10000000L;

    while (this->is_alive)
    {
        memorySharedEncoder->read(&encoderData, sizeof(Encoder_data));

        if (encoderData.time != lastData.time)
        {

            lastData.time = encoderData.time;

            buffer << lastData.time << ";"
                   << lastData.leftPulses << ";"
                   << lastData.rigthPulses << ";"
                   << lastData.backPulses << ";" << endl;
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

void Record::salvar()
{
    saida.open("../DataRecorder.txt", ios_base::out | ios_base::app);
    saida << buffer.str();
    saida.close();
}