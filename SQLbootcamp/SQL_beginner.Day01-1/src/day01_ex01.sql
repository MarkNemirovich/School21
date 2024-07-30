SELECT * FROM (
  SELECT name as object_name FROM person
  ORDER BY object_name
) AS persons
UNION ALL
SELECT * FROM (
  SELECT pizza_name as object_name FROM menu
  ORDER BY object_name
) AS pizzas
ORDER BY object_name;
