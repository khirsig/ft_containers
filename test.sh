mkdir -p tester_results/diff
mkdir -p tester_results/output
make
./ft_vector  > tester_results/output/ft_vector.txt
./std_vector > tester_results/output/std_vector.txt
diff -u tester_results/output/ft_vector.txt tester_results/output/std_vector.txt > tester_results/diff/vector.diff

if [ $? == 0 ]; then
	echo "Vector: \033[32;1mOK\033[0m"
else
	echo "Vector: \033[31;1mKO\033[0m"
fi

./ft_map  > tester_results/output/ft_map.txt
./std_map > tester_results/output/std_map.txt
diff -u tester_results/output/ft_map.txt tester_results/output/std_map.txt > tester_results/diff/map.diff

if [ $? == 0 ]; then
	echo "Map:    \033[32;1mOK\033[0m"
else
	echo "Map:    \033[31;1mKO\033[0m"
fi

./ft_stack  > tester_results/output/ft_stack.txt
./std_stack > tester_results/output/std_stack.txt
diff -u tester_results/output/ft_stack.txt tester_results/output/std_stack.txt > tester_results/diff/stack.diff

if [ $? == 0 ]; then
	echo "Stack:  \033[32;1mOK\033[0m"

else
	echo "Stack:  \033[31;1mKO\033[0m"
fi

./ft_set  > tester_results/output/ft_set.txt
./std_set > tester_results/output/std_set.txt
diff -u tester_results/output/ft_set.txt tester_results/output/std_set.txt > tester_results/diff/set.diff

if [ $? == 0 ]; then
	echo "Set:    \033[32;1mOK\033[0m"

else
	echo "Set:    \033[31;1mKO\033[0m"
fi

make fclean