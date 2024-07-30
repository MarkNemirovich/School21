CREATE OR REPLACE FUNCTION fnc_persons_male() RETURNS TABLE(
		id bigint,
		name varchar,
		age integer,
		gender varchar,
		address varchar
	) AS $$
SELECT id,
	name,
	age,
	gender,
	address
FROM person
WHERE gender = 'male';
$$ LANGUAGE sql;
CREATE OR REPLACE FUNCTION fnc_persons_female() RETURNS TABLE(
		id bigint,
		name varchar,
		age integer,
		gender varchar,
		address varchar
	) AS $$
SELECT id,
	name,
	age,
	gender,
	address
FROM person
WHERE gender = 'female';
$$ LANGUAGE sql;
--
SELECT *
FROM fnc_persons_male();
SELECT *
FROM fnc_persons_female();