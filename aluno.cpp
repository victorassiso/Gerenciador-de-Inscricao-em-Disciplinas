#include "aluno.h"

Aluno::Aluno(string aluno_id)
{
    Postgres postgres;
    pqxx::connection con(postgres.getConnection_str().c_str());
    pqxx::work wrk(con);
    
    pqxx::result aluno = wrk.exec("SELECT * FROM alunos WHERE id = " + aluno_id);

    id = to_string(aluno[0][0]);
    nome = to_string(aluno[0][1]);
    curso_id = to_string(aluno[0][2]);
}

Aluno::~Aluno(){ cout << "Aluno destruído" << endl; }

string Aluno::getId(){ return id; }

string Aluno::getNome(){ return nome; }

string Aluno::getCursoId(){ return curso_id; }
