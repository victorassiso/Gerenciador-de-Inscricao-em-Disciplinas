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

        //Funções auxiliares
        string dataTimestamp(); //Retorna um timestamp no formato necessário
        vector<string> separaStringPorEspaco(string &);
        bool validaIDsNaTabela(pqxx::result &, int, string &);
};

#endif