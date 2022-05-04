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

commit ;


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

commit ;


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

commit ;


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

