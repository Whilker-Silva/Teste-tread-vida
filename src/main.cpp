#include <iostream>
#include <cstdlib>
#include "Containers/Registro/Registro.h"
#include "Containers/Control/Control.h"
#include "Utils/wifiComunication/wifiComunication.h"


using namespace std;

int main (int argc, char* argv[])  
{
    wifiComunication *wifi = new wifiComunication(8080);

    cout << wifi->receive();

    int quit = -1;
    do
    {
        cin >> quit;
    } 
    while (quit != 0);

    //delete registro;

    return EXIT_SUCCESS;
}