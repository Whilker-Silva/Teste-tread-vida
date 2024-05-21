#include "Serial.h"

Serial::Serial(int interrupt, int baudRate, string p)
{
    string porta = "/dev/" + p;
    this->serialport = serialOpen(porta.c_str(), baudRate);
    this->interrupt = interrupt;
    wiringPiSetup();
    pinMode(interrupt, OUTPUT);
    digitalWrite(interrupt, LOW);
}

Serial::~Serial()
{
    serialClose(serialport);
}

void Serial::write(string s)
{
    serialPrintf(serialport, "%s\n", s.c_str());
}

string Serial::read(char c)
{
    digitalWrite(interrupt, LOW);
    delay(10);
    digitalWrite(interrupt, HIGH);

    char receivedChar[256];
    int indice = 0;

    bool fim = false;
    long tempo = millis();
    do
    {

        if (serialDataAvail(serialport))
        {                                                  // Verifica se há dados disponíveis para leitura
            char incomingByte = serialGetchar(serialport); // Lê um byte da porta serial

            if (incomingByte == '\n' || incomingByte == c)
            {                                // Se encontrou um caractere de término de linha
                receivedChar[indice] = '\0'; // Adiciona um terminador de string ao final
                fim = true;
            }
            else
            {
                receivedChar[indice++] = incomingByte; // Armazena o byte no buffer e incrementa o índice
            }
        }

        if ((millis() - tempo) > 1000)
        {
            receivedChar[indice++] = '-';
            receivedChar[indice++] = '1';
            receivedChar[indice] = '\0';
            fim = true;
        }

    } while (!fim);

    digitalWrite(interrupt, LOW);
    return receivedChar;
}
