WITH g AS (
	SELECT person_id,
	COUNT(*) AS count_of_visits
FROM person_visits
GROUP BY person_id
HAVING COUNT(*) > 3
)
SELECT p.name,
	g.count_of_visits
	FROM g
	INNER JOIN person p ON p.id = g.person_id
ORDER BY count_of_visits DESC, p.name;