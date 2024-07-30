SELECT DISTINCT person_order.order_date AS action_date, person.name
FROM person_order
INNER JOIN person
ON person.id = person_order.person_id
WHERE (person_order.order_date, person_order.person_id) IN (
    SELECT DISTINCT visit_date, person_id
    FROM person_visits
)
ORDER BY action_date ASC, person.name DESC;