#ifndef REQUERIMENTO_H
#define REQUERIMENTO_H

#include "aluno.h"

class Requerimento: public Aluno
{
    protected:
        Requerimento(string);
        ~Requerimento();

        string selectNomeDoCurso(pqxx::work &);
        pqxx::result selectGrade(pqxx::work &);
        pqxx::result selectPeriodosDoCurso(pqxx::work &);
        pqxx::result selectTurmasDisponiveis(pqxx::work &);
        void insertInscricoes(pqxx::work &, string &);
        pqxx::result selectInscricoes(pqxx::work &);
        pqxx::result selectPeriodosDasInscricoes(pqxx::work &);
    
};

#endif