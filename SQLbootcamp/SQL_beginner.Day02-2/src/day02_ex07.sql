SELECT
    pizzeria.name AS pizzeria_name,
	person_visits.visit_date,
	menu.price
FROM menu
CROSS JOIN pizzeria
INNER JOIN person_visits ON person_visits.pizzeria_id = pizzeria.id AND person_visits.pizzeria_id = menu.pizzeria_id
INNER JOIN person ON person.id = person_visits.person_id
WHERE person.name = 'Dmitriy' AND person_visits.visit_date = '2022-01-08' AND menu.price < 800