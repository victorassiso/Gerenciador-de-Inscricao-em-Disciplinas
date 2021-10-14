#include "requisicao.h"

Requerimento::Requerimento(string aluno_id): Aluno(aluno_id)
{
    cout << "-Log: Requerimento criado!" << endl;
}

Requerimento::~Requerimento()
{
    cout << "-Log: Requerimento destruído!" << endl;
}

string Requerimento::selectNomeDoCurso(pqxx::work &wrk)
{
    pqxx::result nomeDoCurso = wrk.exec(
        "SELECT nome\
        FROM cursos\
        WHERE id = '" + getCursoId() + "'"
    );
    
    return to_string(nomeDoCurso[0][0]);
}

pqxx::result Requerimento::selectGrade(pqxx::work &wrk)
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

pqxx::result Requerimento::selectPeriodosDoCurso(pqxx::work &wrk)
{
    pqxx::result periodos = wrk.exec(
        "SELECT DISTINCT periodo\
        FROM grades\
        ORDER BY periodo ASC"
    );

    return periodos;
}

pqxx::result Requerimento::selectTurmasDisponiveis(pqxx::work &wrk)
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

void Requerimento::insertInscricoes(pqxx::work &wrk, string values)
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

pqxx::result Requerimento::selectInscricoes(pqxx::work &wrk)
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

pqxx::result Requerimento::selectPeriodosDasInscricoes(pqxx::work &wrk)
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
