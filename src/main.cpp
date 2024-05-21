#include <iostream>
#include <cstdlib>
#include "Containers/Controle/Controle.h"
#include "Containers/Aquisicao/Aquisicao.h"
#include "Utils/Serial/Serial.h"
#include "Files/DefinePin.h"

using namespace std;

int main(int argc, char *argv[]) /// < Main function that create and calls for reading and writing in memory
{   
    Aquisicao *aquisicao = new Aquisicao();
    Controle *controle = new Controle();
    

    int quit = -1;
    do
    {
        cin >> quit;
    } while (quit != 0);

    delete controle;
    delete aquisicao;

    return EXIT_SUCCESS;
}