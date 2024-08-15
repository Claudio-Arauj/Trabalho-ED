# plot_hash_table_cases.gnu

set terminal png size 800,600

# Caso médio
set output 'hash_table_average_case.png'
set title "Average Case Search Time for Hash Table"
set xlabel "Search"
set ylabel "Time (microseconds)"
set grid
plot 'hash_average_case.txt' using 1:2 with lines title 'Average Case'

# Pior caso
set output 'hash_table_worst_case.png'
set title "Worst Case Search Time for Hash Table"
set xlabel "Search"
set ylabel "Time (microseconds)"
set grid
plot 'hash_worst_case.txt' using 1:2 with lines title 'Worst Case'

# Comparação
set output 'hash_table_comparison.png'
set title "Comparison of Search Times for Hash Table"
set xlabel "Search"
set ylabel "Time (microseconds)"
set grid
plot 'hash_average_case.txt' using 1:2 with lines title 'Average Case', \
     'hash_worst_case.txt' using 1:2 with lines title 'Worst Case'
