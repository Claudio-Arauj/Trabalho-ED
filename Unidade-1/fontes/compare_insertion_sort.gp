# Define o terminal de saída e o tamanho do gráfico
set terminal pngcairo size 800,600 enhanced font 'Verdana,10'

# Define a saída para o gráfico comparativo de Insertion Sort
set output 'graficos/compare_insertion_sort.png'
set title "Comparação do Tempo de Execução do Insertion Sort"
set xlabel "Tamanho do Array"
set ylabel "Tempo Médio de Execução (microssegundos)"
set grid

# Plota os dados dos três arquivos
plot 'graficos/insertion_a_time.txt' using 1:2 with linespoints title 'Insertion Sort (Caso Médio)', \
     'graficos/insertion_b_time.txt' using 1:2 with linespoints title 'Insertion Sort (Melhor Caso)', \
     'graficos/insertion_w_time.txt' using 1:2 with linespoints title 'Insertion Sort (Pior Caso)'
