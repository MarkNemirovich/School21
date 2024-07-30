SELECT DISTINCT order_date AS action_date, person_id
FROM person_order
WHERE (order_date, person_id) IN (
    SELECT DISTINCT visit_date, person_id
    FROM person_visits
)
ORDER BY action_date ASC, person_id DESC;