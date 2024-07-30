INSERT INTO person_discounts (id, person_id, pizzeria_id, discount)
SELECT ROW_NUMBER() OVER () AS id,
	person_id,
	pizzeria_id,
	CASE
		WHEN COUNT(*) = 1 THEN 10.5
		WHEN COUNT(*) = 2 THEN 22
		ELSE 30
	END
FROM person_order po
	INNER JOIN menu m ON m.id = po.menu_id
	INNER JOIN pizzeria p ON p.id = m.pizzeria_id
GROUP BY person_id,
	pizzeria_id;