mv door_management_fi door_management_files
cd door_management_files
mkdir door_configuration
mkdir door_map
mkdir door_logs
mv door_map_1.1 door_map
mv *.conf door_configuration
mv *.log door_logs
cd ..
sh ai_door_management_module.sh