CREATE OR REPLACE FUNCTION fnc_trg_person_update_audit() RETURNS TRIGGER AS $$ BEGIN
INSERT INTO person_audit (
		created,
		type_event,
		row_id,
		name,
		age,
		gender,
		address
	)
VALUES (
		current_timestamp,
		'U',
		NEW.id,
		NEW.name,
		NEW.age,
		NEW.gender,
		NEW.address
	);
RETURN NEW;
END;
--
$$ LANGUAGE plpgsql;
CREATE TRIGGER trg_person_update_audit
AFTER
UPDATE ON person FOR EACH ROW EXECUTE FUNCTION fnc_trg_person_update_audit();
--
UPDATE person
SET name = 'Damir'
WHERE id = 10;
UPDATE person
SET name = 'Bulat'
WHERE id = 10;