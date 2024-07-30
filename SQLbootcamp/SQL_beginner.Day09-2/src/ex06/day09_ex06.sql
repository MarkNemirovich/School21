CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date (
		IN pperson VARCHAR DEFAULT 'Dmitriy',
		IN pprice NUMERIC DEFAULT 500,
		IN pdate DATE DEFAULT '2022-01-08'
	) RETURNS TABLE(pizzeria_name VARCHAR) AS $$ BEGIN RETURN QUERY
SELECT DISTINCT pz.name
FROM person_visits v
	INNER JOIN person p ON v.person_id = p.id
	INNER JOIN pizzeria pz ON v.pizzeria_id = pz.id
	INNER JOIN menu m ON pz.id = m.pizzeria_id
WHERE p.name = pperson
	AND v.visit_date = pdate
	AND m.price < pprice;
END;
$$ LANGUAGE plpgsql;
--
select *
from fnc_person_visits_and_eats_on_date(pprice := 800);
select *
from fnc_person_visits_and_eats_on_date(
		pperson := 'Anna',
		pprice := 1300,
		pdate := '2022-01-01'
	);