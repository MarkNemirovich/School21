SELECT pi.name,
	COUNT(*) as count_of_orders,
	ROUND(AVG(m.price), 2) as average_price,
	MAX(m.price) as max_price,
	MIN(m.price) as min_price
FROM person_order po
	INNER JOIN menu m ON m.id = po.menu_id
	INNER JOIN pizzeria pi ON pi.id = m.pizzeria_id
GROUP BY pi.name
ORDER BY pi.name;