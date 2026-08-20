# Write your MySQL query statement below
SELECT e.NAME AS EMPLOYEE
from Employee e
join Employee m
on e.managerID = m.id
where e.salary > m.salary;