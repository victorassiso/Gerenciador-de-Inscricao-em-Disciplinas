#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <iomanip>

using namespace std;

class Menu 
{
    public:
        void printTelaDeLogin();
        void printMenuPrincipal();
        
        template <typename T>
        void getInput(T&, int);

        int getOpcaoMenu();
        int getOpcaoLogin();

        void pressioneEnterParaContinuar();
        bool confirma();
};

#endif