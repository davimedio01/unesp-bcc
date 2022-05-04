REM   Script: Solução - Lista de Exercícios - Consultas sobre o BD OR EMPRESA
REM   Solução - Lista de Exercícios - Consultas sobre o BD OR EMPRESA

REM   Script: BD Objeto-Relacional Empresa (classes com métodos) 


REM   Modelagem de dados objeto-relacional da EMPRESA (inclui dependentes como componente de Empregados e um método idade na classe Empregado_TY para calcular a idade dos empregados. 


create or replace type LOCALIZACAO_NT as table of VARCHAR2(30);    
 
/

create or replace type NOME_TY as object    
(pnome  VARCHAR2(15),    
 mnome  VARCHAR2(15),    
 snome  VARCHAR2(15));   
/

create or replace type ENDERECO_TY as object    
(rua  VARCHAR2(20),    
 numero VARCHAR2(5),  
 bairro  VARCHAR2(15),   
 cidade  VARCHAR2(15),    
 estado  VARCHAR2(2),  
 Cep VARCHAR2(20)) ;   
/

 create or replace type EMPREGADO_TY;   
/

 create  or replace type EMPREGADO_NT as table of REF EMPREGADO_TY;  
/

create or replace type EMPREGADO_PROJETO_TY as object    
 (empregado   REF EMPREGADO_TY,    
  horas     number    
 );  
/

 create or replace type EMPREGADO_PROJETO_NT as table of EMPREGADO_PROJETO_TY;   
/

create or replace type GERENTE_TY as object    
 (gerente   REF EMPREGADO_TY,    
  dataInicio date);    
/

 create or replace type PROJETO_TY;   
/

 create or replace type PROJETO_NT as table of REF PROJETO_TY;   
/

create or replace type PROJETO_TRABALHO_TY as object    
 (projeto   REF PROJETO_TY,    
  horas     number    
 ); 
/

 create or replace type PROJETO_TRABALHO_NT as table of PROJETO_TRABALHO_TY;    
/

 create  or replace type DEPARTAMENTO_TY;   
/

 create or replace type DEPARTAMENTO_NT as table of REF DEPARTAMENTO_TY;   
/

create or replace type DEPGERENCIADO_TY as object    
 (departamento   REF DEPARTAMENTO_TY,    
  dataInicio date);  
/

create or replace type DEPENDENTE_TY as object    
 (nome  varchar2(30),    
  sexo  varchar2(1),    
  dataNasc  date,    
  relacao   varchar2(30));  
/

 create or replace type DEPENDENTE_NT as table of DEPENDENTE_TY;  
/

create or replace type EMPREGADO_TY as object    
(NSS            number,    
 nome           NOME_TY,    
 sexo           varchar2(1),    
 endereco       ENDERECO_TY,    
 dataNasc       date,    
 salario        number(7,2),    
 departamento   REF DEPARTAMENTO_TY,    
 depGerenciado  DEPGERENCIADO_TY,    
 supervisor     REF EMPREGADO_TY,    
 supervisionados EMPREGADO_NT,    
 dependentesEmp  DEPENDENTE_NT,    
 projetosEmp     PROJETO_TRABALHO_NT, 
 member function idade return integer);   
/

create or replace type body EMPREGADO_TY as  
	-- calcula a idade 
	member function idade  
		return integer 
	is 
	begin 
		return trunc(sysdate-dataNasc)/365; 
	end; 
end; 
/

create or replace type DEPARTAMENTO_TY as object    
(nome   varchar2(30),    
 numero number,    
 localizacao    LOCALIZACAO_NT,    
 empregadosDep  EMPREGADO_NT,    
 gerente        GERENTE_TY,    
 projetosDep    PROJETO_NT);   
/

create or replace type PROJETO_TY as object    
(nome   varchar(30),    
 numero number,    
 localizacao    varchar2(30),    
 empregadosProj EMPREGADO_PROJETO_NT,    
 departamento   REF DEPARTAMENTO_TY);  
/

create table Empregados of EMPREGADO_TY    
(NSS primary key)    
NESTED TABLE supervisionados STORE AS EMPREGADO_ST    
NESTED TABLE dependentesEmp STORE AS DEPENDENTE_ST    
NESTED TABLE projetosEmp STORE AS PROJETOS_TRABALHO_ST;

create table Departamentos of DEPARTAMENTO_TY    
(primary key(numero), unique(nome) )    
NESTED TABLE empregadosDep STORE AS EMPREGADOS_ST    
NESTED TABLE projetosDep STORE AS PROJETOS_ST    
NESTED TABLE localizacao STORE AS LOCALIZACAO_ST;

create table Projetos of PROJETO_TY    
(primary key(numero, nome))    
NESTED TABLE empregadosProj STORE AS EMPREGADO_PROJETO_ST;

alter table Empregados    
add scope for(departamento) is Departamentos;

alter table Empregados    
add scope for(supervisor) is Empregados;

alter table Projetos    
add scope for(departamento) is Departamentos;

commit 


insert into DEPARTAMENTOS(nome, numero, localizacao) values ('Research', 5, LOCALIZACAO_NT('Bellaire', 'Sugarland','Houston'));

insert into DEPARTAMENTOS(nome, numero, localizacao) values ('Administration', 4, LOCALIZACAO_NT('Stanford'));

insert into DEPARTAMENTOS(nome, numero, localizacao) values ('Headquarters', 1, LOCALIZACAO_NT('Houston'));

insert into PROJETOS(nome, numero, localizacao, departamento)     
            values ('ProductX', 1, 'Bellaire',     
            (select ref(d) from DEPARTAMENTOS d where d.numero = 5));

insert into PROJETOS(nome, numero, localizacao, departamento)     
            values ('ProductY', 2, 'Sugarland',     
            (select ref(d) from DEPARTAMENTOS d where d.numero = 5));

insert into PROJETOS(nome, numero, localizacao, departamento)     
            values ('ProductZ', 3, 'Houston',     
            (select ref(d) from DEPARTAMENTOS d where d.numero = 5));

insert into PROJETOS(nome, numero, localizacao, departamento)     
            values ('Computerization', 10, 'Stanford',     
            (select ref(d) from DEPARTAMENTOS d where d.numero = 4));

insert into PROJETOS(nome, numero, localizacao, departamento)     
            values ('Reorganization', 20, 'Houston',     
            (select ref(d) from DEPARTAMENTOS d where d.numero = 1));

insert into PROJETOS(nome, numero, localizacao, departamento)     
            values ('Newbenefits', 30, 'Stanford',     
            (select ref(d) from DEPARTAMENTOS d where d.numero = 4));

insert into EMPREGADOS(NSS, nome, sexo, endereco, datanasc, salario, departamento, projetosEmp, dependentesEmp)    
            values(123456789, NOME_TY('John', 'B', 'Smith'), 'M', ENDERECO_TY('Fondren','731',' ', 'Houston', 'TX',' '), TO_DATE('1955-01-09', 'yyyy-mm-dd'), 30000,     
            (select ref(d) from DEPARTAMENTOS d where d.numero = 5),    
            PROJETO_TRABALHO_NT(    
                PROJETO_TRABALHO_TY((select ref(p) from PROJETOS p where p.numero = 1), 32.5),    
                PROJETO_TRABALHO_TY((select ref(p) from PROJETOS p where p.numero = 2), 7.5)    
                ), 
            DEPENDENTE_NT(DEPENDENTE_TY('Michael', 'M', TO_DATE('1978-01-01', 'yyyy-mm-dd'),'Son' ), DEPENDENTE_TY('Alyce', 'F', TO_DATE('1978-12-31', 'yyyy-mm-dd'),'Daughter'), 
            DEPENDENTE_TY('Elizabeth', 'F', TO_DATE('1957-05-05', 'yyyy-mm-dd'),'Spouse' ))        
            );

insert into EMPREGADOS(NSS, nome, sexo, endereco, datanasc, salario, departamento, projetosEmp,dependentesEmp)    
            values(333445555, NOME_TY('Franklin', 'T', 'Wong'), 'M', ENDERECO_TY('Voss','638', ' ', 'Houston', 'TX', '') , TO_DATE('1945-12-08', 'yyyy-mm-dd'), 40000,     
            (select ref(d) from DEPARTAMENTOS d where d.numero = 5),    
            PROJETO_TRABALHO_NT(    
                PROJETO_TRABALHO_TY((select ref(p) from PROJETOS p where p.numero = 2), 10),    
                PROJETO_TRABALHO_TY((select ref(p) from PROJETOS p where p.numero = 3), 10),    
                PROJETO_TRABALHO_TY((select ref(p) from PROJETOS p where p.numero = 10), 10),    
                PROJETO_TRABALHO_TY((select ref(p) from PROJETOS p where p.numero = 20), 10)    
                ), 
            DEPENDENTE_NT(DEPENDENTE_TY( 'Alice', 'F', TO_DATE('1976-04-05', 'yyyy-mm-dd'),'Daughter'  ), DEPENDENTE_TY('Theodore', 'M', TO_DATE('1973-10-25', 'yyyy-mm-dd'),'Son' ), 
            DEPENDENTE_TY( 'Joy', 'F', TO_DATE('1948-05-03', 'yyyy-mm-dd'),'Spouse' ))     
            );

insert into EMPREGADOS(NSS, nome, sexo, endereco, datanasc, salario, departamento, projetosEmp)    
            values(999887777, NOME_TY('Alicia', 'J', 'Zelaya'), 'F', ENDERECO_TY( 'Castle', '3321',  ' ' , 'Spring', 'TX', ' ' ) , TO_DATE('1958-07-19', 'yyyy-mm-dd'), 25000,     
            (select ref(d) from DEPARTAMENTOS d where d.numero = 4),    
            PROJETO_TRABALHO_NT(    
                PROJETO_TRABALHO_TY((select ref(p) from PROJETOS p where p.numero = 30), 30),    
                PROJETO_TRABALHO_TY((select ref(p) from PROJETOS p where p.numero = 10), 10)    
                )    
            );

insert into EMPREGADOS(NSS, nome, sexo, endereco, datanasc, salario, departamento, projetosEmp,dependentesEmp)    
            values(987654321, NOME_TY('Jennifer', 'S', 'Wallace'), 'F', ENDERECO_TY( 'Berry', '291', ' ', 'Bellaire', 'TX', ' ') ,  TO_DATE('1931-06-20', 'yyyy-mm-dd'), 43000,     
            (select ref(d) from DEPARTAMENTOS d where d.numero = 4),    
            PROJETO_TRABALHO_NT(    
                PROJETO_TRABALHO_TY((select ref(p) from PROJETOS p where p.numero = 30), 20),    
                PROJETO_TRABALHO_TY((select ref(p) from PROJETOS p where p.numero = 20), 15)    
                ), 
             DEPENDENTE_NT(DEPENDENTE_TY ( 'Abner', 'M', TO_DATE('1932-02-29', 'yyyy-mm-dd'),'Spouse' ))    
            );

insert into EMPREGADOS(NSS, nome, sexo, endereco, datanasc, salario, departamento,  projetosEmp)    
            values(666884444, NOME_TY('Ramesh', 'K', 'Naravan'), 'M', ENDERECO_TY ('Fire Oak','975', ' ',  'Humble', 'TX',' '), TO_DATE('1952-09-15', 'yyyy-mm-dd'), 38000,     
            (select ref(d) from DEPARTAMENTOS d where d.numero = 5),    
            PROJETO_TRABALHO_NT(    
                PROJETO_TRABALHO_TY((select ref(p) from PROJETOS p where p.numero = 3), 40)    
                )    
            );

insert into EMPREGADOS(NSS, nome, sexo, endereco, datanasc, salario, departamento, projetosEmp)    
            values(453453453, NOME_TY('Joyce', 'A', 'English'), 'F', ENDERECO_TY('Rice','5631', ' ', 'Houston', 'TX',' ') ,  TO_DATE('1962-07-31', 'yyyy-mm-dd'), 25000,     
            (select ref(d) from DEPARTAMENTOS d where d.numero = 5),    
            PROJETO_TRABALHO_NT(    
                PROJETO_TRABALHO_TY((select ref(p) from PROJETOS p where p.numero = 1), 20),    
                PROJETO_TRABALHO_TY((select ref(p) from PROJETOS p where p.numero = 2), 20)    
                )    
            );

insert into EMPREGADOS(NSS, nome, sexo, endereco, datanasc, salario, departamento, projetosEmp)    
            values(987987987, NOME_TY('Ahmad', 'V', 'Jabba'), 'M', ENDERECO_TY('Dallas', '980', ' ' ,'Houston', 'TX',' '), TO_DATE('1959-03-29', 'yyyy-mm-dd'), 25000,     
            (select ref(d) from DEPARTAMENTOS d where d.numero = 4),    
            PROJETO_TRABALHO_NT(    
                PROJETO_TRABALHO_TY((select ref(p) from PROJETOS p where p.numero = 10), 35),    
                PROJETO_TRABALHO_TY((select ref(p) from PROJETOS p where p.numero = 30), 5)    
                )    
            );

insert into EMPREGADOS(NSS, nome, sexo, endereco, datanasc, salario, departamento, projetosEmp)    
            values(888665555, NOME_TY('James', 'E', 'Borg'), 'M', ENDERECO_TY('Stone','450', ' ',  'Houston', 'TX', ' ' ) , TO_DATE('1927-11-10', 'yyyy-mm-dd'), 55000,     
            (select ref(d) from DEPARTAMENTOS d where d.numero = 1),    
            PROJETO_TRABALHO_NT(    
                PROJETO_TRABALHO_TY((select ref(p) from PROJETOS p where p.numero = 20), NULL)    
                )    
            );

update DEPARTAMENTOS d set gerente = GERENTE_TY((select ref(e) from EMPREGADOS e where e.NSS = 333445555), TO_DATE('1978-05-22', 'yyyy-mm-dd')),    
                           empregadosdep  = ((select cast(collect(ref(e)) as EMPREGADO_NT) from EMPREGADOS e where e.departamento = ref(d)))    
                       where NUMERO = 5;

update DEPARTAMENTOS d set gerente = GERENTE_TY((select ref(e) from EMPREGADOS e where e.NSS = 987654321), TO_DATE('1985-01-01', 'yyyy-mm-dd')),    
                           empregadosdep  = ((select cast(collect(ref(e)) as EMPREGADO_NT) from EMPREGADOS e where e.departamento = ref(d)))    
                       where NUMERO = 4;

update DEPARTAMENTOS d set gerente = GERENTE_TY((select ref(e) from EMPREGADOS e where e.NSS = 888665555), TO_DATE('1971-06-19', 'yyyy-mm-dd')),    
                           empregadosdep  = ((select cast(collect(ref(e)) as EMPREGADO_NT) from EMPREGADOS e where e.departamento = ref(d)))    
                       where NUMERO = 1;

update PROJETOS p set empregadosproj =     
        ( (select cast( collect(EMPREGADO_PROJETO_TY(ref(e),     
                                (select horas from table(e.projetosemp) x where x.projeto = ref(p))))     
                        as EMPREGADO_PROJETO_NT)     
           from Empregados e     
           where ref(p) in (select projeto from table(e.projetosemp))));

select t.column_value.nome.pnome from table(select d.empregadosdep from departamentos d where d.numero = 5) t;

select e.nome.pnome from empregados e where e.NSS = 999887777;

select e.nome.pnome, e.supervisor.nome.pnome from empregados e;

select e.nome.pnome, e.nss, e.supervisor.nome.pnome from empregados e;

select e.nome.pnome, e.nss, e.supervisor.nss from empregados e;

commit 


update EMPREGADOS set supervisor = (select ref(e) from EMPREGADOS e where e.NSS = 333445555) where NSS = 123456789;

select e.nome.pnome, e.endereco.cidade, (e.supervisor.nome.pnome) from empregados e;

update EMPREGADOS set supervisor = (select ref(e) from EMPREGADOS e where e.NSS = 888665555) where NSS = 123456789;

select e.nome.pnome, e.endereco.cidade, (e.supervisor.nome.pnome) from empregados e;

update EMPREGADOS set supervisor = (select ref(e) from EMPREGADOS e where e.NSS = 987654321) where NSS = 123456789;

select e.nome.pnome, e.endereco.cidade, (e.supervisor.nome.pnome) from empregados e;

update EMPREGADOS set supervisor = (select ref(e) from EMPREGADOS e where e.NSS = 333445555) where NSS = 123456789;

update EMPREGADOS set supervisor = (select ref(e) from EMPREGADOS e where e.NSS = 888665555) where NSS = 333445555;

update EMPREGADOS set supervisor = (select ref(e) from EMPREGADOS e where e.NSS = 987654321) where NSS = 999887777;

update EMPREGADOS set supervisor = (select ref(e) from EMPREGADOS e where e.NSS = 888665555) where NSS = 987654321;

update EMPREGADOS set supervisor = (select ref(e) from EMPREGADOS e where e.NSS = 333445555) where NSS = 666884444;

update EMPREGADOS set supervisor = (select ref(e) from EMPREGADOS e where e.NSS = 333445555) where NSS = 453453453;

update EMPREGADOS set supervisor = (select ref(e) from EMPREGADOS e where e.NSS = 987654321) where NSS = 987987987;

select e.nome.pnome, e.endereco.cidade, (e.supervisor.nome.pnome) from empregados e;

update EMPREGADOS e1 set supervisionados = (select cast(collect(ref(e2)) as EMPREGADO_NT) from EMPREGADOS e2 where e2.supervisor = ref(e1));

select e.nome.pnome, e.endereco.cidade, (e.supervisor.nome.pnome) from empregados e;

commit 


select e.nome.pnome, e.departamento.nome from empregados e;

select e.nome.pnome, e.departamento.nome, p.column_value.nome from empregados e , TABLE(e.departamento.projetosdep) p;

update Departamentos d1 set projetosdep = (select cast(collect(ref(p2)) as PROJETO_NT) from PROJETOS p2 where p2.departamento = ref(d1));

select e.nome.pnome, e.departamento.nome, p.column_value.nome from empregados e , TABLE(e.departamento.projetosdep) p ;

select e.nome.pnome, e.dataNasc, e.idade() as idade from empregados e;

update Empregados e   
set depGerenciado = DepGerenciado_TY((select ref(d) from Departamentos d where ref(e) = d.gerente.gerente), 
                                     (select d.gerente.DataInicio from Departamentos d where ref(e) = d.gerente.gerente)) ;

select e.nome.pnome, e.depGerenciado.departamento.nome, e.depGerenciado.dataInicio 
from empregados e;

select d.gerente.gerente.nome.pnome, d.nome, d.gerente.dataInicio from departamentos d;

update empregados e 
set dependentesEmp = Dependente_NT() 
where e.nome.pnome = 'Alicia';

insert into TABLE(select e.dependentesEmp  
from empregados e  where e.nome.pnome = 'Alicia' ) values ('Alicia', 'F', TO_DATE('1978-12-31', 'yyyy-mm-dd'),'Daughter' ) ;

select e.nome.pnome, e.nome.mnome, e.nome.snome  
from empregados e  
where e.nome.pnome in (select d.nome from TABLE(e.dependentesEmp) d);

select d.nome, d.gerente.gerente.nome.pnome, d.gerente.dataInicio from departamentos d;

select d.nome, NVL(CARDINALITY(d.projetosDep),0) as NumProjetos, NVL(CARDINALITY(d.empregadosDep),0) as NumEmpregados from departamentos d;

select p.nome as NomeProjeto, e.empregado.nome.pnome as NomeEmpregado, e.horas as NHoras from projetos p, TABLE(p.empregadosProj) e;

Rem 1.	Faça uma lista de todos os números de projetos para os projetos que envolvem empregados com sobrenome 'Smith', ou como trabalhador, ou como gerente de um departamento que controla o projeto. Obs: não utilize aninhamento de consultas.  


select p.numero   
from PROJETOS p, TABLE(p.empregadosproj) e   
where e.empregado.nome.snome = 'Smith' or   
             p.departamento.gerente.gerente.nome.snome = 'Smith';

rem 2.	Idem ao exercício 1, porém utilizando aninhamento de consultas.  


select p.numero   
from PROJETOS p   
where exists(select * from TABLE(p.empregadosproj) e   
                        where e.empregado.nome.snome = 'Smith')  or   
                        p.departamento.gerente.gerente.nome.snome = 'Smith';

rem 3.	Recupere o nome de cada empregado da empresa que tem um dependente com o mesmo nome do empregado. Obs: não utilize aninhamento de consultas.  


select e.nome.pnome, e.nome.mnome,  e.nome.snome   
from EMPREGADOS e , TABLE(e.dependentesemp) d  
where d.nome = e.nome.pnome;

rem 4.	Idem ao exercício 3, porém utilizando aninhamento de consultas com o operador in.  


select e.nome.pnome, e.nome.mnome, e.nome.snome  
from EMPREGADOS e  
where e.nome.pnome in (select d.nome   
                       from TABLE(e.dependentesemp) d );

rem 5.	Idem ao exercício 3, porém utilizando aninhamento de consultas com o operador exists  


select e.nome.pnome, e.nome.mnome, e.nome.snome  
from EMPREGADOS e  
where exists (select *   
                         from TABLE(e.dependentesemp) d   
                         where d.nome = e.nome.pnome);

rem 6.	Recupere o nome de cada empregado que trabalha em todos os projetos controlados pelo departamento número 5.  


select   
    e.nome.pnome, e.nome.mnome, e.nome.snome as  
from Empregados e  
where not exists (( select p.numero  
                                  from Projetos p  
                                  where p.departamento.numero = 5  
                                ) minus   
                             (  
                               Select pe.projeto.numero  
                               from table(e.projetosEmp) pe  
                            )  )  
and exists ( select p.numero  
                     from Projetos p  
                     where p.departamento.numero = 5  
           );

Rem 7.	Recupere os nomes dos empregados que não têm dependentes. Obs: não utilize aninhamento de consultas.  


select e.nome.pnome, e.nome.mnome, e.nome.snome  
from EMPREGADOS e  
where e.dependentesemp is null;

rem 8.	Idem ao exercício 7, porém utilizando aninhamento de consultas e o operador not exists.  


select e.nome.pnome, e.nome.mnome, e.nome.snome  
from EMPREGADOS e  
where not exists (select d.* from TABLE(e.DEPENDENTESEMP) d);

rem 9.	Liste os nomes dos gerentes que possuem pelo menos um dependente. Obs: não utilize aninhamento de consultas.  


select e.nome.pnome, e.nome.mnome, e.nome.snome  
from EMPREGADOS e  
where e.dependentesemp is not null and e.depgerenciado is not null;

rem 10.	Idem ao exercício 9, porém utilizando aninhamento de consultas e o operador  exists.  


select e.nome.pnome, e.nome.mnome, e.nome.snome  
from EMPREGADOS e  
where e.depgerenciado is not null and  
            exists (select * from TABLE(e.dependentesemp) )   ;

rem 11.	Liste os números do seguro social (SSN) de todos os empregados que trabalham nos projetos 1,2 ou 3.Obs: utilize o operador in, com conjuntos enumerados.  


select distinct e.empregado.nss   
from PROJETOS p, TABLE(p.empregadosproj) e   
where p.numero in (1,2,3) ;

rem 12.	Liste os nomes dos empregados que não tem supervisores. Utilize o operador is null. 


select e.nome.pnome, e.nome.mnome, e.nome.snome  
from EMPREGADOS e  
where e.SUPERVISOR is null;

rem 13.	Encontre a soma dos salários de todos os empregados da empresa, bem como o valor máximo, mínimo e médio pagos pela empresa a seus empregados  


select sum(salario), max(salario), min(salario), avg(salario) from Empregados;

rem 14.	Encontre a soma dos salários de todos os empregados que trabalham no departamento 'Research'.  


select SUM(e.salario)  
from EMPREGADOS e  
where e.departamento.nome = 'Research';

rem 15.	Encontre o número de empregados do departamento 'Research'.  


select count(e.column_value.nss) NumeroEmpregados  
from DEPARTAMENTOS d, TABLE(d.empregadosdep) e   
where d.nome = 'Research';

rem 16.	Liste os nomes dos empregados que têm mais do que três dependentes.  


select e.nome.pnome, e.nome.mnome, e.nome.snome  
from EMPREGADOS e  
where NVL(CARDINALITY(e.dependentesEmp), 0) > 3;

rem 17.	Conte o número de salários distintos pagos pela empresa aos seus funcionários.  


select count(distinct salario)  
from EMPREGADOS;

rem 18.	Para cada departamento, liste o seu número, o seu número de empregados e o salário médio dos seus empregados.  


select d.numero, COUNT(e.column_value.NSS) NumeroEmpregados, AVG(e.column_value.salario) SalarioMedio  
from DEPARTAMENTOS d, TABLE(d.empregadosdep) e  
group by d.numero;

rem 19.	Para cada projeto, liste o seu número, o seu nome e o número de empregados que trabalham nele.  


select p.numero, p.nome, NVL(CARDINALITY(p.empregadosproj), 0) as QtdeEmpregados  
from PROJETOS p;

rem 20.	Para cara projeto no qual mais do que um empregado trabalha, recupere o seu número, o seu nome e o número de empregados que trabalham nele.  


select p.numero, p.nome, NVL(CARDINALITY(p.empregadosproj), 0) as QtdeEmpregados  
from PROJETOS p  
where NVL(CARDINALITY(p.empregadosproj), 0) > 1;

rem 21.	Para cada projeto, liste o seu número, o seu nome, e o número de empregados do departamento 5 que trabalham no projeto.  


select p.numero, p.nome, count(e.empregado) QtdeEmpregados  
from PROJETOS p, TABLE(p.empregadosProj) e  
where e.empregado.departamento.numero = 5  
group by p.numero, p.nome;

rem 22.	Para cada departamento tendo mais do que 5 empregados, liste o seu número, e o número de empregados que recebem mais do que $40000.  


select p.numero, p.nome, COUNT(e.empregado) QtdeEmpregados  
from PROJETOS p, TABLE(p.empregadosproj) e  
where NVL(CARDINALITY(p.empregadosproj), 0) > 5 and e.empregado.salario > 4000  
group by p.numero, p.nome;

rem 23.	Liste todos os empregados cujo endereço fica em São Paulo.  


select e.nome.pnome, e.nome.mnome, e.nome.snome from EMPREGADOS e   
where e.endereco.cidade = 'São Paulo';

rem 24.	Mostre os salários resultantes após serem concedidos 10% de aumento para os empregados que trabalham no 'ProductX'.  


select e.salario * 1.1 NovosSalarios  
from EMPREGADOS e, TABLE(e.projetosemp) p  
where p.projeto.nome = 'ProductX';

Rem 25.	Recupere os nomes dos empregados e os projetos nos quais eles trabalham, ordenados pelos nomes dos departamentos e, dentro de cada departamento, ordenados alfabeticamente pelos sobrenomes.  


select e.nome.pnome, p.projeto.nome  
from EMPREGADOS e, TABLE(e.projetosemp) p  
order by e.nome.pnome, p.projeto.nome;

