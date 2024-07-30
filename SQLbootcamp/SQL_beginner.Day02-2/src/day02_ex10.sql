WITH person1 AS (
SELECT id, name, address FROM person
),
person2 AS (
SELECT id, name, address FROM person
)
SELECT
	person1.name,
	person2.name,	
	person1.address
FROM person1
INNER JOIN person2 ON person1.address = person2.address
WHERE person1.id > person2.id -- чтобы не было обратного дублирования