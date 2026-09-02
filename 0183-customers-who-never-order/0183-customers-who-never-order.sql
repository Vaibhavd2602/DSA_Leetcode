# Write your MySQL query statement below
Select C.name as Customers
from customers C
Left Join orders as O
On c.id = o.customerid
where o.customerid is null;
