CREATE OR REPLACE TRIGGER Controla_Soma_Salario
AFTER
INSERT OR UPDATE OR DELETE
OF salary
ON employee
FOR EACH ROW
  BEGIN
    IF INSERTING THEN
        UPDATE Project Proj
           SET Proj.sum_salary = Proj.sum_salary + :new.salary
        WHERE Proj.dnum = :new.dno;
    ELSIF DELETING THEN
        UPDATE Project Proj
           SET Proj.sum_salary = Proj.sum_salary - :old.salary
        WHERE Proj.dnum = :old.dno;
    ELSE
        UPDATE Project Proj
           SET Proj.sum_salary = Proj.sum_salary + :new.salary
        WHERE Proj.dnum = :new.dno;
        UPDATE Project Proj
           SET Proj.sum_salary = Proj.sum_salary - :old.salary
        WHERE Proj.dnum = :old.dno;
    END IF;
  END;
/
