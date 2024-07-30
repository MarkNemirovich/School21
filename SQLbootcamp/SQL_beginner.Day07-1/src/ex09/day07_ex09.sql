SELECT p.address,
	ROUND(MAX(p.age) - (MIN(p.age)::numeric / MAX(p.age)), 2) AS formula,
	ROUND(AVG(p.age), 2) AS average,
	ROUND(MAX(p.age) - (MIN(p.age)::numeric / MAX(p.age)), 2) > AVG(age) AS comparison
FROM person p
GROUP BY address
ORDER BY address;