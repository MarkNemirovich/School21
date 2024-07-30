CREATE OR REPLACE FUNCTION func_minimum (IN arr NUMERIC[]) RETURNS NUMERIC AS $$
DECLARE min_value NUMERIC;
BEGIN
SELECT MIN(unnested) INTO min_value
FROM UNNEST(arr) AS unnested;
RETURN min_value;
END;
$$ LANGUAGE plpgsql;
--
SELECT func_minimum(VARIADIC arr => ARRAY [10.0, -1.0, 5.0, 4.4]);