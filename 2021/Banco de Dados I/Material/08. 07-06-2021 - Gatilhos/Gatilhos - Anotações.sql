rem Gatilhos - Escopos
rem ****************************************
rem Variáveis -> :new.nome_campo (informação nova  na tabela)
rem           -> :old.nome_campo (informação atual na tabela)
rem ****************************************
rem ATRIBUTOS DERIVADOS: https://www.devmedia.com.br/trabalhando-com-triggers-dml-no-oracle/32329 e 

rem Sintaxe Básica
CREATE [OR REPLACE ] TRIGGER trigger_name
  {BEFORE | AFTER | INSTEAD OF }
  {INSERT [OR] | UPDATE [OR] | DELETE}
  [OF col_name]
  ON table_name
  [REFERENCING OLD AS o NEW AS n]
  [FOR EACH ROW]
  WHEN (condition)
  DECLARE
    Declaration-statements
  BEGIN
    Executable-statements
  EXCEPTION Exception-handling-statements
  END;
/

rem Exemplo 1
CREATE OR REPLACE TRIGGER Atualiza_salario_func
    BEFORE DELETE OR INSERT OR UPDATE ON funcionario
    FOR EACH ROW
  WHEN (NEW.CODFUNC > 0)
  DECLARE
      diferenca_salario number;
  BEGIN
      diferenca_salario  := :NEW.SALARIOFUNC  - :OLD.SALARIOFUNC;
      dbms_output.put('Salário antigo:' || :OLD.salarioFunc);
      dbms_output.put('Salário novo:' || :NEW.salarioFunc);
      dbms_output.put_line(' A diferença de salário foi de: ' || diferenca_salario);
  END;
  /

rem Exemplo 2: Trigger COMPOSTA
CREATE OR REPLACE TRIGGER <trigger-name>
    FOR <trigger-action> ON <table-name>
      COMPOUND TRIGGER
    -- Declaração global.
    g_global_variable VARCHAR2(10);

    BEFORE STATEMENT IS
    BEGIN
      NULL; -- as instruções são postas aqui. --
    END BEFORE STATEMENT;

    BEFORE EACH ROW IS
    BEGIN
      NULL; -- as instruções são postas aqui. --
    END BEFORE EACH ROW;

    AFTER EACH ROW IS
    BEGIN
      NULL; -- as instruções são postas aqui. --
    END AFTER EACH ROW;

    AFTER STATEMENT IS
    BEGIN
      NULL; -- as instruções são postas aqui. --
    END AFTER STATEMENT;
  END <trigger-name>;
  /

rem Exemplo Nilceu:
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

rem ****************************************
rem VIEW: https://www.devmedia.com.br/criando-visoes-views-no-oracle/1945

rem Sintaxe Padrão: subquery é onde fica a query (select e tals)
CREATE [OR REPLACE] [FORCE|NOFORCE] VIEW Nome_Da_View
  [(alias[, alias]...)]
 AS subquery
[WITH CHECK OPTION [CONSTRAINT nome_Constraint]]
[WITH READ ONLY [CONSTRAINT nome_Constraint]];

rem Exemplo 1
CREATE VIEW emp_dep_option_Const
 AS
  (SELECT employee_id,Last_name,salary
 FROM
   employees
 WHERE department_id = 20)
 WITH CHECK OPTION CONSTRAINT emp_20;

 rem Exemplo 2
 CREATE VIEW emp_dep_apelido(Cod_Func,Nome_Func,Salario)
 AS (SELECT employee_id,Last_name,salary
     FROM employees);


rem ****************************************
rem ESPECIALIZAÇÃO DISJUNTA

rem Sintaxe Básica: igual Gatilho!!! (usado para inserir nas View!!!)
CREATE [OR REPLACE ] TRIGGER trigger_name
  {BEFORE | AFTER | INSTEAD OF }
  {INSERT [OR] | UPDATE [OR] | DELETE}
  [OF col_name]
  ON table_name
  [REFERENCING OLD AS o NEW AS n]
  [FOR EACH ROW]
  WHEN (condition)
  DECLARE
    Declaration-statements
  BEGIN
    Executable-statements
  EXCEPTION Exception-handling-statements
  END;
/

rem Exemplo: Dado três tabelas (Pessoa, Aluno e Professor) e, sabendo que CPF é a chave em comum de Aluno e Professor
rem         (ou seja, existe uma especialização de Pessoa para Aluno e Professor -> sera a view PessoaAluno)
rem Gatilho para Inserir na View de Especialização Disjunta PessoaAluno!!
CREATE OR REPLACE TRIGGER Controla_Insert_View_PessoaAluno
INSTEAD OF INSERT ON PessoaAluno
FOR EACH row
BEGIN
    INSERT INTO Pessoa(CPF, Nome, Endereco, Fone) VALUES(:new.CPF, :new.Nome, :new.Endereco, :new.Fone);
    INSERT INTO Aluno(CPF, RA, Email) VALUES(:new.CPF, :new.RA, :new.Email);
END;
/

rem ****************************************
rem AUDITORIA: https://vidadba.wordpress.com/2016/11/08/auditoria-utilizando-triggers/

rem Sintaxe Básica: igual Gatilho !!!
CREATE [OR REPLACE ] TRIGGER trigger_name
  {BEFORE | AFTER | INSTEAD OF }
  {INSERT [OR] | UPDATE [OR] | DELETE}
  [OF col_name]
  ON table_name
  [REFERENCING OLD AS o NEW AS n]
  [FOR EACH ROW]
  WHEN (condition)
  DECLARE
    Declaration-statements
  BEGIN
    Executable-statements
  EXCEPTION Exception-handling-statements
  END;
/

rem Exemplo: suponha que queira armazenar o LOG de operações realizadas numa "Tabela Comum"
rem Primeiro passo é criar uma tabela comum (a que será analisada)
CREATE TABLE common_table (key VARCHAR2(16) primary key, formula VARCHAR2(16));
INSERT INTO common_table VALUES ('square', 'f(x)=x^2');

rem Segundo passo é criar a tabela de log onde as informações de auditoria serão armazenadas.
CREATE TABLE audit_table (LOG VARCHAR2(150), timestamp DATE DEFAULT SYSDATE);
 
rem Terceiro passo é criar a trigger que ira identificar qualquer evento de insert, update ou delete na tabela comum e executar a ação para capturar os dados que estão sendo modificados.
CREATE OR REPLACE TRIGGER audit_trigger_Common_Table
AFTER INSERT OR DELETE OR UPDATE ON common_table
FOR EACH ROW
BEGIN
  IF INSERTING THEN
    INSERT INTO audit_table(LOG) VALUES (USER || ' is inserting' || ' new key: ' || :new.key);
  ELSIF DELETING THEN
    INSERT INTO audit_table(LOG) VALUES (USER || ' is deleting' || ' new key: ' || :old.key);
  ELSIF UPDATING('FORMULA') THEN
    INSERT INTO audit_table(LOG) VALUES (USER || ' is updating' || ' old formula: ' || :old.formula || ' new formula: ' || :new.formula);
  ELSIF UPDATING THEN
    INSERT INTO audit_table(LOG) VALUES (USER || ' is updating' || ' old key: ' || :old.key || ' new key: ' || :new.key);
  END IF;
END;
/
