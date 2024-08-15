# plot_binary_tree_cases.gnu

set terminal png size 800,600

# Melhor caso
set output 'binary_tree_best_case.png'
set title "Best Case Search Time for Binary Tree"
set xlabel "Search"
set ylabel "Time (microseconds)"
set grid
plot 'binary_best_case_time.txt' using 1:2 with lines title 'Best Case'

# Caso médio
set output 'binary_tree_average_case.png'
set title "Average Case Search Time for Binary Tree"
set xlabel "Search"
set ylabel "Time (microseconds)"
set grid
plot 'binary_average_case_time.txt' using 1:2 with lines title 'Average Case'

# Pior caso
set output 'binary_tree_worst_case.png'
set title "Worst Case Search Time for Binary Tree"
set xlabel "Search"
set ylabel "Time (microseconds)"
set grid
plot 'binary_worst_case_time.txt' using 1:2 with lines title 'Worst Case'

# Comparação
set output 'binary_tree_comparison.png'
set title "Comparison of Search Times for Binary Tree"
set xlabel "Search"
set ylabel "Time (microseconds)"
set grid
plot 'binary_best_case_time.txt' using 1:2 with lines title 'Best Case', \
     'binary_average_case_time.txt' using 1:2 with lines title 'Average Case', \
     'binary_worst_case_time.txt' using 1:2 with lines title 'Worst Case'
