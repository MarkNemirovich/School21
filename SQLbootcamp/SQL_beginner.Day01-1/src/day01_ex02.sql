WITH RankedPizzas AS (
    SELECT 
		pizza_name,
        ROW_NUMBER() OVER (PARTITION BY pizza_name ORDER BY pizza_name DESC) AS row_num
    FROM menu
)
SELECT pizza_name FROM RankedPizzas
WHERE row_num = 1
ORDER BY pizza_name DESC;
