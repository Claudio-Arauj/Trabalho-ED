# Define o terminal de saída e o tamanho do gráfico
set terminal pngcairo size 800,600 enhanced font 'Verdana,10'

# Define a saída para o gráfico de Distribution Sort
set output 'graficos/distribution_sort.png'
set title "Tempo de Execução do Distribution Sort"
set xlabel "Tamanho do Array"
set ylabel "Tempo Médio de Execução (microssegundos)"
set grid
plot 'graficos/distribution_a_time.txt' using 1:2 with linespoints title 'Distribution Sort'

# Define a saída para o gráfico de Insertion Sort (Caso Médio)
set output 'graficos/insertion_sort_a.png'
set title "Tempo de Execução do Insertion Sort (Caso Médio)"
set xlabel "Tamanho do Array"
set ylabel "Tempo Médio de Execução (microssegundos)"
set grid
plot 'graficos/insertion_a_time.txt' using 1:2 with linespoints title 'Insertion Sort (Caso Médio)'

# Define a saída para o gráfico de Insertion Sort (Melhor Caso)
set output 'graficos/insertion_sort_b.png'
set title "Tempo de Execução do Insertion Sort (Melhor Caso)"
set xlabel "Tamanho do Array"
set ylabel "Tempo Médio de Execução (microssegundos)"
set grid
plot 'graficos/insertion_b_time.txt' using 1:2 with linespoints title 'Insertion Sort (Melhor Caso)'

# Define a saída para o gráfico de Insertion Sort (Pior Caso)
set output 'graficos/insertion_sort_w.png'
set title "Tempo de Execução do Insertion Sort (Pior Caso)"
set xlabel "Tamanho do Array"
set ylabel "Tempo Médio de Execução (microssegundos)"
set grid
plot 'graficos/insertion_w_time.txt' using 1:2 with linespoints title 'Insertion Sort (Pior Caso)'

# Define a saída para o gráfico de Merge Sort
set output 'graficos/merge_sort.png'
set title "Tempo de Execução do Merge Sort"
set xlabel "Tamanho do Array"
set ylabel "Tempo Médio de Execução (microssegundos)"
set grid
plot 'graficos/merge_a_time.txt' using 1:2 with linespoints title 'Merge Sort'

# Define a saída para o gráfico de Quick Sort (Caso Médio)
set output 'graficos/quick_sort_a.png'
set title "Tempo de Execução do Quick Sort (Caso Médio)"
set xlabel "Tamanho do Array"
set ylabel "Tempo Médio de Execução (microssegundos)"
set grid
plot 'graficos/quick_a_time.txt' using 1:2 with linespoints title 'Quick Sort (Caso Médio)'

# Define a saída para o gráfico de Quick Sort (Melhor Caso)
set output 'graficos/quick_sort_b.png'
set title "Tempo de Execução do Quick Sort (Melhor Caso)"
set xlabel "Tamanho do Array"
set ylabel "Tempo Médio de Execução (microssegundos)"
set grid
plot 'graficos/quick_b_time.txt' using 1:2 with linespoints title 'Quick Sort (Melhor Caso)'

# Define a saída para o gráfico de Quick Sort (Pior Caso)
set output 'graficos/quick_sort_w.png'
set title "Tempo de Execução do Quick Sort (Pior Caso)"
set xlabel "Tamanho do Array"
set ylabel "Tempo Médio de Execução (microssegundos)"
set grid
plot 'graficos/quick_w_time.txt' using 1:2 with linespoints title 'Quick Sort (Pior Caso)'

# Define a saída para o gráfico de Selection Sort
set output 'graficos/selection_sort.png'
set title "Tempo de Execução do Selection Sort"
set xlabel "Tamanho do Array"
set ylabel "Tempo Médio de Execução (microssegundos)"
set grid
plot 'graficos/selection_a_time.txt' using 1:2 with linespoints title 'Selection Sort'
