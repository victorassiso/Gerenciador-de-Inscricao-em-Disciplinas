--Turmas Disponíveis
WITH
gradeDoCurso AS
(
	SELECT disciplina_id, pre_requisitos[1] AS p1, pre_requisitos[2] AS p2, periodo
	FROM grades
	WHERE curso_id = 'EEL'
),
historicoDoAluno AS
(
	SELECT disciplina_id
	FROM historico
	WHERE aluno_id = 5
),
gradeMenosHistorico AS
(
	SELECT A.disciplina_id, A.p1, A.p2, A.periodo
	FROM gradeDoCurso A
	LEFT JOIN historicoDoAluno B
	ON A.disciplina_id = B.disciplina_id
	WHERE B.disciplina_id IS NULL
),
gradeMenosHistoricoMenosP1 AS
(
	SELECT DISTINCT C.disciplina_id, C.p1, C.p2, C.periodo
	FROM GradeMenosHistorico C
	LEFT JOIN GradeMenosHistorico D
	ON C.p1 = D.disciplina_id
	WHERE D.p1 IS NULL
),
gradeMenosHistoricoMenosP2 AS
(
	SELECT DISTINCT E.disciplina_id, E.p1, E.p2, E.periodo
	FROM GradeMenosHistoricoMenosP1 E
	LEFT JOIN GradeMenosHistoricoMenosP1 F
	ON E.p2 = F.disciplina_id
	WHERE F.p2 IS NULL
)

SELECT G.periodo, G.disciplina_id, H.descricao, H.vagas, H.id
FROM gradeMenosHistoricoMenosP2 G
INNER JOIN turmas H
ON G.disciplina_id = H.disciplina_id
ORDER BY G.periodo ASC, H.descricao

/*
pqxx::result turmas = wrk.exec(
        "--Turmas Disponíveis\
        WITH\
        gradeDoCurso AS\
        (\
            SELECT disciplina_id, pre_requisitos[1] AS p1, pre_requisitos[2] AS p2, periodo\
            FROM grades\
            WHERE curso_id = 'EEL'\
        ),\
        historicoDoAluno AS\
        (\
            SELECT disciplina_id\
            FROM historico\
            WHERE aluno_id = 5\
        ),\
        gradeMenosHistorico AS\
        (\
            SELECT A.disciplina_id, A.p1, A.p2, A.periodo\
            FROM gradeDoCurso A\
            LEFT JOIN historicoDoAluno B\
            ON A.disciplina_id = B.disciplina_id\
            WHERE B.disciplina_id IS NULL\
        ),\
        gradeMenosHistoricoMenosP1 AS\
        (\
            SELECT DISTINCT C.disciplina_id, C.p1, C.p2, C.periodo\
            FROM GradeMenosHistorico C\
            LEFT JOIN GradeMenosHistorico D\
            ON C.p1 = D.disciplina_id\
            WHERE D.p1 IS NULL\
        ),\
        gradeMenosHistoricoMenosP2 AS\
        (\
            SELECT DISTINCT E.disciplina_id, E.p1, E.p2, E.periodo\
            FROM GradeMenosHistoricoMenosP1 E\
            LEFT JOIN GradeMenosHistoricoMenosP1 F\
            ON E.p2 = F.disciplina_id\
            WHERE F.p2 IS NULL\
        )\
        SELECT G.periodo, G.disciplina_id, H.descricao, H.vagas, H.id\
        FROM gradeMenosHistoricoMenosP2 G\
        INNER JOIN turmas H\
        ON G.disciplina_id = H.disciplina_id\
        ORDER BY G.periodo ASC, H.descricao"
    );
    */