CREATE INDEX IF NOT EXISTS idx_person_order_multi ON person_order USING BTREE (person_id, menu_id) INCLUDE (order_date);
set enable_seqscan = off;
set enable_indexscan = on;
EXPLAIN ANALYZE
SELECT person_id,
	menu_id,
	order_date
FROM person_order
WHERE person_id = 8
	AND menu_id = 19;
-- Статья с этим заданием и примером:
-- https://habr.com/ru/companies/quadcode/articles/696498/