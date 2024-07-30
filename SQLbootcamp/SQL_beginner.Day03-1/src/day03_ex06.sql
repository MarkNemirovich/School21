WITH pizza_names AS (
	SELECT DISTINCT menu.pizza_name, menu.price, menu.pizzeria_id, pizzeria.name as pizzeria_name
	FROM menu 
	INNER JOIN pizzeria ON pizzeria.id = menu.pizzeria_id)
SELECT menu.pizza_name, pizzeria.name as pizzeria_name_1, pizza_names.pizzeria_name as pizzeria_name_2, menu.price FROM menu
INNER JOIN pizza_names ON menu.pizza_name = pizza_names.pizza_name
	INNER JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
WHERE menu.price = pizza_names.price AND menu.pizzeria_id > pizza_names.pizzeria_id -- != will create duplicates
ORDER BY menu.pizza_name