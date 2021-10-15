#ifndef ALUNO_H
#define ALUNO_H

#include <vector>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <string>
#include <pqxx/pqxx>
#include "postgres.h"

using namespace std;

class Aluno
{
    protected:

    public:
        ~Aluno();
        Aluno(string);
        string getId();
        string getNome();
        string getCursoId();
        
        void setAluno(string);

    private:
        string id;
        string nome;
        string curso_id;
        string semestreAtual = "2021.1";
};

#endif
