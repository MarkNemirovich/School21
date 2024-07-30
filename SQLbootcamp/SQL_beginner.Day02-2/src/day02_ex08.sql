SELECT DISTINCT
	person.name
FROM person_order
CROSS JOIN menu
INNER JOIN person ON person_order.menu_id = menu.id AND person.id = person_order.person_id
WHERE (menu.pizza_name LIKE '%mushroom%' OR  menu.pizza_name LIKE '%pepperoni%')
AND person.gender = 'male' 
AND (person.address = 'Moscow' OR person.address = 'Samara')
ORDER BY person.name DESC