set terminal png size 800,600

# Melhor caso de todos os algoritmos
set output 'all_best_cases.png'
set title "Best Case Search Times for Binary and AVL Algorithms"
set xlabel "Vector Size"
set ylabel "Execution Time (microseconds)"
set grid
plot 'binary_best_case_time.txt' using 1:2 with lines title 'Binary Tree Best', \
     'avl_best_case.txt' using 1:2 with lines title 'AVL Tree Best'

# Caso médio de todos os algoritmos
set output 'all_average_cases.png'
set title "Average Case Search Times for Binary, AVL, and Hash Algorithms"
set xlabel "Vector Size"
set ylabel "Execution Time (microseconds)"
set grid
plot 'binary_average_case_time.txt' using 1:2 with lines title 'Binary Tree Average', \
     'avl_average_case.txt' using 1:2 with lines title 'AVL Tree Average', \
     'hash_average_case.txt' using 1:2 with lines title 'Hash Table Average'

# Pior caso de todos os algoritmos
set output 'all_worst_cases.png'
set title "Worst Case Search Times for Binary, AVL, and Hash Algorithms"
set xlabel "Vector Size"
set ylabel "Execution Time (microseconds)"
set grid
plot 'binary_worst_case_time.txt' using 1:2 with lines title 'Binary Tree Worst', \
     'avl_worst_case.txt' using 1:2 with lines title 'AVL Tree Worst', \
     'hash_worst_case.txt' using 1:2 with lines title 'Hash Table Worst'

# Comparação de todos os casos
set output 'all_cases_comparison.png'
set title "Comparison of Search Times for Binary, AVL, and Hash Algorithms"
set xlabel "Vector Size"
set ylabel "Execution Time (microseconds)"
set grid
plot 'binary_best_case_time.txt' using 1:2 with lines title 'Binary Tree Best', \
     'binary_average_case_time.txt' using 1:2 with lines title 'Binary Tree Average', \
     'binary_worst_case_time.txt' using 1:2 with lines title 'Binary Tree Worst', \
     'avl_best_case.txt' using 1:2 with lines title 'AVL Tree Best', \
     'avl_average_case.txt' using 1:2 with lines title 'AVL Tree Average', \
     'avl_worst_case.txt' using 1:2 with lines title 'AVL Tree Worst', \
     'hash_average_case.txt' using 1:2 with lines title 'Hash Table Average', \
     'hash_worst_case.txt' using 1:2 with lines title 'Hash Table Worst'

# Comparação de todos os casos exceto o caso médio e pior do Binary
set output 'all_cases_excluding_binary_avg_worst.png'
set title "Search Times Excluding Binary Tree Average and Worst"
set xlabel "Vector Size"
set ylabel "Execution Time (microseconds)"
set grid
plot 'binary_best_case_time.txt' using 1:2 with lines title 'Binary Tree Best', \
     'avl_best_case.txt' using 1:2 with lines title 'AVL Tree Best', \
     'avl_average_case.txt' using 1:2 with lines title 'AVL Tree Average', \
     'avl_worst_case.txt' using 1:2 with lines title 'AVL Tree Worst', \
     'hash_average_case.txt' using 1:2 with lines title 'Hash Table Average', \
     'hash_worst_case.txt' using 1:2 with lines title 'Hash Table Worst'
