WITH male_visits AS (
    SELECT
        pizzeria.id AS pizzeria_id,
        pizzeria.name AS pizzeria_name,
        person.gender
    FROM pizzeria
    INNER JOIN menu ON menu.pizzeria_id = pizzeria.id
    INNER JOIN person_order ON menu.id = person_order.menu_id
    INNER JOIN person ON person_order.person_id = person.id
	WHERE person.gender = 'male'
    GROUP BY pizzeria.id, pizzeria_name, person.gender
),
female_visits AS (
    SELECT
        pizzeria.id AS pizzeria_id,
        pizzeria.name AS pizzeria_name,
        person.gender
    FROM pizzeria
    INNER JOIN menu ON menu.pizzeria_id = pizzeria.id
    INNER JOIN person_order ON menu.id = person_order.menu_id
    INNER JOIN person ON person_order.person_id = person.id
	WHERE person.gender = 'female'
    GROUP BY pizzeria.id, pizzeria_name, person.gender
)
SELECT pizzeria_name FROM male_visits
EXCEPT
SELECT pizzeria_name FROM female_visits
UNION ALL
SELECT pizzeria_name FROM female_visits
EXCEPT
SELECT pizzeria_name FROM male_visits
ORDER BY pizzeria_name;