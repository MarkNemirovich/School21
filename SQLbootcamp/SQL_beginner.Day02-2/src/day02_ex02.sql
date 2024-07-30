WITH d AS (
    SELECT generate_series('2022-01-01'::date, '2022-01-03'::date, '1 day'::interval) AS day
)
SELECT 
    person_name, 
    visit_date, 
    pizzeria_name
FROM (
    SELECT DISTINCT
        COALESCE(p.name, '-') AS person_name,
        d.day::date AS visit_date,
        COALESCE(pz.name, '-') AS pizzeria_name
    FROM d
    INNER JOIN person_visits v ON v.visit_date = d.day
    FULL JOIN person p ON v.person_id = p.id 
    FULL JOIN pizzeria pz ON v.pizzeria_id = pz.id
) AS subquery
ORDER BY person_name, visit_date, pizzeria_name;
