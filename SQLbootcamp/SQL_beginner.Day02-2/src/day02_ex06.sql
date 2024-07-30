SELECT m.pizza_name, pz.name AS pizzeria_name 
FROM person_order AS po 
INNER JOIN person p ON p.id = po.person_id 
INNER JOIN menu m ON m.id = po.menu_id 
INNER JOIN pizzeria pz ON m.pizzeria_id = pz.id 
WHERE p.name IN ('Denis', 'Anna') 
ORDER BY 1, 2;