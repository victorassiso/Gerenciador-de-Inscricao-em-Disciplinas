#include "aluno.h"

Aluno::Aluno(string aluno_id)
{
    try
    {
        //Abre Conexão com o BD
        Postgres postgres;
        pqxx::connection con(postgres.getConnection_str().c_str());
        pqxx::work wrk(con);
        
        pqxx::result aluno = wrk.exec("SELECT * FROM alunos WHERE id = " + aluno_id);
        //Fecha Conexão com o BD
        con.disconnect();
        
        id = to_string(aluno[0][0]);
        nome = to_string(aluno[0][1]);
        curso_id = to_string(aluno[0][2]);
        
        cout << "-Log: Aluno criado!" << endl;
    }
    catch (exception const &e)
    {
        std::cerr << e.what() << std::endl;
        cout << "ERRO: Falha no Login!" << endl;
        id = "-1";
    }
}

Aluno::~Aluno(){ cout << "-Log: Aluno destruído!" << endl; }

string Aluno::getId(){ return id; }

string Aluno::getNome(){ return nome; }

string Aluno::getCursoId(){ return curso_id; }
