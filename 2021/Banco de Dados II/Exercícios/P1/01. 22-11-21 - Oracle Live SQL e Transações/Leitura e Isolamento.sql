rem ************ Nome: Davi Augusto Neves Leite ******************
rem ************ RA: 191027383                  ******************

rem **************** SGBD: Oracle Live SQL ***********************

rem **************************************************************
rem * Fenômenos de leitura e níveis de isolamento das transações *
rem **************************************************************


rem Pré-requisitos: criação e população da tabela "Toys"

create table toys (
  toy_name varchar2(30),
  price    number(10, 2)
);

insert into toys values ( 'Miss Snuggles', 9.99 );

commit;

rem 1) Introdução: o tutorial irá abordar dos problemas de leitura/escrita por duas ou mais pessoas, ao mesmo tempo, na mesma tabela
select * from toys;

rem 2) Transações Autonomas: transações dentro de outras
declare
  pragma autonomous_transaction;

rem Dessa maneira, é possível inserir o primeiro dado abaixo e excluir com rollback, ao mesmo tempo que é inserido o segundo e ele não é excluido (transação dentro de outra)
insert into toys values ( 'Baby Turtle', 7.95 );

declare
  pragma autonomous_transaction;
begin
  insert into toys values ( 'Blue Dinosaur', 15.95 );
  commit;
end;
/

select * from toys;
rollback;
select * from toys;

rem 3) Fenomeno de Leitura: aborda os problemas de leitura/escrita na tupla, como leituras sujas, leituras sem repetição e leituras fantasmas
rem OBS: os três tipos de problemas abordados são impossíveis no Oracle Database, haja visto que há um tratamento previsto
rem 
rem Leitura Suja: quando é possível visualizar tuplas não comitadas em outra transação, não tendo garantia que outra transação irá comitar
rem Leitura Sem Repetição: quando ocorre a seleção da mesma tupla e retorna valores diferentes
rem Leitura Fantasma: tipo especial de Leitura Sem Repetição em que uma transação insere/deleta a tupla em que outra transação estava usando de condição (where), podendo retornar valores diferentes

rem 4) Níveis de Isolamento: existe quatro níveis de isolamento para cada uma dos tipos de leitura anterior, sendo eles: leitura não comitada, leitura comitada, leitura repetível e leitura serializável.
rem
rem Leitura não comitada: não é relevante, já que o Oracle Database trata
rem Leitura comitada: default do Oracle Databse, em que há consistência para cada operação DML (pode visualizar os dados salvos antes de iniciar a transação). Utilização do MVCC (controle de concorrência de multiversão) em que é criado um buffer da tupla a ser manipulada por um transação.
rem Leitura repetível: prover consistentes resultados de uma query, já implementado pelo Oracle Database...
rem Leitura serializável: utilizado para garantir a consistência de transação por nível (serialização), separando as operações de transações concorrentes

rem 5) Como setar o nível de isolamento de uma transação: comando abaixo
set transaction isolation level read committed;

rem Ao executar o comando abaixo, terá erro pois o comando acima deve ser o primeiro!
insert into toys values ( 'Purple Ninja', 19.99 );
set transaction isolation level read committed;
rollback;

rem 6) Leitura comitada: default do Oracle Database, o que garante a consistência de comandos por nível.
rem O código aabaixo representa o tratamento feito pelo SGBD, em que as mudanças devem ser comitadas antes da query iniciar
set transaction isolation level read committed;
select * from toys;

declare 
  pragma autonomous_transaction;
begin
  update toys set price = 1.61;
  insert into toys values ( 'Baby Turtle', 19.99 );  
  commit;
end;
/

select * from toys;
commit;
select * from toys;

rem 7) Serialização: existência da consistência de transação por nível, sendo utilizado se há apenas um usuário no database
rem Neste caso, as mudanças feitas por uma transação são invisíveis a outra.
rem É possível ver isso no código abaixo, em que a transação pai não pode ver os novos valores da transação filho (dentro do pai), a menos que o filho dê um commit
set transaction isolation level serializable;

select * from toys;

declare 
  pragma autonomous_transaction;
begin
  update toys set price = 2.71;
  insert into toys values ( 'Purple Ninja', 7.95 );  
  commit;
end;
/

select * from toys;
commit;
select * from toys;

rem Também, este tipo garante que as tuplas não sejam modificadas por uma transação se já estão sendo por outras
set transaction isolation level serializable;

select * from toys;

declare 
  pragma autonomous_transaction;
begin
  update toys set price = 3.14;
  commit;
end;
/

update toys 
set    price = price * 10
where  toy_name = 'Miss Snuggles';

delete toys 
where  toy_name = 'Baby Turtle';

commit;
select * from toys;

rem Dessa forma, deve-se usar a Serialização quando uma transação acessa as mesmas tuplas muitas vezes e quando muitas pessoas estão rodando a transação ao mesmo tempo
rem Contudo, há necessidade de manipular o erro "ORA-08177"...

rem 8) Apenas Leitura: outro modo de transação, o qual funciona semelhante ao Serializável (consistência em transações por nível), contudo há a restrição de apenas rodar o comando SELECT
rem Caso seja utilizado outro comando ao contrário do SELECT, irá ter o erro "ORA-01456".
set transaction read only;

select * from toys;

update toys
set    price = price + 1;

declare 
  pragma autonomous_transaction;
begin
  update toys set price = 99.00;
  commit;
end;
/

select * from toys;
commit;
select * from toys;

rem Ou seja, é um modo que deve ser utilizado para conferência dos dados e criação de relatórios
rem Também é possível colocar a transação como leitura-escrita, caso seja necessário utilizar os comandos de não-SELECT DML
set transaction read write;

rem Também, esse é o modo padrão do Oracle Database
