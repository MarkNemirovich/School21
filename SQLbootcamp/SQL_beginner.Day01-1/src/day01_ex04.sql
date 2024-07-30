SELECT person_order.person_id - person_visits.person_id as person_id
FROM person_order, person_visits
WHERE person_order.order_date = '2022-01-07'
and person_visits.visit_date = '2022-01-07'; 