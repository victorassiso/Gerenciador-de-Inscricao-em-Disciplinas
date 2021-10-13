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
    ('EEL', 'Engenharia Eletrônica e de Computação'),
    ('COS', 'Engenharia de Computação e Informação');

--Disciplinas

INSERT INTO disciplinas
    (id, nome)
VALUES
    --Engenharia Eletrônica e de Computação
    --1º Período
    ('EEL170', 'Computação I'),
    ('FIS111', 'Física Experimental I'),
    ('FIT112', 'Física I'),
    ('IQG111', 'Química EE'),
    ('MAC118', 'Cálculo I'),

    --2º Período
    ('EEH210', 'Eng. e Meio Ambiente'),
    ('EEL270', 'Computação II'),
    ('EEL280', 'Circuitos Lógicos'),
    ('FIS121', 'Física Experimental II'),
    ('FIT122', 'Física II'),
    ('MAC128', 'Cálculo II'),
    ('MAE125', 'Álgebra Linear II'),

    --3º Período
    ('EEG105', 'Sistemas Projetivos'),
    ('EEL350', 'Sistemas Lineares I'),
    ('EEL356', 'Métodos Mat em Eng Eletro'),
    ('FIM230', 'Física III'),
    ('FIN231', 'Física Experimental III'),
    ('MAC238', 'Cálculo III'),

    --4º Período
    ('EEL315', 'Eletrônica I'),
    ('EEL420', 'Circuitos Elétricos I'),
    ('EEL470', 'Algor e Estr de Dados'),
    ('EEL480', 'Sistemas Digitais'),
    ('FIM240', 'Física IV'),
    ('FIN241', 'Física Experimental IV'),

    --Engenharia de Computação e Informação
    --1º Período
    ('COS110', 'Algoritmos e Programação'),
    ('COS111', 'Introd Eng Comput e Informacao'),

    --2º Período
    ('EEL670', 'Linguagens de Programação'),

    --3º Período
    ('COS231', 'Estruturas de Dados'),
    ('EEL580', 'Arquitetura de Computadores'),
    ('EEL881', 'Teoria da Computação'),

    --4º Período
    ('COE241', 'Estatistica e Mod. Probabilist.'),
    ('COS242', 'Teorias dos Grafos'),
    ('COS471', 'Computadores e Sociedade'),
    ('MAC248', 'Cálculo IV');

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
    --Engenharia Eletrônica e de Computação
    --1º Período
    ('EEL', 'EEL170', NULL, 1),
    ('EEL', 'FIS111', NULL, 1),
    ('EEL', 'FIT112', NULL, 1),
    ('EEL', 'IQG111', NULL, 1),
    ('EEL', 'MAC118', NULL, 1),

	--2º Período
    ('EEL', 'EEH210', NULL, 2),
    ('EEL', 'EEL270', '{"EEL170"}', 2),
    ('EEL', 'EEL280', NULL, 2),
    ('EEL', 'FIS121', '{"FIS111", "FIT112"}', 2),
    ('EEL', 'FIT122', '{"FIT112", "MAC118"}', 2),
    ('EEL', 'MAC128', '{"MAC118"}', 2),
    ('EEL', 'MAE125', NULL, 2),

	--3º Período
    ('EEL', 'EEG105', NULL, 3),
    ('EEL', 'EEL350', '{"MAC128"}', 3),
    ('EEL', 'EEL356', '{"MAC128"}', 3),
    ('EEL', 'FIM230', '{"FIT112", "MAC128"}', 3),
    ('EEL', 'FIN231', '{"FIS121"}', 3),
    ('EEL', 'MAC238', '{"MAC128"}', 3),
    
	--4º Período
    ('EEL', 'EEL315', NULL, 4),
    ('EEL', 'EEL420', '{"EEL350"}', 4),
    ('EEL', 'EEL470', NULL, 4),
    ('EEL', 'EEL480', '{"EEL280"}', 4),
    ('EEL', 'FIM240', '{"FIM230", "MAC238"}', 4),
    ('EEL', 'FIN241', '{"FIM230", "FIN231"}', 4),

	--Engenharia de Computação e Informação
	--1º Período
	('COS', 'COS110', NULL, 1),
	('COS', 'COS111', NULL, 1),
    ('COS', 'EEL280', NULL, 1),
    ('COS', 'FIS111', NULL, 1),
    ('COS', 'FIT112', NULL, 1),
    ('COS', 'MAC118', NULL, 1),

	--2º Período
    ('COS', 'EEL480', '{"EEL280"}', 2),
	('COS', 'EEL670', NULL, 2),
    ('COS', 'FIS121', '{"FIS111", "FIT112"}', 2),
    ('COS', 'FIT122', '{"FIT112", "MAC118"}', 2),
    ('COS', 'MAC128', '{"MAC118"}', 2),
    ('COS', 'MAE125', NULL, 2),

	--3º Período
	('COS', 'COS231', '{"COS110", "MAE125"}', 3),
	('COS', 'EEL580', NULL, 3),
	('COS', 'EEL881', NULL, 3),
	('COS', 'FIM230', '{"FIT112", "MAC128"}', 3),
	('COS', 'FIN231', '{"FIS121"}', 3),
	('COS', 'MAC238', '{"MAC128"}', 3),

	--4º Período
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
    --Eletrônica
    --Em dia com a grade
    ('Alexandre', 'EEL'),--1
    ('Bruno', 'EEL'),--2
    ('Carlos', 'EEL'),--3
    ('Daniel', 'EEL'),--4

    --Grade bagunçada
    ('Ernesto', 'EEL'),--5

    --Computação
    --Em dia com a grade
    ('Aline', 'COS'),--6
    ('Bianca', 'COS'),--7
    ('Caroline', 'COS'),--8
    ('Daniela', 'COS'),--9

    --Grade bagunçada
    ('Eloisa', 'COS');--10

--Turmas
INSERT INTO turmas
    (disciplina_id, descricao, semestre_id, vagas)
VALUES
    --Ciclo Básico
	--Matemática
    ('MAC118', 'Cálculo I - A', '2021.1', 1),
	('MAC118', 'Cálculo I - B', '2021.1', 1),
	
    ('MAC128', 'Cálculo II - A', '2021.1', 1),
    ('MAC128', 'Cálculo II - B', '2021.1', 1),
    
    ('MAC238', 'Cálculo III - A', '2021.1', 1),
    ('MAC238', 'Cálculo III - B', '2021.1', 1),
    
    ('MAE125', 'Álgebra Linear II - A', '2021.1', 1),
    ('MAE125', 'Álgebra Linear II - B', '2021.1', 1),

	('COE241', 'Estatistica e Mod. Probabilist. - A', '2021.1', 1),
	('COE241', 'Estatistica e Mod. Probabilist. - B', '2021.1', 1),

    --Física
    ('FIT112', 'Física I - A', '2021.1', 1),
    ('FIT112', 'Física I - B', '2021.1', 1),
	
    ('FIT122', 'Física II - A', '2021.1', 1),
    ('FIT122', 'Física II - B', '2021.1', 1),
    
    ('FIM230', 'Física III - A', '2021.1', 1),
    ('FIM230', 'Física III - B', '2021.1', 1),
    
    ('FIM240', 'Física IV - A', '2021.1', 1),
    ('FIM240', 'Física IV - B', '2021.1', 1),

    ('FIS111', 'Física Experimental I - A', '2021.1', 1),
    ('FIS111', 'Física Experimental I - B', '2021.1', 1),

    ('FIS121', 'Física Experimental II - A', '2021.1', 1),
    ('FIS121', 'Física Experimental II - B', '2021.1', 1),
    
    ('FIN231', 'Física Experimental III - A', '2021.1', 1),
    ('FIN231', 'Física Experimental III - B', '2021.1', 1),
    
    ('FIN241', 'Física Experimental IV - A', '2021.1', 1),
    ('FIN241', 'Física Experimental IV - B', '2021.1', 1),

    --Outros
	('IQG111', 'Química EE - A', '2021.1', 1),
	('IQG111', 'Química EE - B', '2021.1', 1),
    
    ('EEH210', 'Eng. e Meio Ambiente - A', '2021.1', 1),
    ('EEH210', 'Eng. e Meio Ambiente - B', '2021.1', 1),

    ('EEG105', 'Sistemas Projetivos - A', '2021.1', 1),
    ('EEG105', 'Sistemas Projetivos - B', '2021.1', 1),

    --Engenharia Eletrônica e de Computação
	--1º Período
	('EEL170', 'Computação I', '2021.1', 1),
	
	--2º Período
    ('EEL270', 'Computação II', '2021.1', 1),
    ('EEL280', 'Circuitos Lógicos - Eletrônica', '2021.1', 1),

	--3º Período
    ('EEL350', 'Sistemas Lineares I', '2021.1', 1),
    ('EEL356', 'Métodos Mat em Eng Eletro', '2021.1', 1),
    
	--4º Período
    ('EEL315', 'Eletrônica I', '2021.1', 1),
    ('EEL420', 'Circuitos Elétricos I', '2021.1', 1),
    ('EEL470', 'Algor e Estr de Dados', '2021.1', 1),
    ('EEL480', 'Sistemas Digitais - Eletrônica', '2021.1', 1),

	--Engenharia de Computação e Informação
	--1º Período
	('COS110', 'Algoritmos e Programação', '2021.1', 1),
	('COS111', 'Introd Eng Comput e Informação', '2021.1', 1),
    ('EEL280', 'Circuitos Lógicos - Computação', '2021.1', 1),

	--2º Período
    ('EEL480', 'Sistemas Digitais - Computação', '2021.1', 1),
	('EEL670', 'Linguagens de Programação - Computação', '2021.1', 1),

	--3º Período
	('COS231', 'Estruturas de Dados', '2021.1', 1),
	('EEL580', 'Arquitetura de Computadores - Computação', '2021.1', 1),
	('EEL881', 'Teoria da Computação - Computação', '2021.1', 1),

	--4º Período
	('COS242', 'Teorias dos Grafos - Computação', '2021.1', 1),
	('COS471', 'Computadores e Sociedade', '2021.1', 1);

--Historico
INSERT INTO historico
    (/*id,*/ aluno_id, disciplina_id)
VALUES
    --Eletrônica
    --1 (1º Período)

    --2 (2º Período)
    --1º Período
    (2, 'EEL170'),
    (2, 'FIS111'),
    (2, 'FIT112'),
    (2, 'IQG111'),
    (2, 'MAC118'),

    --3 (3º Período)
    --1º Período
    (3, 'EEL170'),
    (3, 'FIS111'),
    (3, 'FIT112'),
    (3, 'IQG111'),
    (3, 'MAC118'),

    --2º Período
    (3, 'EEH210'),
    (3, 'EEL270'),
    (3, 'EEL280'),
    (3, 'FIS121'),
    (3, 'FIT122'),
    (3, 'MAC128'),
    (3, 'MAE125'),

    --4 (4º Período)
    --1º Período
    (4, 'EEL170'),
    (4, 'FIS111'),
    (4, 'FIT112'),
    (4, 'IQG111'),
    (4, 'MAC118'),

    --2º Período
    (4, 'EEH210'),
    (4, 'EEL270'),
    (4, 'EEL280'),
    (4, 'FIS121'),
    (4, 'FIT122'),
    (4, 'MAC128'),
    (4, 'MAE125'),

    --3º Período
    (4, 'EEG105'),
    (4, 'EEL350'),
    (4, 'EEL356'),
    (4, 'FIM230'),
    (4, 'FIN231'),
    (4, 'MAC238'),

    --5 (4º Período mas possui buracos no histórico bem como disciplinas adiantadas)
    --1º Período
    (5, 'EEL170'),
    (5, 'FIS111'),
    (5, 'FIT112'),
    (5, 'MAC118'),

    --2º Período
    (5, 'EEH210'),
    (5, 'EEL270'),
    (5, 'FIS121'),
    (5, 'MAC128'),
    (5, 'MAE125'),

    --3º Período
    (5, 'EEG105'),
    (5, 'EEL350'),
    (5, 'EEL356'),
    (5, 'FIN231'),
    (5, 'MAC238'),

    --4º Período
    (5, 'EEL315'),
    (5, 'EEL470'),

    --Computação
    --6 (1º Período)

    --7 (2º Período)
    --1º Período
    (7, 'COS110'),
    (7, 'COS111'),
    (7, 'EEL280'),
    (7, 'FIS111'),
    (7, 'FIT112'),
    (7, 'MAC118'),

    --8 (3º Período)
    --1º Período
    (8, 'COS110'),
    (8, 'COS111'),
    (8, 'EEL280'),
    (8, 'FIS111'),
    (8, 'FIT112'),
    (8, 'MAC118'),

    --2º Período
    (8, 'EEL480'),
    (8, 'EEL670'),
    (8, 'FIS121'),
    (8, 'FIT122'),
    (8, 'MAC128'),
    (8, 'MAE125'),

    --9 (4º Período)
    --1º Período
    (9, 'COS110'),
    (9, 'COS111'),
    (9, 'EEL280'),
    (9, 'FIS111'),
    (9, 'FIT112'),
    (9, 'MAC118'),

    --2º Período
    (9, 'EEL480'),
    (9, 'EEL670'),
    (9, 'FIS121'),
    (9, 'FIT122'),
    (9, 'MAC128'),
    (9, 'MAE125'),

    --3º Período
    (9, 'COS231'),
    (9, 'EEL580'),
    (9, 'EEL881'),
    (9, 'FIM230'),
    (9, 'FIN231'),
    (9, 'MAC238'),

    --10 (4º Período mas possui buracos no histórico bem como disciplinas adiantadas)
    --1º Período
    (10, 'COS110'),
    (10, 'COS111'),
    (10, 'EEL280'),
    (10, 'FIS111'),
    (10, 'FIT112'),
    (10, 'MAC118'),

    --2º Período
    (10, 'EEL480'),
    (10, 'FIS121'),
    (10, 'FIT122'),
    (10, 'MAC128'),
    (10, 'MAE125'),

    --3º Período
    (10, 'COS231'),
    (10, 'EEL580'),
    (10, 'EEL881'),
    (10, 'FIN231'),
    (10, 'MAC238'),

    --4º Período
    (10, 'COE241'),
    (10, 'IQG111');