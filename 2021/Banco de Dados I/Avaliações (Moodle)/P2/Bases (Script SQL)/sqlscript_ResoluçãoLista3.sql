rem ************ Nome: Davi Augusto Neves Leite ****************
rem ************ RA: 191027383                  ****************

rem ******** SCRIPT PARA CRIAÇÃO E POPULAÇÃO DOS DADOS *********
rem https://livesql.oracle.com/apex/livesql/s/lxerzwyb9a21bbjk0i7eck6to

rem **************** SGBD: Oracle Live SQL *********************

rem ************************************************************ 
rem *************** Resolução da Lista 3: SQL ******************
rem ************************************************************ 

rem 1)
select distinct tur.cod_turma, cur.nome_curso, ins.nome_instrutor, tur.sala
from turmas tur, cursos cur, instrutores ins
where tur.cod_curso = cur.cod_curso and tur.cod_instrutor = ins.cod_instrutor
order by cod_turma asc;

rem ************************************************************ 
rem 2)
select distinct nome_aluno, endereco_aluno, cidade_aluno
from alunos
order by nome_aluno asc;

rem ************************************************************ 
rem 3)
select distinct nome_curso, carga_horaria, preco
from cursos
order by nome_curso asc;

rem ************************************************************ 
rem 4)
select distinct alu.nome_aluno, cur.nome_curso
from historico his, alunos alu, cursos cur
where his.matricula = alu.matricula
order by alu.nome_aluno asc;

rem ************************************************************ 
rem 5)
select distinct alu.nome_aluno
from alunos alu, historico his, cursos cur, turmas tur
where alu.matricula = his.matricula and his.cod_turma = tur.cod_turma and tur.cod_curso = cur.cod_curso and cur.nome_curso != 'Redes I'
order by alu.nome_aluno asc;

rem ************************************************************ 
rem 6)
select distinct alu.nome_aluno, ins.nome_instrutor
from alunos alu, historico his, turmas tur, instrutores ins
where alu.matricula = his.matricula and his.cod_turma = tur.cod_turma and tur.cod_instrutor = ins.cod_instrutor
order by alu.nome_aluno asc;

rem ************************************************************ 
rem 7)

rem Todas as médias, ordenadas da maior para menor
select alunos_media.nome_aluno, avg(alunos_media.nota) as media
from (select distinct alu.nome_aluno, his.nota
      from alunos alu, historico his
      where alu.matricula = his.matricula
      order by alu.nome_aluno asc) alunos_media
group by (alunos_media.nome_aluno)
order by media desc;

rem O valor da maior média da escola
select max(media) as maior_media
from (select alunos_media.nome_aluno, avg(alunos_media.nota) as media
      from (select distinct alu.nome_aluno, his.nota
            from alunos alu, historico his
            where alu.matricula = his.matricula
            order by alu.nome_aluno asc) alunos_media
      group by (alunos_media.nome_aluno)
      order by media desc);

rem As maiores médias da escola: retorna só o nome
select alunos_medias_decres.nome_aluno
from (select alunos_media.nome_aluno, avg(alunos_media.nota) as media
      from (select distinct alu.nome_aluno, his.nota
            from alunos alu, historico his
            where alu.matricula = his.matricula
            order by alu.nome_aluno asc) alunos_media
      group by (alunos_media.nome_aluno)
      order by media desc) alunos_medias_decres,
      (select max(media) as maior_media
       from (select alunos_media.nome_aluno, avg(alunos_media.nota) as media
             from (select distinct alu.nome_aluno, his.nota
                   from alunos alu, historico his
                   where alu.matricula = his.matricula
                   order by alu.nome_aluno asc) alunos_media
        group by (alunos_media.nome_aluno)
        order by media desc)) maior_media
where alunos_medias_decres.media = maior_media.maior_media
order by nome_aluno asc;    

rem ************************************************************ 
rem 8)

rem Código dos Instrutores que foram contratados após 31/12/2000
select ins.cod_instrutor
from instrutores ins
where ins.admissao > to_date('31/12/2000', 'dd/mm/yyyy');

rem Código das Turmas ministradas pelos instrutores acima
select tur.cod_turma
from (select ins.cod_instrutor
      from instrutores ins
      where ins.admissao > to_date('31/12/2000', 'dd/mm/yyyy')) instrutor_con,
      turmas tur
where tur.cod_instrutor = instrutor_con.cod_instrutor;

rem Nome do(s) Aluno(s) matriculado(s) nas turmas acima
select distinct alu.nome_aluno
from (select tur.cod_turma
     from (select ins.cod_instrutor
           from instrutores ins
           where ins.admissao > to_date('31/12/2000', 'dd/mm/yyyy')) instrutor_con,
           turmas tur
     where tur.cod_instrutor = instrutor_con.cod_instrutor) turma_rest,
     alunos alu, historico his
where alu.matricula = his.matricula and turma_rest.cod_turma = his.cod_turma
order by nome_aluno asc;

rem ************************************************************ 
rem 9)

rem Código dos Instrutores que foram contratados após 31/12/2000
select ins.cod_instrutor
from instrutores ins
where ins.admissao > to_date('31/12/2000', 'dd/mm/yyyy');

rem Código dos Cursos ministradas pelos instrutores acima
select tur.cod_curso
from (select ins.cod_instrutor
      from instrutores ins
      where ins.admissao > to_date('31/12/2000', 'dd/mm/yyyy')) instrutor_con,
      turmas tur
where tur.cod_instrutor = instrutor_con.cod_instrutor;

rem Nome dos Cursos ministrados pelos instrutores restritos
select cur.nome_curso
from (select tur.cod_curso
      from (select ins.cod_instrutor
            from instrutores ins
            where ins.admissao > to_date('31/12/2000', 'dd/mm/yyyy')) instrutor_con,
            turmas tur
      where tur.cod_instrutor = instrutor_con.cod_instrutor) cursos_res,
      cursos cur
where cur.cod_curso = cursos_res.cod_curso
order by nome_curso asc;

rem ************************************************************ 
rem 10) "Por todos" = divisão!
select nome_curso
from cursos cur
where not exists(select cod_instrutor
                 from instrutores
                 where admissao > to_date('31/12/2020', 'dd/mm/yyyy')
                
                 minus

                 select cod_instrutor
                 from turmas
                 where cod_curso = cur.cod_curso)
and exists      (select cod_instrutor
                 from instrutores
                 where admissao > to_date('31/12/2020', 'dd/mm/yyyy'));

rem ************************************************************ 
rem 11)

rem Código do Instrutor com a Quantidade de Turmas Ministradas
select tur.cod_instrutor, count(cod_turma) as qtd_turma
from turmas tur
group by (tur.cod_instrutor)
order by cod_instrutor;

rem Maior Quantidade de Turmas Ministradas da Tabela Acima
select max(instrutor_max.qtd_turma) as qtd_max_turma
from (select tur.cod_instrutor, count(cod_turma) as qtd_turma
      from turmas tur
      group by (tur.cod_instrutor)
      order by cod_instrutor) instrutor_max;

rem Nome do Instrutor com a Maior Quantidade de Turmas Ministradas
select distinct ins.nome_instrutor
from (select tur.cod_instrutor, count(cod_turma) as qtd_turma
      from turmas tur
      group by (tur.cod_instrutor)
      order by cod_instrutor) instrutor_cod,
     (select max(instrutor_max.qtd_turma) as qtd_max_turma
      from (select tur.cod_instrutor, count(cod_turma) as qtd_turma
            from turmas tur
            group by (tur.cod_instrutor)
            order by cod_instrutor) instrutor_max) ministra_max,
     instrutores ins
where instrutor_cod.qtd_turma = ministra_max.qtd_max_turma and instrutor_cod.cod_instrutor = ins.cod_instrutor
order by nome_instrutor asc;

rem ************************************************************ 
rem 12)

rem Código do Curso com a Quantidade de Turmas
select tur.cod_curso, count(cod_turma) as qtd_turma
from turmas tur
group by (tur.cod_curso)
order by cod_curso;

rem Menor Quantidade de Turmas da Tabela Acima
select min(cursos_min.qtd_turma) as qtd_min_turma
from (select tur.cod_curso, count(cod_turma) as qtd_turma
      from turmas tur
      group by (tur.cod_curso)
      order by cod_curso) cursos_min;

rem Nome do Curso com a Menor Quantidade de Turmas Ministradas
select distinct cur.nome_curso
from (select tur.cod_curso, count(cod_turma) as qtd_turma
      from turmas tur
      group by (tur.cod_curso)
      order by cod_curso) cursos_cod,
     (select min(cursos_min.qtd_turma) as qtd_min_turma
      from (select tur.cod_curso, count(cod_turma) as qtd_turma
            from turmas tur
            group by (tur.cod_curso)
            order by cod_curso) cursos_min) ministrado_min,
     cursos cur
where cursos_cod.qtd_turma = ministrado_min.qtd_min_turma and cursos_cod.cod_curso = cur.cod_curso
order by nome_curso asc;

rem ************************************************************ 
rem 13)

rem Instrutores e Código de Turmas Associadas
select ins.nome_instrutor, tur.cod_turma
from instrutores ins, turmas tur
where ins.cod_instrutor = tur.cod_instrutor;

rem Retorna os Instrutores e a Quantidade de Turmas que Ministram (para cada)
select instru_turma.nome_instrutor, count(instru_turma.cod_turma) as qtd_turma_ministra
from (select ins.nome_instrutor, tur.cod_turma
      from instrutores ins, turmas tur
      where ins.cod_instrutor = tur.cod_instrutor)
      instru_turma
group by (instru_turma.nome_instrutor)
order by nome_instrutor asc;

rem Retorna a média de turmas ministradas
select avg(qtd_turma_ministra) as media_ministrados
  from (select instru_turma.nome_instrutor, count(instru_turma.cod_turma) as qtd_turma_ministra
        from (select ins.nome_instrutor, tur.cod_turma
              from instrutores ins, turmas tur
              where ins.cod_instrutor = tur.cod_instrutor)
              instru_turma
        group by (instru_turma.nome_instrutor)
        order by nome_instrutor);

rem Retorna os Instrutores (nome) que ministram acima da média
select instrutor_ministra_turma.nome_instrutor
from (select instru_turma.nome_instrutor, count(instru_turma.cod_turma) as qtd_turma_ministra
      from (select ins.nome_instrutor, tur.cod_turma
            from instrutores ins, turmas tur
            where ins.cod_instrutor = tur.cod_instrutor)
            instru_turma
      group by (instru_turma.nome_instrutor))
      instrutor_ministra_turma,
     (select avg(qtd_turma_ministra) as media_ministrados
      from (select instru_turma.nome_instrutor, count(instru_turma.cod_turma) as qtd_turma_ministra
            from (select ins.nome_instrutor, tur.cod_turma
                  from instrutores ins, turmas tur
                  where ins.cod_instrutor = tur.cod_instrutor)
                  instru_turma
            group by (instru_turma.nome_instrutor)
            order by nome_instrutor))
      media_turma_ministrados
where instrutor_ministra_turma.qtd_turma_ministra > media_turma_ministrados.media_ministrados
order by nome_instrutor;

rem ************************************************************ 
rem 14)

rem Nome e Código dos Cursos que são pré-requisitos
select distinct cur.cod_curso as cod_pre_requisito, cur.nome_curso as nome_pre_requisito
from cursos cur, cursos cur_pr
where cur.cod_curso = cur_pr.pre_requisito;

rem Nome dos Cursos e seus Pré-Requisitos
select distinct cur.nome_curso, pre_requisito_tabela.nome_pre_requisito
from (select cur.cod_curso as cod_pre_requisito, cur.nome_curso as nome_pre_requisito
      from cursos cur, cursos cur_pr
      where cur.cod_curso = cur_pr.pre_requisito) pre_requisito_tabela,
     cursos cur
where cur.pre_requisito = pre_requisito_tabela.cod_pre_requisito
order by nome_curso asc;

rem ************************************************************ 
rem 15)

rem Ordena cada código de turma com as suas notas que foram abaixo da média
select cod_turma
from historico
where nota < 5.0
order by cod_turma asc;

rem Retorna a quantidade de reprovações por código de turma
select turma_abaixo_media.cod_turma, count(turma_abaixo_media.cod_turma) as qtd_reprova
from (select cod_turma, nota
      from historico
      where nota < 5.0
      order by cod_turma asc) turma_abaixo_media
group by (cod_turma)
order by cod_turma asc;

rem Retorna o nome do curso e sua respectiva qtd de reprovação
select cur.nome_curso, turma_reprova.qtd_reprova
from (select turma_abaixo_media.cod_turma, count(turma_abaixo_media.cod_turma) as qtd_reprova
      from (select cod_turma, nota
            from historico
            where nota < 5.0
            order by cod_turma asc) turma_abaixo_media
      group by (cod_turma)) turma_reprova,
      turmas tur, cursos cur
where tur.cod_turma = turma_reprova.cod_turma and tur.cod_curso = cur.cod_curso
order by cur.nome_curso asc;

rem Realiza a soma total de reprovação por curso
select curso_reprova.nome_curso, sum(curso_reprova.qtd_reprova) as qtd_reprova_total
from (select cur.nome_curso, turma_reprova.qtd_reprova
      from (select turma_abaixo_media.cod_turma, count(turma_abaixo_media.cod_turma) as qtd_reprova
            from (select cod_turma, nota
                  from historico
                  where nota < 5.0
                  order by cod_turma asc) turma_abaixo_media
            group by (cod_turma)) turma_reprova,
            turmas tur, cursos cur
      where tur.cod_turma = turma_reprova.cod_turma and tur.cod_curso = cur.cod_curso) curso_reprova
group by (curso_reprova.nome_curso)
order by curso_reprova.nome_curso asc;

rem Obtenção do maior valor de reprovação por curso
select max(qtd_reprova_total) as qtd_max_reprova
from (select curso_reprova.nome_curso, sum(curso_reprova.qtd_reprova) as qtd_reprova_total
      from (select cur.nome_curso, turma_reprova.qtd_reprova
            from (select turma_abaixo_media.cod_turma, count(turma_abaixo_media.cod_turma) as qtd_reprova
                  from (select cod_turma, nota
                        from historico
                        where nota < 5.0
                        order by cod_turma asc) turma_abaixo_media
                  group by (cod_turma)) turma_reprova,
                  turmas tur, cursos cur
            where tur.cod_turma = turma_reprova.cod_turma and tur.cod_curso = cur.cod_curso) curso_reprova
      group by (curso_reprova.nome_curso));

rem Retorna o nome do curso com maior valor de reprovação
select curso_reprova_total.nome_curso
from (select curso_reprova.nome_curso, sum(curso_reprova.qtd_reprova) as qtd_reprova_total
      from (select cur.nome_curso, turma_reprova.qtd_reprova
            from (select turma_abaixo_media.cod_turma, count(turma_abaixo_media.cod_turma) as qtd_reprova
                  from (select cod_turma, nota
                        from historico
                        where nota < 5.0
                        order by cod_turma asc) turma_abaixo_media
                  group by (cod_turma)) turma_reprova,
                  turmas tur, cursos cur
            where tur.cod_turma = turma_reprova.cod_turma and tur.cod_curso = cur.cod_curso) curso_reprova
      group by (curso_reprova.nome_curso)) 
      curso_reprova_total,
     (select max(qtd_reprova_total) as qtd_max_reprova
      from (select curso_reprova.nome_curso, sum(curso_reprova.qtd_reprova) as qtd_reprova_total
            from (select cur.nome_curso, turma_reprova.qtd_reprova
                  from (select turma_abaixo_media.cod_turma, count(turma_abaixo_media.cod_turma) as qtd_reprova
                        from (select cod_turma, nota
                              from historico
                              where nota < 5.0
                              order by cod_turma asc) turma_abaixo_media
                        group by (cod_turma)) turma_reprova,
                        turmas tur, cursos cur
                where tur.cod_turma = turma_reprova.cod_turma and tur.cod_curso = cur.cod_curso) curso_reprova
            group by (curso_reprova.nome_curso)))
        qtd_max_reprova_total
where curso_reprova_total.qtd_reprova_total = qtd_max_reprova_total.qtd_max_reprova;

rem ************************************************************ 
rem 16)

rem Lista com todos os alunos (nome) e os códigos de cursos associados (repetidos)
select alu.nome_aluno, tur.cod_curso
from alunos alu, historico his, turmas tur
where alu.matricula = his.matricula and his.cod_turma = tur.cod_turma;

rem Lista com os valores gastos por cada aluno em cada curso
select aluno_curso.nome_aluno, cur.preco
from (select alu.nome_aluno, tur.cod_curso
      from alunos alu, historico his, turmas tur
      where alu.matricula = his.matricula and his.cod_turma = tur.cod_turma) aluno_curso,
      cursos cur
where aluno_curso.cod_curso = cur.cod_curso;

rem Lista o valor total gasto por cada aluno
select aluno_preco.nome_aluno, sum(aluno_preco.preco) as preco_total
from (select aluno_curso.nome_aluno, cur.preco
      from (select alu.nome_aluno, tur.cod_curso
            from alunos alu, historico his, turmas tur
            where alu.matricula = his.matricula and his.cod_turma = tur.cod_turma) aluno_curso,
            cursos cur
      where aluno_curso.cod_curso = cur.cod_curso) aluno_preco
group by (aluno_preco.nome_aluno)
order by nome_aluno asc;

rem ************************************************************ 
rem 17)

rem Código de Curso e Carga Horária associadas (não nulas)
select cod_curso, carga_horaria
from cursos
where carga_horaria is not null;

rem Retorna os Instrutores e Carga Hóraria associada
select ins.nome_instrutor, curso_horario.carga_horaria
from (select cod_curso, carga_horaria
      from cursos
      where carga_horaria is not null) curso_horario,
      instrutores ins, turmas tur
where curso_horario.cod_curso = tur.cod_curso and ins.cod_instrutor = tur.cod_instrutor;

rem Lista a Carga Horária total gasta por Cada Instrutor
select instrutor_horario.nome_instrutor, sum(instrutor_horario.carga_horaria) as carga_horaria_total
from (select ins.nome_instrutor, curso_horario.carga_horaria
      from (select cod_curso, carga_horaria
            from cursos
            where carga_horaria is not null) curso_horario,
            instrutores ins, turmas tur
      where curso_horario.cod_curso = tur.cod_curso and ins.cod_instrutor = tur.cod_instrutor) instrutor_horario
group by (instrutor_horario.nome_instrutor)
order by nome_instrutor;

rem ************************************************************ 
rem 18) 

rem Nome e Código dos Cursos que são pré-requisitos
select distinct cur.cod_curso as cod_pre_requisito, cur.preco
from cursos cur, cursos cur_pr
where cur.cod_curso = cur_pr.pre_requisito;

rem Valor total dos Cursos que são pré-requisitos
select sum(cur_pre_requisitos.preco) as preco_total
from (select distinct cur.cod_curso as cod_pre_requisito, cur.preco
      from cursos cur, cursos cur_pr
      where cur.cod_curso = cur_pr.pre_requisito) cur_pre_requisitos;

rem Lista os cursos (código e nome) cujos preços unitários sejam menores que o preço total dos cursos pré-requisitos
select cur.cod_curso, cur.nome_curso
from (select sum(cur_pre_requisitos.preco) as preco_total
      from (select distinct cur.cod_curso as cod_pre_requisito, cur.preco
            from cursos cur, cursos cur_pr
            where cur.cod_curso = cur_pr.pre_requisito) cur_pre_requisitos) cur_pr, 
     cursos cur
where cur.preco < cur_pr.preco_total;

rem ************************************************************ 
rem 19)

rem Retorna o nome dos alunos e nome do curso de diferentes matrículas
select alu.nome_aluno, cur.nome_curso
from alunos alu, historico his, turmas tur, cursos cur
where alu.matricula = his.matricula and his.cod_turma = tur.cod_turma and tur.cod_curso = cur.cod_curso
order by alu.nome_aluno asc;

rem Retorna o nome do aluno e os cursos repetidos (em quantidade)
select aluno_cursos.nome_aluno, aluno_cursos.nome_curso, count(*) as qtd_cursada
from (select alu.nome_aluno, cur.nome_curso
      from alunos alu, historico his, turmas tur, cursos cur
      where alu.matricula = his.matricula and his.cod_turma = tur.cod_turma and tur.cod_curso = cur.cod_curso)
      aluno_cursos
group by aluno_cursos.nome_aluno, aluno_cursos.nome_curso
having count(*) > 1
order by nome_aluno asc;

rem ************************************************************ 
