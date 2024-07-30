SELECT name, 
CASE WHEN name = 'Denis' THEN 'true'
ELSE 'false' END as check_name
FROM person
WHERE id = (
    SELECT person_id
    FROM person_order
    WHERE menu_id = 13 AND order_date = '2022-01-07'
) OR id = (
    SELECT person_id
    FROM person_order
    WHERE menu_id = 14 AND order_date = '2022-01-07'
) OR id = (
    SELECT person_id
    FROM person_order
    WHERE menu_id = 18 AND order_date = '2022-01-07'
); -- бред какой-то, через IN или CTE, или JOIN это сделать куда лучше
