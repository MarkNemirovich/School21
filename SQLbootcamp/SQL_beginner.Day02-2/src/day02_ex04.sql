SELECT 
	menu.pizza_name, 
	pizzeria.name as pizzeria_name, 
	menu.price 
FROM menu
INNER JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
WHERE menu.pizza_name LIKE '%mushroom%' OR  menu.pizza_name LIKE '%pepperoni%'
ORDER BY menu.pizza_name, pizzeria_name