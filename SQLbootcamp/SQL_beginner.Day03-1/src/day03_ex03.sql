WITH male_visits AS (
    SELECT pizzeria.id AS pizzeria_id,
        pizzeria.name AS pizzeria_name,
        person.gender,
        COUNT(*) AS visit_count
    FROM pizzeria
        INNER JOIN person_visits ON pizzeria.id = person_visits.pizzeria_id
        INNER JOIN person ON person_visits.person_id = person.id
    WHERE person.gender = 'male'
    GROUP BY pizzeria.id,
        pizzeria_name,
        person.gender
),
female_visits AS (
    SELECT pizzeria.id AS pizzeria_id,
        pizzeria.name AS pizzeria_name,
        person.gender,
        COUNT(*) AS visit_count
    FROM pizzeria
        INNER JOIN person_visits ON pizzeria.id = person_visits.pizzeria_id
        INNER JOIN person ON person_visits.person_id = person.id
    WHERE person.gender = 'female'
    GROUP BY pizzeria.id,
        pizzeria_name,
        person.gender
)
SELECT pizzeria_name
FROM male_visits
WHERE visit_count = (
        SELECT MAX(visit_count)
        FROM male_visits
    )
UNION ALL
SELECT pizzeria_name
FROM female_visits
WHERE visit_count = (
        SELECT MAX(visit_count)
        FROM female_visits
    )
ORDER BY pizzeria_name


 /*   (select p2.name as pizzeria_name from person p inner join person_visits pv on p.id = pv.person_id inner join pizzeria p2 on p2.id = pv.pizzeria_id where p.gender = 'female' except all select p2.name from person p inner join person_visits pv on p.id = pv.person_id inner join pizzeria p2 on p2.id = pv.pizzeria_id where p.gender = 'male') union all (select p2.name from person p inner join person_visits pv on p.id = pv.person_id inner join pizzeria p2 on p2.id = pv.pizzeria_id where p.gender = 'male' except all select p2.name from person p inner join person_visits pv on p.id = pv.person_id inner join pizzeria p2 on p2.id = pv.pizzeria_id where p.gender = 'female') order by 1*/