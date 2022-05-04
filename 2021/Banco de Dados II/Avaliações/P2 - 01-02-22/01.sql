REM Prova 2 - Banco de Dados II
REM Autor: Davi Neves
REM ----------------------------------------------------------------------------------------------------------------------
REM 1) Modelagem da Questão 1

REM Criação dos Objetos

REM Atributo: Email (1, n)
create or replace type EMAIL_NT as table of VARCHAR2(50);
/

REM Entidade Pai: Sócio
create or replace type SOCIO_TY as object (
    Matricula NUMBER(11), 
    Nome VARCHAR2(30),
    Endereco VARCHAR2(30),  
    DataNasc VARCHAR2(10)
) NOT FINAL ;
/

REM Entidade Filho-Pai: Piloto
create or replace type PILOTO_TY under SOCIO_TY (
    Breve VARCHAR2(50)
) NOT FINAL ;
/

REM Entidade Filho: Aluno
create or replace type ALUNO_TY under SOCIO_TY (
    Email EMAIL_NT,
    DataInicioCurso VARCHAR2(10)
) ;
/

REM Entidade Filho: Instrutor
create or replace type INSTRUTOR_TY under PILOTO_TY (
    Instituicao VARCHAR2(20),
    Curso VARCHAR2(20),
    Data VARCHAR2(10)
) ;
/

REM Relacionamento-Entidade: AulaVoo
create or replace type AULAVOO_TY as object(
    Parecer VARCHAR2(30),
    Data VARCHAR2(10),
    HoraSaida VARCHAR2(5),
    HoraChegada VARCHAR2(5),
    MatriculaAluno REF ALUNO_TY,
    MatriculaInstrutor REF INSTRUTOR_TY
) ;
/

REM Criação das Tabelas

REM A entidade Sócio, como possui especialização TOTAL e DISJUNTA, não deve ser criada!
REM Entidade Piloto

create table pilotos of PILOTO_TY
(primary key (Matricula));
/

REM Entidade Aluno
create table alunos of ALUNO_TY
(primary key (Matricula))
nested table Email store as EmailAlunos_ST;
/

REM Entidade Instrutor
create table instrutores of INSTRUTOR_TY
(primary key (Matricula));
/

REM Relacionamento AulaVoo
create table aulasvoo of AULAVOO_TY
(primary key (Data, HoraSaida))
/

REM Chaves Estrangeiras em AulaVoo
alter table aulasvoo    
add scope for(MatriculaAluno) is alunos;
/

alter table aulasvoo    
add scope for(MatriculaInstrutor) is instrutores;
/

REM 2) Inserção de Dois Dados em Cada Tabela
insert into pilotos values
(
    PILOTO_TY(
        1,
        'Nilceu Banana',
        'Rua dos Bananas, 90, 07892-482',
        '01/02/1920',
        '95769127492'
    )
);

insert into pilotos values
(
    PILOTO_TY(
        2,
        'Nilceu Sacana',
        'Rua dos Sacanas, 99, 08892-182',
        '01/02/1925',
        '58275927321'
    )
);

insert into alunos values
(
    ALUNO_TY(
        1,
        'Davi e Neves',
        'Rua dos Davis, 128, 02759-592',
        '18/01/2000',
        EMAIL_NT(
            'davi.neves@unesp.br',
            'davi.augusto@unesp.br'
        ),
        '01/02/2020'
    )
);

insert into alunos values
(
    ALUNO_TY(
        2,
        'Luis e Morelli',
        'Rua dos Gados, 12, 12759-592',
        '07/01/1980',
        EMAIL_NT(
            'luis.morelli@unesp.br',
            'luis.e.nilceu@unesp.br'
        ),
        '01/02/2019'
    )
);

insert into instrutores values
(
    INSTRUTOR_TY(
        1,
        'João Perea',
        'Rua dos Brutais, 90, 01929-429',
        '09/02/1930',
        '293192412052',
        'UNESP',
        'BCC',
        '20/03/1990'
    )
);

insert into instrutores values
(
    INSTRUTOR_TY(
        2,
        'João Martins',
        'Rua dos Pessoal, 99, 41929-429',
        '09/02/1935',
        '291252482092',
        'UNESP Bauru',
        'BSI',
        '20/08/1990'
    )
);

insert into aulasvoo values
(
    AULAVOO_TY(
        'Legal!',
        '02/05/2021',
        '20:00',
        '23:00',
        (select REF(a) from alunos a where a.Matricula = 1),
        (select REF(i) from instrutores i where i.Matricula = 1)
    )
);

insert into aulasvoo values
(
    AULAVOO_TY(
        'Não Legal',
        '08/08/2011',
        '09:00',
        '16:30',
        (select REF(a) from alunos a where a.Matricula = 2),
        (select REF(i) from instrutores i where i.Matricula = 2)
    )
);


REM 3) Para cada instrutor, retorne o seu nome, o seu brevê, e os nomes dos alunos para os quais ministrou aulas;



REM 4) Para cada instrutor, retorne o seu nome, a sua matrícula e a quantidade de aulas ministradas.


