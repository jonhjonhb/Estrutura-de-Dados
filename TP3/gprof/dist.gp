set term pngcairo enhanced font 'Arial, 28.0' size 1500,1100
set grid lw 1 lt 0
#set key outside
set xtics 10000
#set logscale y
set format x '%.0s%c'
set output "Desempenho-Distribuição.png"
#set output "Desempenho-Linear.png"
set title "Desempenho Distribuição de operações"
set xlabel "Número de inserções totais"
set ylabel "Tempo de execução (s)"

plot "DIST20-20.data" w lp lw 6 ps 3 pt 13 lt 2 lc rgb 'turquoise' title '20% consultas, 20% remoções', \
     "DIST0-100.data" w lp lw 6 ps 3 pt 13 lt 2 lc rgb 'royalblue' title '0% consultas, 100% remoções', \
     "DIST100-0.data" w lp lw 6 ps 3 pt 13 lt 2 lc rgb 'dark-grey' title '100% consultas, 0% remoções'