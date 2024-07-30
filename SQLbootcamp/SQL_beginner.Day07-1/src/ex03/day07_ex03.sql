select t1.name, coalesce(t1.count,0) + coalesce(t2.count,0) as total_count
from
(select p.name, count(*) as "count"
from person_visits inner join pizzeria p on p.id = person_visits.pizzeria_id
group by p.name) as t1 full join
(select p.name, count(*) as "count"
from person_order inner join menu m on person_order.menu_id = m.id
inner join pizzeria p on m.pizzeria_id = p.id
group by p.name) as t2 on t1.name = t2.name
order by 2 desc,1 asc;