CREATE UNIQUE INDEX IF NOT EXISTS idx_person_order_order_date ON person_order USING BTREE (person_id, menu_id)
WHERE order_date = '2022-01-01';
set enable_seqscan = off;
set enable_indexscan = on;
EXPLAIN ANALYZE
SELECT person_id,
	menu_id
FROM person_order 
-- Статья c примером:
	-- https://www.postgresql.org/docs/current/indexes-partial.html