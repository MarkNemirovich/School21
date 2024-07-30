WITH person_renamed AS (
    SELECT 
        id AS person_id,
        name, 
        age, 
        gender, 
        address 
    FROM person
)
SELECT 
    person_order.order_date, 
    person_renamed.name || ' (age:' || person_renamed.age || ')' AS person_information
FROM person_order
NATURAL JOIN person_renamed
ORDER BY person_order.order_date, person_information;
