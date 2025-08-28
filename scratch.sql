SELECT * FROM customers; 

INSERT INTO customers(name, email) VALUES('John Doe', 'john@example.com'); 

UPDATE customers SET email='newemail@example.com' WHERE id = 1; 

DELETE FROM customers WHERE id = 1; 

CREATE TABLE employees (
  id INT PRIMARY KEY,
  name VARCHAR(50),
  age INT,
  salary DECIMAL(10,2)
);

ALTER TABLE employees ADD COLUMN department VARCHAR(50); 

SELECT customers.name, orders.order_date
FROM customers
JOIN orders ON customers.id = orders.customer_id; 


/*
Suppose you have the following tables in a database:
====================================================
Person
    PersonId       int            (Primary Key)
    FirstName      varchar(255)
    LastName       varchar(255)

Team
    TeamId         int            (Primary Key)
    Name           varchar(255)
    LeadId         int            (Foreign Key to Person table)

PeopleInTeams
    PersonId       int            (Foreign key to Person table)
    TeamId         int            (Foreign key to Team table)
*/

/*
Question (1)
============
Write a SQL statement that will list:
- all people working in the company and what team they are working in
*/
SELECT Person.FirstName, Person.LastName, Team.Name 
FROM Person
JOIN PeopleInTeams ON Person.PersonId = PeopleInTeams.PersonId
JOIN Team ON Team.TeamId = PeopleInTeams.TeamId; 

/*
Question (2)
============ 
Write a SQL statement that will list:
- the team name
- and number of team members for teams that have more than two members
*/
SELECT Team.Name, COUNT(PeopleInTeams.PersonId)
FROM Team
JOIN PeopleInTeams ON Team.TeamId = PeopleInTeams.TeamId
GROUP BY Team.Name
HAVING COUNT(PeopleInTeams.PersonId) > 2; 

/*
Question (3)
============ 
Write a SQL statement that will list:
- all people working in the company,
- what team are they working in
- and what is the first and last name of the lead of the team
*/

SELECT p.FirstName, p.LastName, t.Name, tl.FirstName, tl.LastName
FROM PeopleInTeams pit 
INNER JOIN Person p ON pit.PersonId = p.PersonId
INNER JOIN Team t ON pit.TeamId = t.TeamId
INNER JOIN Person tl ON t.LeadId = tl.Person; 