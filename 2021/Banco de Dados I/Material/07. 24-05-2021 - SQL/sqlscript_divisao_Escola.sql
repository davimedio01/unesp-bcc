REM   Script: Session Aula BD I - BSI - 29-04-2020
REM   Exercícios sobre o operador de existência e o operador de divisão em SQL.

rem criando tabelas 


rem ************************************************************ 


create table instrutores 
   (cod_instrutor      number(3)    constraint instrutores_pk primary key, 
    nome_instrutor     varchar2(30) constraint instrutores_nome_nu not null, 
    tel_instrutor      varchar2(10), 
    admissao 	       date default sysdate);

create table cursos 
   (cod_curso     number(3)   constraint cursos_pk primary key, 
    nome_curso    varchar2(60) constraint cursos_nome_nnu not null unique, 
    carga_horaria number(3), 
    preco 	  number(7,2) default 0, 
    pre_requisito number(3));

create table alunos 
   (matricula       number(3)    constraint alunos_pk primary key, 
    nome_aluno	    varchar2(30) constraint alunos_nome_nu not null, 
    tel_aluno       varchar2(10), 
    endereco_aluno  varchar2(30), 
    cidade_aluno    varchar2(20) default 'Rio de Janeiro', 
    uf		    char(2)      default 'RJ' constraint alunos_uf_ch 
                            check (uf in ('SP', 'MG', 'RJ', 'ES')));

create table turmas 
   (cod_turma 	    	  number(3)   constraint turmas_pk primary key,  
    cod_curso                  	      constraint turmas_curso_fk references cursos(cod_curso), 
    cod_instrutor                     constraint turmas_instrutor_fk references instrutores(cod_instrutor), 
    preco_hora_instrutor  number(7,2) default 0, 
    sala	    	  number(2));

create table historico 
   (cod_turma              constraint historico_turma_fk references turmas (cod_turma), 
    matricula              constraint historico_aluno_fk references alunos (matricula), 
    nota	    number (7,2), 
    constraint historico_pk primary key (cod_turma, matricula));

commit 


rem inserindo dados: instrutores 


rem ************************************************************ 


insert into instrutores (cod_instrutor, nome_instrutor, tel_instrutor, admissao) 
values (1, 'Maria Carolina Sirio', '344-8788', to_date('1/2/1997','dd/mm/yyyy'));

insert into instrutores (cod_instrutor, nome_instrutor, tel_instrutor, admissao) 
values (2, 'Pedro Paulo Canopo', '274-9018', to_date('3/8/1996','dd/mm/yyyy'));

insert into instrutores (cod_instrutor, nome_instrutor, tel_instrutor, admissao) 
values (3, 'Augusto Lemos Vega', '722-1300', to_date('12/11/1998','dd/mm/yyyy'));

insert into instrutores (cod_instrutor, nome_instrutor, tel_instrutor, admissao) 
values (4, 'Monica Silveira Capela',  '212-7938', to_date('30/12/1997','dd/mm/yyyy'));

insert into instrutores (cod_instrutor, nome_instrutor, tel_instrutor, admissao) 
values (5, 'Almir Altair',  '220-6022', to_date('3/10/1996','dd/mm/yyyy'));

insert into instrutores (cod_instrutor, nome_instrutor, admissao) 
values (6, 'Leonardo Guimaraes Rigel', to_date('17/7/1997','dd/mm/yyyy'));

insert into instrutores (cod_instrutor, nome_instrutor,  admissao) 
values (7, 'Beatriz Bellatrix',  to_date('18/9/1998','dd/mm/yyyy'));

insert into instrutores (cod_instrutor, nome_instrutor,  admissao) 
values (8, 'Carlos Regulos',  to_date('1/3/1997','dd/mm/yyyy'));

insert into instrutores (cod_instrutor, nome_instrutor) 
values (9, 'Joana Aldebaran');

insert into instrutores (cod_instrutor, nome_instrutor) 
values (10, 'Matias Agena');

rem inserindo dados: cursos 


rem ************************************************************ 


insert into cursos (cod_curso, nome_curso, carga_horaria , preco) 
values (1, 'Introducao a Logica de Programacao', 32, 800);

insert into cursos (cod_curso, nome_curso, carga_horaria , preco) 
values (2, 'Fundamentos da Modelagem de Dados', 40, 950);

insert into cursos (cod_curso, nome_curso) 
values (3, 'Redes I');

insert into cursos (cod_curso, nome_curso) 
values (4, 'Introducao a Sistemas Operacionais');

insert into cursos (cod_curso, nome_curso) 
values (5, 'Analise Orientada por Objetos');

insert into cursos (cod_curso, nome_curso, carga_horaria , preco, pre_requisito) 
values (6, 'Delphi: Recursos Basicos', 24, 400, 1);

insert into cursos (cod_curso, nome_curso, carga_horaria , preco, pre_requisito) 
values (7, 'Delphi: Acesso a Bancos de Dados', 24, 400, 1);

insert into cursos (cod_curso, nome_curso, carga_horaria , preco, pre_requisito) 
values (8, 'Oracle: SQL*Plus e SQL', 32, 750, 2);

insert into cursos (cod_curso, nome_curso, carga_horaria , preco, pre_requisito) 
values (9, 'Oracle: PL/SQL', 24, 750, 8);

insert into cursos (cod_curso, nome_curso, pre_requisito) 
values (10, 'Redes II', 3);

rem inserindo dados: alunos 


rem ************************************************************ 


insert into alunos (matricula, nome_aluno, tel_aluno, endereco_aluno, cidade_aluno, uf) 
values (1, 'Zebedeu Silva Hydra', '3474-2318', 'R. Adolfo Lutz, 27/902', 'Sao Paulo', 'SP');

insert into alunos (matricula, nome_aluno, tel_aluno, endereco_aluno, cidade_aluno, uf) 
values (2, 'Yamandu Ramos Centaurus', '399-1490', 'R. Albert Einstein, 13/102', 'Campinas', 'SP');

insert into alunos (matricula, nome_aluno, tel_aluno, endereco_aluno, cidade_aluno, uf) 
values (3, 'Wellington Libra', '665-1138', 'Av. do Contorno, 5900', 'Linhares', 'ES');

insert into alunos (matricula, nome_aluno, tel_aluno, endereco_aluno, cidade_aluno, uf) 
values (4, 'Tadeu Perseu', '311-4671', 'Tv. Orquideas, 127 Casa 2', 'Barbacena', 'MG');

insert into alunos (matricula, nome_aluno, tel_aluno, endereco_aluno, cidade_aluno, uf) 
values (5, 'Luis Eridanus Rios', '211-6600', 'Av. Conceicao Silva, 222/1002', 'Uberaba', 'MG');

insert into alunos (matricula, nome_aluno, tel_aluno, endereco_aluno, cidade_aluno, uf) 
values (6, 'Marcelo Lyra', '221-1639', 'R. Joaquim Hernandez, 1/703', 'Vitoria', 'ES');

insert into alunos (matricula, nome_aluno, tel_aluno, endereco_aluno, cidade_aluno, uf) 
values (7, 'Carla Cassiopeia', '219-2266', 'Av. 15 de Abril, 3500/1902', 'Sorocaba', 'SP');

insert into alunos (matricula, nome_aluno, tel_aluno, endereco_aluno, cidade_aluno, uf) 
values (8, 'Daniel Auriga', '9786-5432', 'Av. Tiete, 1178/1204', 'Sao Paulo', 'SP');

insert into alunos (matricula, nome_aluno, tel_aluno, endereco_aluno, cidade_aluno, uf) 
values (9, 'Jose Neves Gemini', '812-5322', 'Av. dos Limoeiros, 44/102', 'Belo Horizonte', 'MG');

insert into alunos (matricula, nome_aluno, tel_aluno, endereco_aluno, cidade_aluno) 
values (10, 'Valeria Scorpio', '761-6432', 'R. Alta, 32/886', 'Campos');

insert into alunos (matricula, nome_aluno) 
values (11, 'Alvaro Lepus');

insert into alunos (matricula, nome_aluno) 
values (12, 'Ana Columba');

insert into alunos (matricula, nome_aluno) 
values (13, 'Luisa Delphinus');

insert into alunos (matricula, nome_aluno) 
values (14, 'Laercio Cetus');

insert into alunos (matricula, nome_aluno) 
values (15, 'Ricardo Vela');

insert into alunos (matricula, nome_aluno) 
values (16, 'Sandra Gomes Carina');

insert into alunos (matricula, nome_aluno) 
values (17, 'Francisco Crux');

insert into alunos (matricula, nome_aluno) 
values (18, 'Gerson Orion');

insert into alunos (matricula, nome_aluno) 
values (19, 'Humberto Musca');

insert into alunos (matricula, nome_aluno) 
values (20, 'Ronaldo Sagittarius');

insert into alunos (matricula, nome_aluno) 
values (21, 'Geraldo Capricornius');

insert into alunos (matricula, nome_aluno) 
values (22, 'Genaro Bootes');

insert into alunos (matricula, nome_aluno) 
values (23, 'Gago Ursa');

insert into alunos (matricula, nome_aluno) 
values (24, 'Nair Pegasus');

insert into alunos (matricula, nome_aluno) 
values (25, 'Ormindo Ophiucus');

insert into alunos (matricula, nome_aluno) 
values (26, 'Paulo Aquarius');

insert into alunos (matricula, nome_aluno) 
values (27, 'Bernardo Corona Borealis');

insert into alunos (matricula, nome_aluno) 
values (28, 'Evaristo Pisces');

insert into alunos (matricula, nome_aluno) 
values (29, 'Fernanda Taurus');

insert into alunos (matricula, nome_aluno) 
values (30, 'Lauro Virgo');

insert into alunos (matricula, nome_aluno) 
values (31, 'Epaminondas Corona Australis');

rem inserindo dados: turmas 


rem ************************************************************ 


insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (1, 1, 1, 20, 2);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (2, 1, 2, 20, 5);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (3, 2, 3, 25, 4);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (4, 3, 4, 20, 4);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (5, 3, 5, 20, 6);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (6, 1, 6, 20, 2);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (7, 7, 6, 25, 1);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (8, 5, 8, 40, 8);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (9, 2, 5, 25, 9);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (10, 4, 2, 15, 3);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (11, 8, 9, 35, 5);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (12, 6, 6, 20, 2);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (13, 5, 7, 45, 2);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (14, 3, 5, 15, 4);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (15, 1, 1, 15, 9);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (16, 4, 7, 10, 1);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (17, 2, 9, 28, 2);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (18, 8, 5, 33, 3);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (19, 6, 3, 14, 6);

insert into turmas (cod_turma, cod_curso, cod_instrutor, preco_hora_instrutor, sala)  
values (20, 2, 8, 18, 1);

rem inserindo dados: historico 


rem ************************************************************ 


insert into historico (cod_turma, matricula, nota) 
values (1, 1, 7.5);

insert into historico (cod_turma, matricula, nota) 
values (1, 2, 9.5);

insert into historico (cod_turma, matricula, nota) 
values (1, 3, 4.5);

insert into historico (cod_turma, matricula, nota) 
values (1, 4, 5.5);

insert into historico (cod_turma, matricula, nota) 
values (1, 5, 6.5);

insert into historico (cod_turma, matricula, nota) 
values (1, 6, 8.5);

insert into historico (cod_turma, matricula, nota) 
values (1, 7, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (1, 8, 7.5);

insert into historico (cod_turma, matricula, nota) 
values (1, 9, 5.0);

insert into historico (cod_turma, matricula, nota) 
values (1, 10, 4.0);

insert into historico (cod_turma, matricula, nota) 
values (2, 1, 8.5);

insert into historico (cod_turma, matricula, nota) 
values (2, 2, 5.5);

insert into historico (cod_turma, matricula, nota) 
values (2, 3, 6.5);

insert into historico (cod_turma, matricula, nota) 
values (2, 4, 4.5);

insert into historico (cod_turma, matricula, nota) 
values (2, 15, 9.5);

insert into historico (cod_turma, matricula, nota) 
values (2, 26, 8.5);

insert into historico (cod_turma, matricula, nota) 
values (2, 7, 4.0);

insert into historico (cod_turma, matricula, nota) 
values (2, 8, 3.5);

insert into historico (cod_turma, matricula, nota) 
values (2, 9, 6.0);

insert into historico (cod_turma, matricula, nota) 
values (2, 10, 5.0);

insert into historico (cod_turma, matricula, nota) 
values (3, 11, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (3, 12, 9.0);

insert into historico (cod_turma, matricula, nota) 
values (3, 13, 7.5);

insert into historico (cod_turma, matricula, nota) 
values (3, 14, 5.0);

insert into historico (cod_turma, matricula, nota) 
values (3, 25, 4.5);

insert into historico (cod_turma, matricula, nota) 
values (3, 16, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (3, 17, 6.0);

insert into historico (cod_turma, matricula, nota) 
values (3, 18, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (3, 19, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (3, 20, 4.5);

insert into historico (cod_turma, matricula, nota) 
values (4, 11, 5.5);

insert into historico (cod_turma, matricula, nota) 
values (4, 12, 5.0);

insert into historico (cod_turma, matricula, nota) 
values (4, 23, 7.5);

insert into historico (cod_turma, matricula, nota) 
values (4, 14, 4.0);

insert into historico (cod_turma, matricula, nota) 
values (4, 15, 9.5);

insert into historico (cod_turma, matricula, nota) 
values (4, 16, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (4, 17, 9.0);

insert into historico (cod_turma, matricula, nota) 
values (4, 18, 3.0);

insert into historico (cod_turma, matricula, nota) 
values (4, 19, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (4, 20, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (5, 11, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (5, 22, 9.0);

insert into historico (cod_turma, matricula, nota) 
values (5, 13, 7.5);

insert into historico (cod_turma, matricula, nota) 
values (5, 24, 5.0);

insert into historico (cod_turma, matricula, nota) 
values (5, 15, 4.5);

insert into historico (cod_turma, matricula, nota) 
values (5, 16, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (5, 17, 6.0);

insert into historico (cod_turma, matricula, nota) 
values (5, 18, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (5, 19, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (5, 20, 4.5);

insert into historico (cod_turma, matricula, nota) 
values (6, 21, 5.5);

insert into historico (cod_turma, matricula, nota) 
values (6, 12, 5.0);

insert into historico (cod_turma, matricula, nota) 
values (6, 13, 7.5);

insert into historico (cod_turma, matricula, nota) 
values (6, 14, 4.0);

insert into historico (cod_turma, matricula, nota) 
values (6, 25, 9.5);

insert into historico (cod_turma, matricula, nota) 
values (6, 16, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (6, 17, 9.0);

insert into historico (cod_turma, matricula, nota) 
values (6, 18, 3.0);

insert into historico (cod_turma, matricula, nota) 
values (6, 19, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (6, 20, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (7, 11, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (7, 12, 9.0);

insert into historico (cod_turma, matricula, nota) 
values (7, 13, 7.5);

insert into historico (cod_turma, matricula, nota) 
values (7, 14, 5.0);

insert into historico (cod_turma, matricula, nota) 
values (8, 15, 4.5);

insert into historico (cod_turma, matricula, nota) 
values (8, 26, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (8, 17, 6.0);

insert into historico (cod_turma, matricula, nota) 
values (8, 18, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (9, 19, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (9, 20, 4.5);

insert into historico (cod_turma, matricula, nota) 
values (9, 11, 5.5);

insert into historico (cod_turma, matricula, nota) 
values (9, 12, 5.0);

insert into historico (cod_turma, matricula, nota) 
values (10, 13, 7.5);

insert into historico (cod_turma, matricula, nota) 
values (10, 14, 4.0);

insert into historico (cod_turma, matricula, nota) 
values (10, 15, 9.5);

insert into historico (cod_turma, matricula, nota) 
values (10, 16, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (10, 17, 9.0);

insert into historico (cod_turma, matricula, nota) 
values (10, 18, 3.0);

insert into historico (cod_turma, matricula, nota) 
values (10, 29, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (10, 20, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (11, 19, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (11, 20, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (11, 9, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (11, 10, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (12, 11, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (12, 2, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (12, 7, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (12, 4, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (13, 9, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (13, 20, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (13, 11, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (14, 2, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (14, 7, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (14, 4, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (15, 29, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (15, 20, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (15, 9, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (15, 10, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (15, 11, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (16, 2, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (16, 27, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (16, 4, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (16, 9, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (17, 10, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (17, 11, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (18, 22, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (18, 27, 8.0);

insert into historico (cod_turma, matricula, nota) 
values (19, 24, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (19, 14, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (20, 22, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (20, 12, 9.0);

insert into historico (cod_turma, matricula, nota) 
values (20, 5, 7.0);

insert into historico (cod_turma, matricula, nota) 
values (20, 16, 9.0);

commit



REM ===============================================================================================


rem mostre os nomes dos cursos que foram ministrados por instrutores admitidos após o ano 2000


select nome_curso  
from cursos , turmas, instrutores 
where cursos.cod_curso = turmas.cod_curso  
      and turmas.cod_instrutor = instrutores.cod_instrutor 
      and  admissao > to_date('31/12/2000','dd/mm/yyyy') ;



Rem operação de divisão


rem Mostre os nomes dos cursos que foram ministrados por TODOS os instrutores admitidos após o ano 2000



select nome_curso  
from cursos , turmas t 
where cursos.cod_curso = t.cod_curso  
and not exists ( (select cod_instrutor 
                   from instrutores 
                   where admissao > to_date('31/12/2020','dd/mm/yyyy') 
                   ) 
                   minus 
                   (select cod_instrutor 
                   from instrutores 
                   where cod_instrutor = t.cod_instrutor 
                   ) ) 
    and exists ( select cod_instrutor 
                   from instrutores 
                   where admissao > to_date('31/12/2020','dd/mm/yyyy') ) ;

rem ==============================================================================================

Rem Para uma turma que tenha sido cursada por alunos de São Paulo, retorne o nome do curso;

select nome_curso 
from cursos c, turmas t , historico h , alunos a 
where c.cod_curso = t.cod_curso and t.cod_turma = h.cod_turma and h.matricula = a.matricula  
     and a.UF = 'SP' ;

Rem Para uma turma que tenha sido cursada por TODOS os alunos de São Paulo, retorne o nome do curso


select nome_curso 
from cursos 
where cod_curso in (select cod_curso 
                    from turmas t 
                    where not exists ( select matricula from alunos where UF = 'SP' 
                                       minus 
                                        select matricula 
                                        from historico  
                                        where cod_turma = t.cod_turma 
                                     ) 
                        and exists ( select matricula from alunos where UF = 'SP' )  
                    ) ;
