WITH max_pizza_id AS (
    SELECT MAX(id) + 1 AS new_pizza_id FROM menu
)
INSERT INTO menu (id, pizzeria_id, pizza_name, price)
SELECT max_pizza_id.new_pizza_id, 2, 'sicilian pizza', 900
FROM max_pizza_id