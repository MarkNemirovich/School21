WITH balance_with_date_in_cur AS (
    SELECT
        b.user_id,
        b.money,
        b.currency_id,
        COALESCE(
            (
                SELECT
                    MAX(currency.updated)
                FROM
                    currency
                WHERE
                    b.currency_id = currency.id
                    AND currency.updated <= b.updated
            ),
            (
                SELECT
                    MIN(currency.updated)
                FROM
                    currency
                WHERE
                    b.currency_id = currency.id
                    AND currency.updated > b.updated
            )
        ) AS updated
    FROM
        balance b
)
SELECT
    COALESCE(u.name, 'not defined') AS name,
    COALESCE(u.lastname, 'not defined') AS lastname,
    c.name AS currency_name,
    bwdic.money * c.rate_to_usd AS currency_in_usd
FROM
    balance_with_date_in_cur bwdic
    JOIN currency c ON (
        bwdic.updated = c.updated
        AND bwdic.currency_id = c.id
    )
    LEFT JOIN public."user" u ON bwdic.user_id = u.id
ORDER BY
    name DESC,
    lastname,
    currency_name;