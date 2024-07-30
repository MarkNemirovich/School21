CREATE INDEX IF NOT EXISTS idx_person_name ON person USING BTREE (UPPER(name));
set enable_seqscan = off;
set enable_indexscan = on;
EXPLAIN ANALYZE
SELECT *
FROM person
WHERE UPPER(name) = 'KATE';
-- Статья с этим заданием и примером:
-- https://habr.com/ru/companies/quadcode/articles/696498/