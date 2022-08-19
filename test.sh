mkdir -p tests
mkdir -p tests/diff
mkdir -p tests/output
make
./ft_vector  > tests/output/ft_vector.txt
./std_vector > tests/output/std_vector.txt
diff -u tests/output/ft_vector.txt tests/output/std_vector.txt > tests/diff/vector.diff
./ft_map  > tests/output/ft_map.txt
./std_map > tests/output/std_map.txt
diff -u tests/output/ft_map.txt tests/output/std_map.txt > tests/diff/map.diff
make fclean