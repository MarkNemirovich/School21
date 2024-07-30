SELECT 
	menu.pizza_name as pizza_name, 
	menu.price,
	pizzeria.name as pizzeria_name
FROM menu
LEFT JOIN person_order ON person_order.menu_id = menu.id
LEFT JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
WHERE person_order.id is NULL
ORDER BY pizza_name, price