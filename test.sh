make test
mkdir -p test
./ft_test  > test/ft_test.txt
./std_test > test/std_test.txt
diff test/ft_test.txt test/std_test.txt > test/diff.txt
make fclean