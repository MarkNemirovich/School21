SELECT 
    person.id AS "person.id",
    person.name AS "person.name",
    person.age AS "age",
    person.gender AS "gender",
    person.address AS "address",
    pizzeria.id AS "pizzeria.id",
    pizzeria.name AS "pizzeria.name",
    pizzeria.rating AS "rating"
FROM 
    person, pizzeria;

--SELECT person.*,  pizzeria.* FROM person, pizzeria