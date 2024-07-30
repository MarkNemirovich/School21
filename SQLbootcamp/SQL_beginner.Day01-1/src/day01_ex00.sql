SELECT id, pizza_name as object_name FROM menu
UNION
SELECT id, name as object_name FROM person
ORDER BY id ASC, object_name;