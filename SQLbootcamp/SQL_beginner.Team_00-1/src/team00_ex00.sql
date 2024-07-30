DROP VIEW IF EXISTS v_combinations, v_tours;
DROP TABLE IF EXISTS graph;
CREATE TABLE IF NOT EXISTS graph(
	point1 varchar NOT NULL,
	point2 varchar NOT NULL,
	cost integer NOT NULL
);

INSERT INTO graph(point1, point2, cost)
VALUES
('a', 'b', 10),
('a', 'c', 15),
('a', 'd', 20),
('b', 'a', 10),
('b', 'c', 35),
('b', 'd', 25),
('c', 'a', 15),
('c', 'b', 35),
('c', 'd', 30),
('d', 'a', 20),
('d', 'b', 25),
('d', 'c', 30);

CREATE OR REPLACE RECURSIVE VIEW v_combinations (direction, point1, point2, cost) AS
	SELECT
		point1 AS direction,
		point1,
		point2,
		cost
	FROM graph
	WHERE point1 = 'a'
	UNION ALL
	SELECT
	(c.direction || ',' || g.point1) as direction,
	g.point1,
	g.point2,
	c.cost + g.cost
		FROM v_combinations c
	INNER JOIN graph g ON c.point2 = g.point1
	WHERE direction NOT LIKE ('%' || g.point1 || '%');
	
SELECT * FROM v_combinations;

CREATE OR REPLACE VIEW v_tours (total_cost, tour) AS
SELECT 
	cost as total_cost,
	('{' || direction || ',' || point2 || '}') as tour
	FROM v_combinations
	WHERE LENGTH(direction) = 7 
	AND point2 = 'a';

SELECT * FROM v_tours;

WITH min AS (SELECT MIN(total_cost) min_cost FROM v_tours)
SELECT * FROM v_tours
INNER JOIN min ON min.min_cost = v_tours.total_cost
ORDER BY total_cost, tour