WITH data_generator AS (
	SELECT gs::date AS generated_date
	FROM generate_series('2022-01-01', '2022-01-10', INTERVAL '1 day') AS gs
)
SELECT dg.generated_date AS missing_date
FROM data_generator dg
LEFT JOIN (
	SELECT visit_date
	FROM person_visits
	WHERE person_id = 1
		OR person_id = 2
) AS pv ON dg.generated_date = pv.visit_date
WHERE pv.visit_date IS NULL
ORDER BY missing_date;