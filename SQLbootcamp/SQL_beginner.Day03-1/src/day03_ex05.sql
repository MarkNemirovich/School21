SELECT DISTINCT pizzeria.name FROM person_visits
INNER JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
INNER JOIN person ON person.id = person_visits.person_id
WHERE person.name = 'Andrey'
EXCEPT
SELECT DISTINCT pizzeria.name FROM person_order
INNER JOIN menu ON menu.id = person_order.menu_id
INNER JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
INNER JOIN person ON person.id = person_order.person_id
WHERE person.name = 'Andrey'