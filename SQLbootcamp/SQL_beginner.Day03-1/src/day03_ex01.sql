SELECT menu.id as menu_id FROM menu
LEFT JOIN person_order ON person_order.menu_id = menu.id
WHERE person_order.id is NULL
ORDER BY menu_id