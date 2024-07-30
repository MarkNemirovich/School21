SELECT pe.name,
	m.pizza_name,
	m.price,
	ROUND(m.price *(100 - pd.discount) / 100) as discount_price,
	pi.name
FROM person_discounts pd
	INNER JOIN person pe ON pe.id = pd.person_id
	INNER JOIN pizzeria pi ON pi.id = pd.pizzeria_id
	INNER JOIN menu m ON m.pizzeria_id = pi.id
ORDER BY pe.name,
	pi.name;