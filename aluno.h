#ifndef ALUNO_H
#define ALUNO_H

#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include <ctime>
#include <pqxx/pqxx>
#include "postgres.h"

using namespace std;

class Aluno {
    public:
        Aluno(string);
        
        string getId();
        string getNome();
        string getCursoId();

        string selectNomeDoCurso(pqxx::work &);
        pqxx::result selectGrade(pqxx::work &);
        pqxx::result selectPeriodosDoCurso(pqxx::work &);
        pqxx::result selectTurmasDisponiveis(pqxx::work &);
        void insertInscricoes(pqxx::work &, string);
        pqxx::result selectInscricoes(pqxx::work &);
        pqxx::result selectPeriodosDasInscricoes(pqxx::work &);

        int printGrade();
        int printTurmasDisponiveis();
        int fazerInscricoes(string);
        int printInscricoes();
        int cancelarInscricoes(string);

    private:
        string id;
        string nome;
        string curso_id;
        string semestreAtual = "2021.1";
};

#endif
