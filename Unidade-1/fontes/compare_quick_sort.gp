# Define o terminal de saída e o tamanho do gráfico
set terminal pngcairo size 800,600 enhanced font 'Verdana,10'

# Define a saída para o gráfico comparativo de Quick Sort
set output 'graficos/compare_quick_sort.png'
set title "Comparação do Tempo de Execução do Quick Sort"
set xlabel "Tamanho do Array"
set ylabel "Tempo Médio de Execução (microssegundos)"
set grid

# Plota os dados dos três arquivos
plot 'graficos/quick_a_time.txt' using 1:2 with linespoints title 'Quick Sort (Caso Médio)', \
     'graficos/quick_b_time.txt' using 1:2 with linespoints title 'Quick Sort (Melhor Caso)', \
     'graficos/quick_w_time.txt' using 1:2 with linespoints title 'Quick Sort (Pior Caso)'
