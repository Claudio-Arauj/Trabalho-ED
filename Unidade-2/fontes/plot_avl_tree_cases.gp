# plot_avl_tree_cases.gnu

set terminal png size 800,600

# Melhor caso
set output 'avl_tree_best_case.png'
set title "Best Case Search Time for AVL Tree"
set xlabel "Search"
set ylabel "Time (microseconds)"
set grid
plot 'avl_best_case.txt' using 1:2 with lines title 'Best Case'

# Caso médio
set output 'avl_tree_average_case.png'
set title "Average Case Search Time for AVL Tree"
set xlabel "Search"
set ylabel "Time (microseconds)"
set grid
plot 'avl_average_case.txt' using 1:2 with lines title 'Average Case'

# Pior caso
set output 'avl_tree_worst_case.png'
set title "Worst Case Search Time for AVL Tree"
set xlabel "Search"
set ylabel "Time (microseconds)"
set grid
plot 'avl_worst_case.txt' using 1:2 with lines title 'Worst Case'

# Comparação
set output 'avl_tree_comparison.png'
set title "Comparison of Search Times for AVL Tree"
set xlabel "Search"
set ylabel "Time (microseconds)"
set grid
plot 'avl_best_case.txt' using 1:2 with lines title 'Best Case', \
     'avl_average_case.txt' using 1:2 with lines title 'Average Case', \
     'avl_worst_case.txt' using 1:2 with lines title 'Worst Case'
