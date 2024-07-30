WITH greek_pizza_id AS (
    SELECT id FROM menu WHERE pizza_name = 'greek pizza'
),
person_ids AS (
    SELECT id AS person_id FROM person
),
max_id AS (
    SELECT MAX(id) AS max_id FROM person_order
),
new_ids AS (
    SELECT 
		max_id.max_id + person_ids.person_id AS new_id, 
		person_ids.person_id
    FROM person_ids
    CROSS JOIN max_id
)
INSERT INTO person_order (id, person_id, menu_id, order_date)
SELECT new_ids.new_id, new_ids.person_id, greek_pizza_id.id, '2022-02-25'
FROM new_ids, greek_pizza_id;
