SELECT 
	person.name as "person_name",
	menu.pizza_name as "pizza_name",
	pizzeria.name as "pizzeria_name"
FROM person_order
INNER JOIN person ON person.id = person_order.person_id
INNER JOIN menu ON menu.id = person_order.menu_id
INNER JOIN pizzeria ON menu.pizzeria_id = menu.pizzeria_id
ORDER BY person_name, pizza_name, pizzeria_name;