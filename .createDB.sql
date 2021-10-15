/*
DROP TABLE inscricoes;
DROP TABLE turmas;
DROP TABLE historico;
DROP TABLE alunos;
DROP TABLE grades;
DROP TABLE semestres;
DROP TABLE disciplinas;
DROP TABLE cursos;

SELECT * FROM cursos;
SELECT * FROM disciplinas;
SELECT * FROM semestres;
SELECT * FROM grades;
SELECT * FROM alunos;
SELECT * FROM historico;
SELECT * FROM turmas;
SELECT * FROM inscricoes;
*/

DROP TABLE inscricoes;
DROP TABLE turmas;
DROP TABLE historico;
DROP TABLE alunos;
DROP TABLE grades;
DROP TABLE semestres;
DROP TABLE disciplinas;
DROP TABLE cursos;

--CREATE TABLE
CREATE TABLE IF NOT EXISTS cursos (
    id VARCHAR(3) PRIMARY KEY UNIQUE NOT NULL,
    nome VARCHAR(50) UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS disciplinas (
    id VARCHAR(7) PRIMARY KEY UNIQUE NOT NULL,
    nome VARCHAR(50) NOT NULL
);

CREATE TABLE IF NOT EXISTS semestres (
    id VARCHAR(7) PRIMARY KEY UNIQUE NOT NULL,
    data_inicio DATE NOT NULL,
    data_fim DATE NOT NULL
);

CREATE TABLE IF NOT EXISTS grades (
     
    curso_id VARCHAR(7) NOT NULL,
    disciplina_id VARCHAR(6) NOT NULL,
    pre_requisitos VARCHAR[],
    periodo INT NOT NULL,
    
    PRIMARY KEY (curso_id, disciplina_id),
    
    FOREIGN KEY (curso_id)
        REFERENCES cursos (id),
    FOREIGN KEY (disciplina_id)
        REFERENCES disciplinas (id)
);

CREATE TABLE IF NOT EXISTS alunos (
    id SERIAL PRIMARY KEY UNIQUE NOT NULL,
    nome VARCHAR NOT NULL,
    curso_id VARCHAR(7) NOT NULL,
    
    FOREIGN KEY (curso_id)
        REFERENCES cursos (id)
);

CREATE TABLE IF NOT EXISTS turmas (
    id SERIAL PRIMARY KEY UNIQUE NOT NULL,
    descricao VARCHAR NOT NULL,
    disciplina_id VARCHAR(6) NOT NULL,
    semestre_id VARCHAR(7) NOT NULL,
    vagas INT NOT NULL,
    
    FOREIGN KEY (disciplina_id)
        REFERENCES disciplinas (id),
    FOREIGN KEY (semestre_id)
        REFERENCES semestres (id)
);

CREATE TABLE IF NOT EXISTS inscricoes (
    aluno_id SERIAL NOT NULL,
    turma_id SERIAL NOT NULL,
    timestamp TIMESTAMP NOT NULL,

    PRIMARY KEY (aluno_id, turma_id),
    UNIQUE (aluno_id, turma_id),

    FOREIGN KEY (aluno_id)
        REFERENCES alunos (id),
    FOREIGN KEY (turma_id)
        REFERENCES turmas (id)
);

CREATE TABLE IF NOT EXISTS historico (
    id SERIAL PRIMARY KEY UNIQUE NOT NULL,
    aluno_id SERIAL NOT NULL,
    disciplina_id VARCHAR(6) NOT NULL,

    FOREIGN KEY (aluno_id)
        REFERENCES alunos (id),
    FOREIGN KEY (disciplina_id)
        REFERENCES disciplinas (id)
);

--INSERT
--Cursos
INSERT INTO cursos
    (id, nome)
VALUES
    ('EEL', 'Engenharia Eletronica e de Computacao'),
    ('COS', 'Engenharia de Computacao e Informacao');

--Disciplinas

INSERT INTO disciplinas
    (id, nome)
VALUES
    --Engenharia Eletronica e de Computacao
    --1º Periodo
    ('EEL170', 'Computacao I'),
    ('FIS111', 'Fisica Experimental I'),
    ('FIT112', 'Fisica I'),
    ('IQG111', 'Quimica EE'),
    ('MAC118', 'Calculo I'),

    --2º Periodo
    ('EEH210', 'Eng. e Meio Ambiente'),
    ('EEL270', 'Computacao II'),
    ('EEL280', 'Circuitos Logicos'),
    ('FIS121', 'Fisica Experimental II'),
    ('FIT122', 'Fisica II'),
    ('MAC128', 'Calculo II'),
    ('MAE125', 'Algebra Linear II'),

    --3º Periodo
    ('EEG105', 'Sistemas Projetivos'),
    ('EEL350', 'Sistemas Lineares I'),
    ('EEL356', 'Metodos Mat em Eng Eletro'),
    ('FIM230', 'Fisica III'),
    ('FIN231', 'Fisica Experimental III'),
    ('MAC238', 'Calculo III'),

    --4º Periodo
    ('EEL315', 'Eletronica I'),
    ('EEL420', 'Circuitos Eletricos I'),
    ('EEL470', 'Algor e Estr de Dados'),
    ('EEL480', 'Sistemas Digitais'),
    ('FIM240', 'Fisica IV'),
    ('FIN241', 'Fisica Experimental IV'),

    --Engenharia de Computacao e Informacao
    --1º Periodo
    ('COS110', 'Algoritmos e Programacao'),
    ('COS111', 'Introd Eng Comput e Informacao'),

    --2º Periodo
    ('EEL670', 'Linguagens de Programacao'),

    --3º Periodo
    ('COS231', 'Estruturas de Dados'),
    ('EEL580', 'Arquitetura de Computadores'),
    ('EEL881', 'Teoria da Computacao'),

    --4º Periodo
    ('COE241', 'Estatistica e Mod. Probabilist.'),
    ('COS242', 'Teorias dos Grafos'),
    ('COS471', 'Computadores e Sociedade'),
    ('MAC248', 'Calculo IV');

--Semestres
INSERT INTO semestres
    (id, data_inicio, data_fim)
VALUES
    ('2020.1', '2020-01-01', '2020-06-30'),
    ('2020.2', '2020-07-01', '2020-12-31'),
    ('2021.1', '2020-01-01', '2020-06-30');

--Grades
INSERT INTO grades
    (curso_id, disciplina_id, pre_requisitos, periodo)
VALUES
    --Engenharia Eletronica e de Computacao
    --1º Periodo
    ('EEL', 'EEL170', NULL, 1),
    ('EEL', 'FIS111', NULL, 1),
    ('EEL', 'FIT112', NULL, 1),
    ('EEL', 'IQG111', NULL, 1),
    ('EEL', 'MAC118', NULL, 1),

	--2º Periodo
    ('EEL', 'EEH210', NULL, 2),
    ('EEL', 'EEL270', '{"EEL170"}', 2),
    ('EEL', 'EEL280', NULL, 2),
    ('EEL', 'FIS121', '{"FIS111", "FIT112"}', 2),
    ('EEL', 'FIT122', '{"FIT112", "MAC118"}', 2),
    ('EEL', 'MAC128', '{"MAC118"}', 2),
    ('EEL', 'MAE125', NULL, 2),

	--3º Periodo
    ('EEL', 'EEG105', NULL, 3),
    ('EEL', 'EEL350', '{"MAC128"}', 3),
    ('EEL', 'EEL356', '{"MAC128"}', 3),
    ('EEL', 'FIM230', '{"FIT112", "MAC128"}', 3),
    ('EEL', 'FIN231', '{"FIS121"}', 3),
    ('EEL', 'MAC238', '{"MAC128"}', 3),
    
	--4º Periodo
    ('EEL', 'EEL315', NULL, 4),
    ('EEL', 'EEL420', '{"EEL350"}', 4),
    ('EEL', 'EEL470', NULL, 4),
    ('EEL', 'EEL480', '{"EEL280"}', 4),
    ('EEL', 'FIM240', '{"FIM230", "MAC238"}', 4),
    ('EEL', 'FIN241', '{"FIM230", "FIN231"}', 4),

	--Engenharia de Computacao e Informacao
	--1º Periodo
	('COS', 'COS110', NULL, 1),
	('COS', 'COS111', NULL, 1),
    ('COS', 'EEL280', NULL, 1),
    ('COS', 'FIS111', NULL, 1),
    ('COS', 'FIT112', NULL, 1),
    ('COS', 'MAC118', NULL, 1),

	--2º Periodo
    ('COS', 'EEL480', '{"EEL280"}', 2),
	('COS', 'EEL670', NULL, 2),
    ('COS', 'FIS121', '{"FIS111", "FIT112"}', 2),
    ('COS', 'FIT122', '{"FIT112", "MAC118"}', 2),
    ('COS', 'MAC128', '{"MAC118"}', 2),
    ('COS', 'MAE125', NULL, 2),

	--3º Periodo
	('COS', 'COS231', '{"COS110", "MAE125"}', 3),
	('COS', 'EEL580', NULL, 3),
	('COS', 'EEL881', NULL, 3),
	('COS', 'FIM230', '{"FIT112", "MAC128"}', 3),
	('COS', 'FIN231', '{"FIS121"}', 3),
	('COS', 'MAC238', '{"MAC128"}', 3),

	--4º Periodo
	('COS', 'COE241', NULL, 4),
	('COS', 'COS242', '{"COS231"}', 4),
	('COS', 'COS471', '{"COS111"}', 4),
	('COS', 'FIM240', '{"FIM230"}', 4),
	('COS', 'FIN241', '{"FIN231"}', 4),
	('COS', 'IQG111', NULL, 4),
	('COS', 'MAC248', '{"MAC128"}', 4);


--Alunos
INSERT INTO alunos
    (/*id,*/ nome, curso_id)
VALUES
    --Eletronica
    --Em dia com a grade
    ('Alexandre', 'EEL'),--1
    ('Bruno', 'EEL'),--2
    ('Carlos', 'EEL'),--3
    ('Daniel', 'EEL'),--4

    --Grade baguncada
    ('Ernesto', 'EEL'),--5

    --Computacao
    --Em dia com a grade
    ('Aline', 'COS'),--6
    ('Bianca', 'COS'),--7
    ('Caroline', 'COS'),--8
    ('Daniela', 'COS'),--9

    --Grade baguncada
    ('Eloisa', 'COS');--10

--Turmas
INSERT INTO turmas
    (disciplina_id, descricao, semestre_id, vagas)
VALUES
    --Ciclo Basico
	--Matematica
    ('MAC118', 'Calculo I - A', '2021.1', 5),
	('MAC118', 'Calculo I - B', '2021.1', 5),
	
    ('MAC128', 'Calculo II - A', '2021.1', 5),
    ('MAC128', 'Calculo II - B', '2021.1', 5),
    
    ('MAC238', 'Calculo III - A', '2021.1', 5),
    ('MAC238', 'Calculo III - B', '2021.1', 5),
    
    ('MAE125', 'Algebra Linear II - A', '2021.1', 5),
    ('MAE125', 'Algebra Linear II - B', '2021.1', 5),

	('COE241', 'Estatistica e Mod. Probabilist. - A', '2021.1', 5),
	('COE241', 'Estatistica e Mod. Probabilist. - B', '2021.1', 5),

    --Fisica
    ('FIT112', 'Fisica I - A', '2021.1', 5),
    ('FIT112', 'Fisica I - B', '2021.1', 5),
	
    ('FIT122', 'Fisica II - A', '2021.1', 5),
    ('FIT122', 'Fisica II - B', '2021.1', 5),
    
    ('FIM230', 'Fisica III - A', '2021.1', 5),
    ('FIM230', 'Fisica III - B', '2021.1', 5),
    
    ('FIM240', 'Fisica IV - A', '2021.1', 5),
    ('FIM240', 'Fisica IV - B', '2021.1', 5),

    ('FIS111', 'Fisica Experimental I - A', '2021.1', 5),
    ('FIS111', 'Fisica Experimental I - B', '2021.1', 5),

    ('FIS121', 'Fisica Experimental II - A', '2021.1', 5),
    ('FIS121', 'Fisica Experimental II - B', '2021.1', 5),
    
    ('FIN231', 'Fisica Experimental III - A', '2021.1', 5),
    ('FIN231', 'Fisica Experimental III - B', '2021.1', 5),
    
    ('FIN241', 'Fisica Experimental IV - A', '2021.1', 5),
    ('FIN241', 'Fisica Experimental IV - B', '2021.1', 5),

    --Outros
	('IQG111', 'Quimica EE - A', '2021.1', 5),
	('IQG111', 'Quimica EE - B', '2021.1', 5),
    
    ('EEH210', 'Eng. e Meio Ambiente - A', '2021.1', 5),
    ('EEH210', 'Eng. e Meio Ambiente - B', '2021.1', 5),

    ('EEG105', 'Sistemas Projetivos - A', '2021.1', 5),
    ('EEG105', 'Sistemas Projetivos - B', '2021.1', 5),

    --Engenharia Eletronica e de Computacao
	--1º Periodo
	('EEL170', 'Computacao I', '2021.1', 5),
	
	--2º Periodo
    ('EEL270', 'Computacao II', '2021.1', 5),
    ('EEL280', 'Circuitos Logicos - Eletronica', '2021.1', 5),

	--3º Periodo
    ('EEL350', 'Sistemas Lineares I', '2021.1', 5),
    ('EEL356', 'Metodos Mat em Eng Eletro', '2021.1', 5),
    
	--4º Periodo
    ('EEL315', 'Eletronica I', '2021.1', 5),
    ('EEL420', 'Circuitos Eletricos I', '2021.1', 5),
    ('EEL470', 'Algor e Estr de Dados', '2021.1', 5),
    ('EEL480', 'Sistemas Digitais - Eletronica', '2021.1', 5),

	--Engenharia de Computacao e Informacao
	--1º Periodo
	('COS110', 'Algoritmos e Programacao', '2021.1', 5),
	('COS111', 'Introd Eng Comput e Informacao', '2021.1', 5),
    ('EEL280', 'Circuitos Logicos - Computacao', '2021.1', 5),

	--2º Periodo
    ('EEL480', 'Sistemas Digitais - Computacao', '2021.1', 5),
	('EEL670', 'Linguagens de Programacao - Computacao', '2021.1', 5),

	--3º Periodo
	('COS231', 'Estruturas de Dados', '2021.1', 5),
	('EEL580', 'Arquitetura de Computadores - Computacao', '2021.1', 5),
	('EEL881', 'Teoria da Computacao - Computacao', '2021.1', 5),

	--4º Periodo
	('COS242', 'Teorias dos Grafos - Computacao', '2021.1', 5),
	('COS471', 'Computadores e Sociedade', '2021.1', 5);

--Historico
INSERT INTO historico
    (/*id,*/ aluno_id, disciplina_id)
VALUES
    --Eletronica
    --1 (1º Periodo)

    --2 (2º Periodo)
    --1º Periodo
    (2, 'EEL170'),
    (2, 'FIS111'),
    (2, 'FIT112'),
    (2, 'IQG111'),
    (2, 'MAC118'),

    --3 (3º Periodo)
    --1º Periodo
    (3, 'EEL170'),
    (3, 'FIS111'),
    (3, 'FIT112'),
    (3, 'IQG111'),
    (3, 'MAC118'),

    --2º Periodo
    (3, 'EEH210'),
    (3, 'EEL270'),
    (3, 'EEL280'),
    (3, 'FIS121'),
    (3, 'FIT122'),
    (3, 'MAC128'),
    (3, 'MAE125'),

    --4 (4º Periodo)
    --1º Periodo
    (4, 'EEL170'),
    (4, 'FIS111'),
    (4, 'FIT112'),
    (4, 'IQG111'),
    (4, 'MAC118'),

    --2º Periodo
    (4, 'EEH210'),
    (4, 'EEL270'),
    (4, 'EEL280'),
    (4, 'FIS121'),
    (4, 'FIT122'),
    (4, 'MAC128'),
    (4, 'MAE125'),

    --3º Periodo
    (4, 'EEG105'),
    (4, 'EEL350'),
    (4, 'EEL356'),
    (4, 'FIM230'),
    (4, 'FIN231'),
    (4, 'MAC238'),

    --5 (4º Periodo mas possui buracos no historico bem como disciplinas adiantadas)
    --1º Periodo
    (5, 'EEL170'),
    (5, 'FIS111'),
    (5, 'FIT112'),
    (5, 'MAC118'),

    --2º Periodo
    (5, 'EEH210'),
    (5, 'EEL270'),
    (5, 'FIS121'),
    (5, 'MAC128'),
    (5, 'MAE125'),

    --3º Periodo
    (5, 'EEG105'),
    (5, 'EEL350'),
    (5, 'EEL356'),
    (5, 'FIN231'),
    (5, 'MAC238'),

    --4º Periodo
    (5, 'EEL315'),
    (5, 'EEL470'),

    --Computacao
    --6 (1º Periodo)

    --7 (2º Periodo)
    --1º Periodo
    (7, 'COS110'),
    (7, 'COS111'),
    (7, 'EEL280'),
    (7, 'FIS111'),
    (7, 'FIT112'),
    (7, 'MAC118'),

    --8 (3º Periodo)
    --1º Periodo
    (8, 'COS110'),
    (8, 'COS111'),
    (8, 'EEL280'),
    (8, 'FIS111'),
    (8, 'FIT112'),
    (8, 'MAC118'),

    --2º Periodo
    (8, 'EEL480'),
    (8, 'EEL670'),
    (8, 'FIS121'),
    (8, 'FIT122'),
    (8, 'MAC128'),
    (8, 'MAE125'),

    --9 (4º Periodo)
    --1º Periodo
    (9, 'COS110'),
    (9, 'COS111'),
    (9, 'EEL280'),
    (9, 'FIS111'),
    (9, 'FIT112'),
    (9, 'MAC118'),

    --2º Periodo
    (9, 'EEL480'),
    (9, 'EEL670'),
    (9, 'FIS121'),
    (9, 'FIT122'),
    (9, 'MAC128'),
    (9, 'MAE125'),

    --3º Periodo
    (9, 'COS231'),
    (9, 'EEL580'),
    (9, 'EEL881'),
    (9, 'FIM230'),
    (9, 'FIN231'),
    (9, 'MAC238'),

    --10 (4º Periodo mas possui buracos no historico bem como disciplinas adiantadas)
    --1º Periodo
    (10, 'COS110'),
    (10, 'COS111'),
    (10, 'EEL280'),
    (10, 'FIS111'),
    (10, 'FIT112'),
    (10, 'MAC118'),

    --2º Periodo
    (10, 'EEL480'),
    (10, 'FIS121'),
    (10, 'FIT122'),
    (10, 'MAC128'),
    (10, 'MAE125'),

    --3º Periodo
    (10, 'COS231'),
    (10, 'EEL580'),
    (10, 'EEL881'),
    (10, 'FIN231'),
    (10, 'MAC238'),

    --4º Periodo
    (10, 'COE241'),
    (10, 'IQG111');