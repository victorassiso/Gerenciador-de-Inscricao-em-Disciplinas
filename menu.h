#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

class Menu 
{
    public:
        void printTelaDeLogin();
        void printMenuPrincipal();
        
        template <typename T>//int ou char
        void getInputVerboso(T&, int);//Valida input e limpa stream
        template <typename T>
        void getInput(T&, int);
        
        int getOpcaoMenu();//Valida e retorna opção do Menu
        int getOpcaoLogin();//Valida e retorna opção de Login

        void pressioneEnterParaContinuar();
        bool confirma();//Pede [S/N] para continuar
};

#endif