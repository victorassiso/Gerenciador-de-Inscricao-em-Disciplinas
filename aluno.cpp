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

string Aluno::getId(){ return id; }
string Aluno::getNome(){ return nome; }
string Aluno::getCursoId(){ return curso_id; }

string Aluno::selectNomeDoCurso(pqxx::work &wrk)
{
    pqxx::result nomeDoCurso = wrk.exec(
        "SELECT nome\
        FROM cursos\
        WHERE id = '" + getCursoId() + "'"
    );
    
    return to_string(nomeDoCurso[0][0]);
}

pqxx::result Aluno::selectGrade(pqxx::work &wrk)
{
    pqxx::result grade = wrk.exec(
        "SELECT B.periodo, A.id, A.nome, B.pre_requisitos[1], B.pre_requisitos[2]\
        FROM disciplinas A\
        INNER JOIN grades B\
        ON B.disciplina_id = A.id\
        WHERE B.curso_id = '" + getCursoId() + "'\
        ORDER BY periodo ASC"
    );

    return grade;
}

pqxx::result Aluno::selectPeriodosDoCurso(pqxx::work &wrk)
{
    pqxx::result periodos = wrk.exec(
        "SELECT DISTINCT periodo\
        FROM grades\
        ORDER BY periodo ASC"
    );

    return periodos;
}

pqxx::result Aluno::selectTurmasDisponiveis(pqxx::work &wrk)
{
    pqxx::result turmas = wrk.exec(
        "WITH\
        gradeDoCurso AS\
        (\
            SELECT disciplina_id, pre_requisitos[1] AS p1, pre_requisitos[2] AS p2, periodo\
            FROM grades\
            WHERE curso_id = '" + getCursoId() + "'\
        ),\
        historicoDoAluno AS\
        (\
            SELECT disciplina_id\
            FROM historico\
            WHERE aluno_id = " + getId() + "\
        ),\
        gradeMenosHistorico AS\
        (\
            SELECT A.disciplina_id, A.p1, A.p2, A.periodo\
            FROM gradeDoCurso A\
            FULL OUTER JOIN historicoDoAluno B\
            ON A.disciplina_id = B.disciplina_id\
            WHERE B.disciplina_id IS NULL\
        ),\
        gradeMenosHistoricoMenosP1 AS\
        (\
            SELECT A.disciplina_id, A.p1, A.p2, A.periodo\
            FROM gradeMenosHistorico A\
            FULL OUTER JOIN historicoDoAluno B\
            ON A.p1 = B.disciplina_id\
            WHERE\
                (B.disciplina_id IS NOT NULL OR A.p1 IS NULL)\
            AND\
                A.disciplina_id IS NOT NULL\
        ),\
        gradeMenosHistoricoMenosP2 AS\
        (\
            SELECT A.disciplina_id, A.p1, A.p2, A.periodo\
            FROM gradeMenosHistoricoMenosP1 A\
            FULL OUTER JOIN historicoDoAluno B\
            ON A.p2 = B.disciplina_id\
            WHERE\
                (B.disciplina_id IS NOT NULL OR A.p2 IS NULL)\
            AND\
                A.disciplina_id IS NOT NULL\
        )\
        SELECT A.periodo, A.disciplina_id, B.descricao, B.vagas, B.id\
        FROM gradeMenosHistoricoMenosP2 A\
        INNER JOIN turmas B\
        ON A.disciplina_id = B.disciplina_id\
        ORDER BY A.periodo ASC, B.descricao"
    );

    return turmas;
}

void Aluno::insertInscricoes(pqxx::work &wrk, string values)
{
    pqxx::result inscricoes = wrk.exec(
        "INSERT INTO inscricoes\
        (aluno_id, turma_id, timestamp)\
        VALUES"
            + values + 
        "ON CONFLICT (aluno_id, turma_id)\
        DO NOTHING;"
    );
}

pqxx::result Aluno::selectInscricoes(pqxx::work &wrk)
{
    pqxx::result inscricoes = wrk.exec(
        "SELECT DISTINCT A.disciplina_id, A.descricao, A.vagas, A.id, G.periodo\
        FROM (\
            SELECT T.disciplina_id, T.descricao, T.vagas, T.id\
            FROM inscricoes I\
            INNER JOIN turmas T\
            ON I.turma_id = T.id\
            WHERE I.aluno_id = " + getId() +  
        ") A\
        INNER JOIN grades G\
        ON A.disciplina_id = G.disciplina_id\
        WHERE G.curso_id = '" + getCursoId() + "'\
        ORDER BY G.periodo ASC, A.descricao"
    );

    return inscricoes;
}

pqxx::result Aluno::selectPeriodosDasInscricoes(pqxx::work &wrk)
{
     pqxx::result periodos = wrk.exec(
        "SELECT DISTINCT G.periodo\
        FROM (\
            SELECT T.disciplina_id, T.descricao, T.vagas, T.id\
            FROM inscricoes I\
            INNER JOIN turmas T\
            ON I.turma_id = T.id\
            WHERE I.aluno_id = " + getId() + 
        ") A\
        INNER JOIN grades G\
        ON A.disciplina_id = G.disciplina_id\
        WHERE G.curso_id = '" + getCursoId() + "'\
        ORDER BY G.periodo ASC"
    );

    return periodos;
}

int Aluno::printGrade()
{
    //Abre Conexão com o Banco de Dados
    Postgres postgres;
    pqxx::connection con(postgres.getConnection_str().c_str());
    pqxx::work wrk(con);
    
    //PRINT GRADE
    string nomeDoCurso = selectNomeDoCurso(wrk);
    pqxx::result grade = selectGrade(wrk);
    pqxx::result periodos = selectPeriodosDoCurso(wrk);
    
    //Fecha Conexão com o BD
    con.disconnect();

    if (grade.size() < 1)
    {
        cout << "Tabela vazia ou erro (grade)" << endl;
        return -1;
    };
    if (nomeDoCurso.size() < 1)
    {
        cout << "Tabela vazia ou erro (curso)" << endl;
        return -1;
    };
    if (periodos.size() < 1)
    {
        cout << "Tabela vazia ou erro (periodos)" << endl;
        return -1;
    };

    //CABEÇALHO
    int larguraMaxima = 50;
    int laterais = larguraMaxima - (int)nomeDoCurso.size();
    cout << "+--------------------------------------------------------------------------+\n";
    if (laterais % 2 == 0)
    {
        cout << "| " << setw(laterais/2) << "" << "Curso de Graduação em " << nomeDoCurso << setw(laterais/2) << "" << " |\n";
    } else {
        cout << "| " << setw(laterais/2) << "" << "Curso de Graduação em " << nomeDoCurso << setw(laterais/2+1) << "" << " |\n";
    };
    cout << "+--------------------------------------------------------------------------+\n";
    
    //grade[row][column]
    //PERIODO
    int row = 0;
    string requisitos;

    for (int p = 0; p < (int)periodos.size(); p++)
    {
        cout << "|" << setw(32) << "" << periodos[p][0] << "º Período" << setw(32) << "" << "|\n";
        cout << "+--------+------------------------------------------------+----------------+\n";
        cout << "| Código | Nome                                           | Requisitos     |\n";
        cout << "+--------+------------------------------------------------+----------------+\n";

        //DISCIPLINAS
        while (grade[row][0] == periodos[p][0])
        {
            requisitos = "";
            grade[row][3].size() > 0 ? requisitos = to_string(grade[row][3]) : requisitos = "      ";
            grade[row][4].size() > 0 ? requisitos += ", " + to_string(grade[row][4]) : requisitos += "        ";
            cout << "| " << grade[row][1] << " | " << grade[row][2] << setw(46 - grade[row][2].size()) << "" << " | " << requisitos << " | " << endl;
            row+=1;
        }
        cout << "+--------+------------------------------------------------+----------------+\n";
    };
    cout << endl;
    
    return 0;
}

int Aluno::printTurmasDisponiveis()
{
    //Abre Conexão com o BD
    Postgres postgres;
    pqxx::connection con(postgres.getConnection_str().c_str());
    pqxx::work wrk(con);
    
    //Realiza requirementos ao BD
    pqxx::result turmas = selectTurmasDisponiveis(wrk);
    
    //Fecha conxeão com o BD
    con.disconnect();

    //Começa lógica de Impressão
    if (turmas.size() < 1)
    {
        cout << "Tabela vazia ou erro (turmas)" << endl;
        return -1;
    };
    
    //CABEÇALHO
    cout << "+--------------------------------------------------------------------------+\n"
         << "|                           Turmas Disponíveis                             |\n"
         << "+--------------------------------------------------------------------------+\n";
    
    //PERIODO
    int row = 0;
    auto periodoAtual = turmas[0][0].as<int>();//Menor período
    auto periodoLimite = turmas[turmas.size()-1][0].as<int>();

    while (row < turmas.size()-1)
    {
        cout << "|" << setw(32) << "" << periodoAtual << "º Período" << setw(32) << "" << "|\n";
        cout << "+--------+----------------------------------------------------+-------+----+\n";
        cout << "| Código | Nome                                               | Vagas | ID |\n";
        cout << "+--------+----------------------------------------------------+-------+----+\n";
        
        //DISCIPLINAS
        while (row < turmas.size() && turmas[row][0].as<int>() == periodoAtual)
        {
            cout << "| " << turmas[row][1] << " | " << turmas[row][2] << setw(50 - turmas[row][2].size()) << "" << " |   " << turmas[row][3] << "   | " << turmas[row][4] << setw(2- turmas[row][4].size()) << "" << " | "  << endl;
            row+=1;
        }
        cout << "+--------+----------------------------------------------------+-------+----+\n";
        
        if (row < turmas.size()-1)
            periodoAtual = turmas[row][0].as<int>();
        
    };
    cout << endl;

   return 0;
   
    /* Template:
    +--------------------------------------------------------------------------+
    |                           Turmas Disponíveis                             |
    +--------------------------------------------------------------------------+
    |                                1º Período                                |
    +--------+----------------------------------------------------+-------+----+
    | Código | Turma                                              | Vagas | ID |
    +--------+----------------------------------------------------+-------+----+
    | MAC238 | Cálculo III - A                                    |   1   | 1  |
    | MAC238 | Cálculo III - B                                    |   2   | 1  |
    +--------|----------------------------------------------------+-------+----+
    |                                2º Período                                |
    +--------+----------------------------------------------------+-------+----+
    | Código | Turma                                              | Vagas | ID |
    +--------+----------------------------------------------------+-------+----+
    | MAC238 | Cálculo III - A                                    |   4   | 1  |
    | MAC238 | Cálculo III - B                                    |   5   | 1  |
    +--------|----------------------------------------------------+-------+----+
    */
}

int Aluno::fazerInscricoes(string turmas_id)
{
    //Trata turmas_id vazio
    if (turmas_id.size() < 1)
    {
        cout << "Nenhuma turma foi selecionada" << endl;
        
        return 1;
    }

    //Abre conexão com o Banco de dados
    Postgres postgres;
    pqxx::connection con(postgres.getConnection_str().c_str());
    pqxx::work wrk(con);
    
    //Requere turmas disponíveis
    pqxx::result turmas = selectTurmasDisponiveis(wrk);

    //Fecha Conxeão com o BD
    con.disconnect();

    //Define timestamp 19:79:55
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string year = to_string(1900 + ltm->tm_year);
    string month = to_string(1 + ltm->tm_mon);
    string day = to_string(ltm->tm_mday);
    string hour = to_string(ltm->tm_hour);
    string min = to_string(ltm->tm_min);
    string sec = to_string(ltm->tm_sec);
    string timestamp = year + "-" + month + "-" + day + " " + hour + ":" + min + ":" + sec;

    //cria um VALUE para cada ID enquanto também os valida
    string values;
    string word = "";
    int i = 0;

    for (auto x : turmas_id)
    {
        if (x == ' ' || x == '\0')
        {
            for (i = 0; i < turmas.size(); i++)
            {
                if (to_string(turmas[i][4]) == word)
                {
                    values += "(" + id + ", '" + word + "', '" + timestamp + "'), ";
                    break;
                }
            }
            if (i == turmas.size()-1){
                cout << "Você não tem os pré-requisitos necessários para inscrever-se na Turma "
                     << turmas[i][2] << "." << endl;
            }
            word = "";
        }
        else
            word += x;
    }
    values += "(" + id + ", '" + word + "', '" + timestamp + "')"; //ultima palavra

    //Faz INSERT das inscrições tratando repetições
    insertInscricoes(wrk, values);
       
    //Salva alterações no Banco de Dados
    wrk.commit();
    //Fecha Conexão com o Banco de dados
    con.disconnect();

    return 0;
}

int Aluno::printInscricoes()
{
    //Abre conexão com o Banco de dados
    Postgres postgres;
    pqxx::connection con(postgres.getConnection_str().c_str());
    pqxx::work wrk(con);

    //Realiza Requisição ao BD
    pqxx::result inscricoes = selectInscricoes(wrk);

    //Trata Resposta vazia
    if (inscricoes.size() < 1)
    {
        cout << "Nenhuma inscrição foi encontrada" << endl;
        return -1;
    };
    
    //Realiza Requisição ao BD
    pqxx::result periodos = selectPeriodosDasInscricoes(wrk);

    //Trata Resposta vazia
    if (periodos.size() < 1)
    {
        cout << "Tabela vazia ou erro (periodos)" << endl;
        return -1;
    };
    
    //Fecha conexão com BD
    con.disconnect();
    
    //CABEÇALHO
    cout << "+--------------------------------------------------------------------------+\n"
         << "|                               Inscrições                                 |\n"
         << "+--------------------------------------------------------------------------+\n";
    
    //PERIODO
    int row = 0;
    //cout << periodos.size() << endl;
    
    for (int p = 0; p < (int)periodos.size(); p++)
    {
        cout << "|" << setw(32) << "" << periodos[p][0] << "º Período" << setw(32) << "" << "|\n";
        cout << "+--------+----------------------------------------------------+-------+----+\n";
        cout << "| Código | Nome                                               | Vagas | ID |\n";
        cout << "+--------+----------------------------------------------------+-------+----+\n";
        
        //DISCIPLINAS
        while (inscricoes[row][4] == periodos[p][0])
        {
            cout << "| " << inscricoes[row][0] << " | " << inscricoes[row][1] << setw(50 - inscricoes[row][1].size()) << "" << " |   " << inscricoes[row][2] << "   | " << inscricoes[row][3] << setw(2- inscricoes[row][3].size()) << "" << " | "  << endl;
            row+=1;
        }
        cout << "+--------+----------------------------------------------------+-------+----+\n";
    };

    return 0;
}

int Aluno::cancelarInscricoes(string turma_ids)
{
    //Retorna caso o vetor de turmas esteja vazio
    if (turma_ids.size() < 1)
    {
        cout << "Nenhuma turma foi selecionada" << endl;
        return 1;
    }
    
    //Abre conexão com o Banco de dados
    Postgres postgres;
    pqxx::connection con(postgres.getConnection_str().c_str());
    pqxx::work wrk(con);

    string turmasCondition = "";
    string word = "";
    for (auto x : turma_ids)
    {
        if (x == ' ')
        {
            turmasCondition += word + ", ";
            word = "";
        }
        else
            word += x;
    }
    turmasCondition += word;//ultima palavra
    
    pqxx::result cancelar = wrk.exec(
        "DELETE FROM inscricoes\
        WHERE aluno_id = " + id +
            "AND turma_id IN (" + turmasCondition + ");"
    );

    //Salva alterações no Banco de Dados
    wrk.commit();

    //Fecha Conexão com o Banco de dados
    con.disconnect();

    return 0;
}

