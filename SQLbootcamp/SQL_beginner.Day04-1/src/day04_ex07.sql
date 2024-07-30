WITH pizzerias_ids AS (
	SELECT pizzeria.id 
	FROM pizzeria
	INNER JOIN menu ON menu.pizzeria_id = pizzeria.id
	WHERE menu.price < 800
EXCEPT
	SELECT pizzeria.id AS pizzeria_name
	FROM menu
	CROSS JOIN pizzeria
	INNER JOIN person_visits ON person_visits.pizzeria_id = pizzeria.id AND person_visits.pizzeria_id = menu.pizzeria_id
	INNER JOIN person ON person.id = person_visits.person_id
	WHERE person.name = 'Dmitriy' AND person_visits.visit_date = '2022-01-08' AND menu.price < 800
	LIMIT 1
),
person_visits_id AS (
    SELECT MAX(id) + 1 AS new_id FROM person_visits
)
INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date)
SELECT
    person_visits_id.new_id, person.id, pizzerias_ids.id, '2022-01-08'
FROM pizzerias_ids
CROSS JOIN person_visits_id
INNER JOIN person ON person.name = 'Dmitriy';

REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;