# Define o terminal de saída e o tamanho do gráfico
set terminal pngcairo size 1200,800 enhanced font 'Verdana,10'

# Define a saída para o gráfico comparativo de todos os algoritmos
set output 'graficos/compare_all_sorts_whitout_insertion(a)(w).png'
set title "Comparação do Tempo de Execução de Diversos Algoritmos de Ordenação"
set xlabel "Tamanho do Array"
set ylabel "Tempo Médio de Execução (microssegundos)"
set grid

# Plota os dados de todos os arquivos
plot 'graficos/distribution_a_time.txt' using 1:2 with linespoints title 'Distribution Sort', \
     'graficos/insertion_b_time.txt' using 1:2 with linespoints title 'Insertion Sort (Melhor Caso)', \
     'graficos/merge_a_time.txt' using 1:2 with linespoints title 'Merge Sort', \
     'graficos/quick_a_time.txt' using 1:2 with linespoints title 'Quick Sort (Caso Médio)', \
     'graficos/quick_b_time.txt' using 1:2 with linespoints title 'Quick Sort (Melhor Caso)', \
     'graficos/quick_w_time.txt' using 1:2 with linespoints title 'Quick Sort (Pior Caso)', \
     'graficos/selection_a_time.txt' using 1:2 with linespoints title 'Selection Sort'
