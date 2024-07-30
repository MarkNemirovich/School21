SELECT p.address,
	pi.name,
	COUNT(*) AS count_of_orders
FROM person_order po
INNER JOIN person p ON p.id = po.person_id
INNER JOIN menu m ON m.id = po.menu_id
INNER JOIN pizzeria pi ON pi.id = m.pizzeria_id
GROUP BY p.address, pi.name
ORDER BY address, pi.name;