rem Escreva uma consulta em SQL do SGBD Oracle 
rem que retorna, para cada turma com menos de 5 alunos, 
rem o código da turma, o nome do instrutor e o nome do curso.

rem Retornando cada turma com os alunos matriculados
create or replace view turma_matricula (cod_turma, matricula)
as
select his.cod_turma, his.matricula
from historico his, alunos alu
where his.matricula = alu.matricula
order by his.cod_turma asc;

rem Retornando cada código de turma com a quantidade de alunos
create or replace view turma_total_aluno(cod_turma, total_aluno)
as
select cod_turma, count(matricula) as total_matricula
from turma_matricula 
group by cod_turma
order by cod_turma asc;

rem Retornando, para turmas com menos de 5 alunos: código da turma, nome do instrutor e nome do curso
select tta.cod_turma, ins.nome_instrutor, cur.nome_curso
from turma_total_aluno tta, turmas tur, instrutores ins, cursos cur
where tta.total_aluno < 5 
and tta.cod_turma = tur.cod_turma
and tur.cod_instrutor = ins.cod_instrutor
and tur.cod_curso = cur.cod_curso
order by tta.cod_turma asc;
