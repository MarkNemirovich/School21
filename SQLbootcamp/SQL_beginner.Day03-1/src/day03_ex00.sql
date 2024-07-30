WITH kate_visits AS (
SELECT
	person_visits.person_id as person_id,
	pizzeria.id as pizzeria_id, 
	pizzeria.name as pizzeria_name, 
	person_visits.visit_date
FROM person_visits
INNER JOIN pizzeria ON pizzeria.id = person_visits.pizzeria_id
INNER JOIN person ON person.id = person_visits.person_id
WHERE person.name = 'Kate'
)
SELECT 
	menu.pizza_name, 
	menu.price, 
	kate_visits.pizzeria_name, 
	kate_visits.visit_date 
FROM kate_visits
INNER JOIN menu ON menu.pizzeria_id = kate_visits.pizzeria_id
WHERE menu.price BETWEEN 800 AND 1000
ORDER BY menu.pizza_name, 
	menu.price, 
	kate_visits.pizzeria_name