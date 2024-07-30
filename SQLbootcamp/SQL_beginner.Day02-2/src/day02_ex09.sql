SELECT p.name
FROM person p
	INNER JOIN person_order po ON po.person_id = p.id
	INNER JOIN menu m ON m.id = po.menu_id
WHERE gender = 'female'
	AND m.pizza_name LIKE 'pepperoni%'
INTERSECT
SELECT p.name
FROM person p
	INNER JOIN person_order po ON po.person_id = p.id
	INNER JOIN menu m ON m.id = po.menu_id
WHERE gender = 'female'
	AND m.pizza_name LIKE 'cheese%'