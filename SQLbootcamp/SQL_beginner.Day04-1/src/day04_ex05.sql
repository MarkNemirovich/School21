--DROP VIEW v_price_with_discount;
CREATE OR REPLACE VIEW v_price_with_discount AS
SELECT 
	person.name, 
	menu.pizza_name, 
	menu.price, 
	(0.9*menu.price)::int as discount_price
FROM person_order
INNER JOIN menu ON menu.id = person_order.menu_id
INNER JOIN person ON person.id = person_order.person_id
ORDER BY person.name, menu.pizza_name;