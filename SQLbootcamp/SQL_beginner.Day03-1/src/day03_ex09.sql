WITH dominos_id AS (
    SELECT id AS pizzeria_id FROM pizzeria WHERE name = 'Dominos'
),
person_ids AS (
    SELECT id AS person_id, name FROM person WHERE name IN ('Denis', 'Irina')
),
new_ids AS (
    SELECT 
        person_id,
        (SELECT MAX(id) FROM person_visits) + ROW_NUMBER() OVER (ORDER BY person_id) AS new_id
    FROM person_ids
)
INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date)
SELECT 
    new_id,
    person_id, 
    dominos_id.pizzeria_id, 
    '2022-02-24'
FROM new_ids, dominos_id
WHERE new_ids.person_id IN (SELECT id FROM person WHERE name IN ('Denis', 'Irina'));
