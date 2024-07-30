DROP INDEX IF EXISTS idx_person_discounts_unique;
CREATE UNIQUE INDEX IF NOT EXISTS idx_person_discounts_unique ON person_discounts USING BTREE (person_id, pizzeria_id);
set enable_seqscan = off;
set enable_indexscan = on;
EXPLAIN ANALYZE
SELECT *
FROM person_discounts pd
	INNER JOIN person pe ON pe.id = pd.person_id
	INNER JOIN pizzeria pi ON pi.id = pd.pizzeria_id
ORDER BY pe.name,
	pi.name;

explain analyse select * from person_discounts where person_id = 1 and pizzeria_id=12;