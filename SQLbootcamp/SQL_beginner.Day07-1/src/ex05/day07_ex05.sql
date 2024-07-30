SELECT DISTINCT p.name
FROM person p
	JOIN person_order o ON p.id = o.person_id
ORDER BY p.name;