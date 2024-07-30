WITH person AS (
    SELECT
        id,
        COALESCE(name, 'not defined') AS name,
        COALESCE(lastname, 'not defined') AS lastname
    FROM
        public.user
),
person_balance AS (
    SELECT
        COALESCE(person.name, 'not defined') AS name,
        COALESCE(person.lastname, 'not defined') AS lastname,
        balance.type,
        SUM(balance.money) AS volume,
        balance.currency_id
    FROM
        balance FULL
        JOIN person ON person.id = balance.user_id
    GROUP BY
        person.name,
        person.lastname,
        balance.type,
        balance.currency_id
),
currency_last AS (
    SELECT
        DISTINCT ON (currency.id) currency.id,
        currency.name AS currency_name,
        currency.rate_to_usd AS last_rate_to_usd
    FROM
        currency
    ORDER BY
        currency.id,
        currency.updated DESC
)
SELECT
    person_balance.name,
    person_balance.lastname,
    person_balance.type,
    person_balance.volume,
    COALESCE(currency_last.currency_name, 'not defined') AS currency_name,
    COALESCE(currency_last.last_rate_to_usd, 1) AS last_rate_to_usd,
    person_balance.volume * COALESCE(currency_last.last_rate_to_usd, 1) AS total_volume_in_usd
FROM
    person_balance FULL
    JOIN currency_last ON currency_last.id = person_balance.currency_id
ORDER BY
    person_balance.name DESC,
    person_balance.lastname ASC,
    person_balance.type ASC;