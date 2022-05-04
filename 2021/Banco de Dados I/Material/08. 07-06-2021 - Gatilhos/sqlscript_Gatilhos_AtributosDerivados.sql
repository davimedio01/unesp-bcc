REM Bando de Dados ESCOLA


Rem Gatilho para controlar o atributo derivado Num_Turmas na tabela Alunos

select matricula , count(*) num_turmas  
from historico 
group by matricula 
order by matricula;

select * from alunos 
;

alter table alunos add num_turmas number(3) default 0 
;

select * from alunos 
;

select matricula , count(*) num_turmas  
from historico 
group by matricula 
order by matricula;

select * from alunos 
;

update alunos a 
set a.num_turmas = (select count(*) from historico h where h.matricula = a.matricula);

select * from alunos 
;

select matricula , count(*) num_turmas  
from historico 
group by matricula 
order by matricula;

select matricula,num_turmas from alunos 
;

select * from historico where matricula = 4;

insert into historico values(3,4,10.0);

select matricula , count(*) num_turmas  
from historico 
group by matricula 
order by matricula;

select matricula,num_turmas from alunos 
;

delete from historico where matricula = 4 and cod_turma = 3;

select matricula , count(*) num_turmas  
from historico 
group by matricula 
order by matricula;

select matricula,num_turmas from alunos 
;



create or replace trigger Controla_Num_Turmas_Alunos   
after insert or delete or update of matricula on historico   
for each row   
begin   
if inserting then   
update alunos   
set num_turmas = num_turmas + 1    
where matricula = :new.matricula;   
elsif deleting then   
update alunos   
set num_turmas = num_turmas - 1    
where matricula = :old.matricula;   
else   
update alunos   
set num_turmas = num_turmas + 1    
where matricula = :new.matricula;   
update alunos   
set num_turmas = num_turmas - 1    
where matricula = :old.matricula;   
end if;   
end; 
/

select * from historico 
where matricula = 4;

insert into historico values(3,4,10,0);

insert into historico values(3,4,10.0);

select * from alunos where matricula = 4;

select * from historico 
where matricula = 4;

delete from historico where matricula = 4;

select * from alunos where matricula = 4 
;

select * from historico 
where matricula = 4;

select * from alunos where matricula = 4 
;

select * from historico 
where matricula = 1;

update historico  
set nota = 10 
where matricula = 1;

select * from historico 
where matricula = 1;

select * from alunos where matricula = 1 
;

select * from historico 
where matricula = 1;

update historico  
set cod_turma = cod_turma + 1 
where matricula = 1;

select * from historico 
where matricula = 1;

select * from alunos where matricula = 1 
;

update historico  
set matricula = 1 
where matricula = 4;

select * from historico 
where matricula in (4,6);

select * from historico 
where matricula in (1,2);

select * from historico 
where matricula in (1,2) 
order by matricula;

select * from historico 
where matricula in (1,12) 
order by matricula;

update historico  
set matricula = 1 
where matricula = 12;

select * from historico 
where matricula in (1,12) 
order by matricula;

update historico  
set matricula = 1 
where matricula = 12 and nota = 5;

select * from alunos where matricula in (1,12);

select * from historico 
where matricula in (2,12) 
order by matricula;

select * from alunos where matricula in (2,12) 
;

update historico  
set matricula = 12 
where matricula = 2 and cod_turma = 12;

select * from alunos where matricula in (2,12) 
;



Rem Gatilho para controlar o atributo derivado Num_Turmas na Tabela Cursos

select * from cursos;

alter table cursos add num_turmas number(3) default 0;

select * from cursos 
;

select cod_curso , count(*) num_turmas 
from turmas 
group by cod_curso 
order by cod_curso;

select * 
from turmas 
where cod_curso = 1;

select cod_curso , count(*) num_turmas 
from turmas 
group by cod_curso 
order by cod_curso;

select * 
from turmas 
where cod_curso = 3;

select * from cursos 
;

update cursos c 
set c.num_turmas = ( select count(*) from turmas t where t.cod_curso = c.cod_curso);

select * from cursos 
;

create or replace trigger Controla_Num_Turmas_Cursos   
after insert or delete or update of cod_curso on turmas   
for each row   
begin   
if inserting then   
update cursos   
set num_turmas = num_turmas + 1    
where cod_curso = :new.cod_curso;   
elsif deleting then   
update cursos   
set num_turmas = num_turmas - 1    
where cod_curso = :old.cod_curso;   
else   
update cursos   
set num_turmas = num_turmas + 1    
where cod_curso = :new.cod_curso;    
update cursos   
set num_turmas = num_turmas - 1    
where cod_curso = :old.cod_curso;    
end if;   
end; 
/

select * from cursos where cod_curso = 1;

select * from turmas where cod_curso = 1;

select * from cursos where cod_curso in (1,2) 
;

select * from turmas where cod_curso in (1,2);

select * from turmas where cod_curso in (1,2) order by cod_curso;

update turmas 
set cod_curso = 2 
where cod_curso = 1;

select * from cursos where cod_curso in (1,2) 
;

select * from turmas where cod_curso in (1,2) order by cod_curso 
;

delete from turmas 
where cod_curso = 2;

update turmas 
set cod_curso = 2 
where cod_curso = 1;

select * from turmas where cod_curso in (1,2) order by cod_curso 
;

delete  
from historico 
where cod_turma in (1,2,3,20,9,15,17,6);

delete from turmas 
where cod_curso = 2;

select * from cursos where cod_curso in (1,2) 
;

select * from turmas where cod_curso in (1,2) order by cod_curso 
;

select * from turmas  order by cod_curso 
;

insert into turmas values (1,1,1,30,1);

select * from cursos where cod_curso in (1,2) 
;

