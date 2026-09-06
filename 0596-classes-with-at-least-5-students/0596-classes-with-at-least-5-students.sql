# Write your MySQL query statement below
select class from courses
GROUP BY class
having count(student) >= 5;