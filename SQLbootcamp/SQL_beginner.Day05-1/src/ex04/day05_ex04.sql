CREATE UNIQUE INDEX IF NOT EXISTS idx_menu_unique ON menu USING BTREE (pizzeria_id, pizza_name);
set enable_seqscan = off;
set enable_indexscan = on;
EXPLAIN ANALYZE
SELECT pizzeria_id,
	pizza_name
FROM menu 
-- Статья с этим заданием и примером:
	-- https://habr.com/ru/companies/quadcode/articles/696498/