#include "aluno.h"

Aluno::Aluno(string aluno_id)
{
    setAluno(aluno_id);
    //Printa confirmação de Criação
    cout << "-Log: Aluno criado!" << endl;
}

Aluno::~Aluno(){ cout << "-Log: Aluno destruído!" << endl; }

string Aluno::getId(){ return id; }

string Aluno::getNome(){ return nome; }

string Aluno::getCursoId(){ return curso_id; }

void Aluno::setAluno(string aluno_id)
{
     try
    {
        //Abre Conexão com o BD
        Postgres postgres;
        pqxx::connection con(postgres.getConnection_str().c_str());
        pqxx::work wrk(con);
        
        //Realiza Requisição das informações do aluno conforme seu ID
        pqxx::result aluno = wrk.exec("SELECT * FROM alunos WHERE id = " + aluno_id);

        //Fecha Conexão com o BD
        con.disconnect();
        
        //Armazena informações nos membros da classe
        id = to_string(aluno[0][0]);
        nome = to_string(aluno[0][1]);
        curso_id = to_string(aluno[0][2]);
        
        //Printa confirmação de Criação
        cout << "-Log: Login realizado com o ID: " << getId() << endl;
    }
    catch (exception const &e)
    {
        cout << "ERRO: Falha no Login!" << endl;
        cerr << "Mensagem do Postgres: " << e.what() << std::endl;
        id = "-1";
    }
}