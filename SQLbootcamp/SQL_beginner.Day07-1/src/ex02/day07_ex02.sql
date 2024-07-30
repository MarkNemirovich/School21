(select p.name, count(*) as "count", 'visit' as action_type
from person_visits inner join pizzeria p on p.id = person_visits.pizzeria_id
group by p.name
order by 2 desc
limit 3)
union
(select p.name, count(*) as "count", 'order' as action_type
from person_order inner join menu m on person_order.menu_id = m.id
inner join pizzeria p on m.pizzeria_id = p.id
group by p.name
order by 2 desc
limit 3)
order by 3,2 desc