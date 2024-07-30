DROP TABLE IF EXISTS person_discounts;
CREATE TABLE person_discounts (
	id bigint PRIMARY KEY,
	person_id bigint not null,
	pizzeria_id bigint not null,
	discount numeric not null default 0,
	constraint fk_person_discounts_person_id foreign key (person_id) references person(id),
	constraint fk_person_discounts_pizzeria_id foreign key (pizzeria_id) references pizzeria(id)
);

SELECT * FROM person_discounts;