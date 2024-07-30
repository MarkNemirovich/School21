WITH dominos_id AS (
    SELECT id AS pizzeria_id FROM pizzeria WHERE name = 'Dominos'
), sicilian_id AS (
    SELECT id AS pizza_id FROM menu 
	INNER JOIN dominos_id ON dominos_id.pizzeria_id = menu.pizzeria_id
	WHERE pizza_name = 'sicilian pizza'
),
person_ids AS (
    SELECT id AS person_id, name FROM person WHERE name IN ('Denis', 'Irina')
),
new_ids AS (
    SELECT 
        person_id,
        (SELECT MAX(id) FROM person_order) + ROW_NUMBER() OVER (ORDER BY person_id) AS new_id
    FROM person_ids
)
INSERT INTO person_order (id, person_id, menu_id, order_date)
SELECT 
    new_id,
    person_id, 
    sicilian_id.pizza_id, 
    '2022-02-24'
FROM new_ids, sicilian_id
WHERE new_ids.person_id IN (SELECT id FROM person WHERE name IN ('Denis', 'Irina'));