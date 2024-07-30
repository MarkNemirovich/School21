CREATE OR REPLACE FUNCTION fnc_fibonacci(IN pstop INTEGER default 10) RETURNS TABLE (fibonacci INTEGER) AS $$
DECLARE a INTEGER := 0;
b INTEGER := 1;
fib INTEGER;
BEGIN RETURN QUERY
SELECT a;
WHILE b < pstop LOOP RETURN QUERY
SELECT b;
fib := a + b;
a := b;
b := fib;
END LOOP;
END;
$$ LANGUAGE plpgsql;
--
select *
from fnc_fibonacci(100);
select *
from fnc_fibonacci();