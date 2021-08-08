REM   Script: UNESP Bauru - BDI - SQL: BD Empresa
REM   teste da P2

REM   Script: Cria e Popula o Banco de Dados EMPRESA


REM   Script para criar e popular o banco de dados Empresa


create table employee(  
    fname varchar2(10) not null,  
    minit varchar(5),  
    lname varchar(10) not null,  
    ssn number(9),  
    bdate date,  
    addreess varchar2(30),  
    sex char(1) not null,  
    salary number(7,2) not null,  
    super_ssn number(9),  
    dno number(1), 
    primary key(ssn));

create table department(  
    dname varchar2(20) not null,  
    dnumber number(1) primary key,  
    mgr_ssn number(9) not null,  
    mgr_start_date date default sysdate);

create table dept_locations(  
    dnumber number(9),  
    dlocation varchar2(20),  
    primary key(dnumber,dlocation));

create table Project(  
    pname varchar2(20) not null unique,  
    pnumber number(2) primary key,  
    plocation varchar2(20) not null,  
    dnum number(9));

create table works_on(  
    essn number(9),  
    pno number(2),  
    hours number(3,1),  
    primary key(essn,pno));

create table dependents(  
    essn number(9),  
    dependent_name varchar2(30),  
    sex char(1) not null,  
    bdate date,  
    relationship varchar2(10),  
    primary key(essn,dependent_name));

insert into employee(fname,minit,lname,ssn,bdate,addreess,sex,salary,super_ssn,dno) 
values('John','B','Smith',123456789,to_date('09/01/1965','dd/mm/yyyy'),'731 Fondren, Houston, TX','M',30000,333445555,5);

insert into employee(fname,minit,lname,ssn,bdate,addreess,sex,salary,super_ssn,dno) 
values('Franklin','T','Wong',333445555,to_date('08/12/1955','dd/mm/yyyy'),'638 Voss, Houston, TX','M',40000,888665555,5);

insert into employee(fname,minit,lname,ssn,bdate,addreess,sex,salary,super_ssn,dno) 
values('Alicia','J','Zelaya',999887777,to_date('19/01/1968','dd/mm/yyyy'),'3321 Castle, Spring, TX','F',25000,987654321,4);

insert into employee(fname,minit,lname,ssn,bdate,addreess,sex,salary,super_ssn,dno) 
values('Jennifer','S','Wallace',987654321,to_date('20/06/1941','dd/mm/yyyy'),'291 Berry, Bellaire, TX','F',43000,888665555,4);

insert into employee(fname,minit,lname,ssn,bdate,addreess,sex,salary,super_ssn,dno) 
values('Ramesh','K','Narayan',666884444,to_date('15/09/1962','dd/mm/yyyy'),'975 Fire Oak, Humble, TX','M',38000,333445555,5);

insert into employee(fname,minit,lname,ssn,bdate,addreess,sex,salary,super_ssn,dno) 
values('Joyce','A','English',453453453,to_date('31/07/1972','dd/mm/yyyy'),'5631 Rice, Houston, TX','F',25000,333445555,5);

insert into employee(fname,minit,lname,ssn,bdate,addreess,sex,salary,super_ssn,dno) 
values('Ahmad','V','Jabbar',987987987,to_date('29/03/1969','dd/mm/yyyy'),'980 Dallas, Houston, TX','M',25000,987654321,4);

insert into employee(fname,minit,lname,ssn,bdate,addreess,sex,salary,super_ssn,dno) 
values('James','E','Borg',888665555,to_date('10/11/1937','dd/mm/yyyy'),'450 Stone, Houston, TX','M',55000,NULL,1);

insert into department(dname, dnumber, mgr_ssn, mgr_start_date) 
values('Research', 5, 333445555, to_date('22/05/1988','dd/mm/yyyy'));

insert into department(dname, dnumber, mgr_ssn, mgr_start_date) 
values('Administration', 4, 987654321, to_date('01/01/1995','dd/mm/yyyy'));

insert into department(dname, dnumber, mgr_ssn, mgr_start_date) 
values('Headquarters', 1, 888665555, to_date('19/06/1981','dd/mm/yyyy'));

insert into dept_locations(dnumber, dlocation) 
values(1, 'Houston');

insert into dept_locations(dnumber, dlocation) 
values(4, 'Stafford');

insert into dept_locations(dnumber, dlocation) 
values(5, 'Bellaire');

insert into dept_locations(dnumber, dlocation) 
values(5, 'Sugarlang');

insert into dept_locations(dnumber, dlocation) 
values(5, 'Houston');

insert into Project(pname, pnumber, plocation, dnum) 
values('ProductX', 1, 'Bellaire', 5);

insert into Project(pname, pnumber, plocation, dnum) 
values('ProductY', 2, 'Sugarland', 5);

insert into Project(pname, pnumber, plocation, dnum) 
values('ProductZ', 3, 'Houston', 5);

insert into Project(pname, pnumber, plocation, dnum) 
values('Computerization', 10, 'Stafford', 4);

insert into Project(pname, pnumber, plocation, dnum) 
values('Reorganization', 20, 'Houston', 1);

insert into Project(pname, pnumber, plocation, dnum) 
values('Newbenefits', 30, 'Stafford', 4);

insert into works_on(essn, pno, hours) 
values(123456789, 1, 32.5);

insert into works_on(essn, pno, hours) 
values(123456789, 2, 7.5);

insert into works_on(essn, pno, hours) 
values(666884444, 3, 40.0);

insert into works_on(essn, pno, hours) 
values(453453453, 1, 20.0);

insert into works_on(essn, pno, hours) 
values(453453453, 2, 20.0);

insert into works_on(essn, pno, hours) 
values(333445555, 2, 10.0);

insert into works_on(essn, pno, hours) 
values(333445555, 3, 10.0);

insert into works_on(essn, pno, hours) 
values(333445555, 10, 10.0);

insert into works_on(essn, pno, hours) 
values(333445555, 20, 10.0);

insert into works_on(essn, pno, hours) 
values(999887777, 30, 30.0);

insert into works_on(essn, pno, hours) 
values(999887777, 10, 10.0);

insert into works_on(essn, pno, hours) 
values(987987987, 10, 35.0);

insert into works_on(essn, pno, hours) 
values(987987987, 30, 5.0);

insert into works_on(essn, pno, hours) 
values(987654321, 30, 20.0);

insert into works_on(essn, pno, hours) 
values(987654321, 20, 15.0);

insert into works_on(essn, pno, hours) 
values(888665555, 20, NULL);

insert into dependents(essn, dependent_name, sex, bdate, relationship) 
values(333445555, 'Alice', 'F', to_date('05/04/1986','dd/mm/yyyy'), 'Daughter');

insert into dependents(essn, dependent_name, sex, bdate, relationship) 
values(333445555, 'Theodore', 'M', to_date('25/10/1983','dd/mm/yyyy'), 'Son');

insert into dependents(essn, dependent_name, sex, bdate, relationship) 
values(333445555, 'Joy', 'F', to_date('03/05/1958','dd/mm/yyyy'), 'Spouse');

insert into dependents(essn, dependent_name, sex, bdate, relationship) 
values(987654321, 'Abner', 'M', to_date('28/02/1942','dd/mm/yyyy'), 'Spouse');

insert into dependents(essn, dependent_name, sex, bdate, relationship) 
values(123456789, 'Michael', 'M', to_date('04/01/1988','dd/mm/yyyy'), 'Son');

insert into dependents(essn, dependent_name, sex, bdate, relationship) 
values(123456789, 'Alice', 'F', to_date('30/12/1988','dd/mm/yyyy'), 'Daughter');

insert into dependents(essn, dependent_name, sex, bdate, relationship) 
values(123456789, 'Elizabeth', 'F', to_date('05/05/1967','dd/mm/yyyy'), 'Spouse');

alter table employee 
    add foreign key (super_ssn) references employee;

alter table employee 
    add foreign key (dno) references department;

alter table department 
    add foreign key (mgr_ssn) references employee;

alter table dept_locations 
    add foreign key (dnumber) references department;

alter table Project 
    add foreign key (dnum) references department;

alter table works_on 
    add foreign key (essn) references employee;

alter table works_on 
    add foreign key (pno) references Project;

alter table dependents 
    add foreign key (essn) references employee;

-- Adiciona sum_salary como atributo derivado
ALTER TABLE Project
ADD sum_salary number(5,2) default 0;


