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

        string getNomeDoCurso(pqxx::work &);
        pqxx::result getGrade();
        pqxx::result getTurmasDisponiveis();
        pqxx::result getInscricoes();
        pqxx::result getPeriodosDoCurso();
        pqxx::result getPeriodosDasInscricoes();


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
