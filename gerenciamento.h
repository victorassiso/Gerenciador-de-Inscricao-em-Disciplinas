#ifndef GERENCIAMENTO_H
#define GERENCIAMENTO_H

#include "requisicao.h"

class Gerenciamento: public Requerimento
{
    public:
        Gerenciamento(string);
        ~Gerenciamento();

        int printGrade();
        int printTurmasDisponiveis();
        int fazerInscricoes(string);
        int printInscricoes();
        int cancelarInscricoes(string);
};

#endif