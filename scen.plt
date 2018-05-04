set term png\
    size 900, 500\
    font 'Arial, 12'


set grid xtics lc rgb  '#555555' lw 1 lt 0
set grid ytics lc rgb  '#555555' lw 1 lt 0
set key left top
set ylabel 'Number processes'
set xlabel 'Speedup'
set xtics axis
set ytics axis

set output 'result_graphs/1nodes.png'
set title '1 node'
plot 'result_1nodes/result_1024_Speedup.txt' using 1:2 with linespoints lw 2 lt rgb 'red' title 'N=1024', \
    'result_1nodes/result_2048_Speedup.txt' using 1:2 with linespoints lw 2 lt rgb 'blue' title 'N=2048', \
    'result_1nodes/result_4096_Speedup.txt' using 1:2 with linespoints lw 2 lt rgb 'green' title 'N=4096', \
    'linear_Speedup.txt' using 1:2 with linespoints lw 2 lt rgb 'black' title 'linear'

set output 'result_graphs/2nodes.png'
set title '2 node'
plot 'result_2nodes/result_1024_Speedup.txt' using 1:2 with linespoints lw 2 lt rgb 'red' title 'N=1024', \
    'result_2nodes/result_2048_Speedup.txt' using 1:2 with linespoints lw 2 lt rgb 'blue' title 'N=2048', \
    'result_2nodes/result_4096_Speedup.txt' using 1:2 with linespoints lw 2 lt rgb 'green' title 'N=4096', \
    'linear_Speedup.txt' using 1:2 with linespoints lw 2 lt rgb 'black' title 'linear'

set output 'result_graphs/4nodes.png'
set title '4 node'
plot 'result_4nodes/result_1024_Speedup.txt' using 1:2 with linespoints lw 2 lt rgb 'red' title 'N=1024', \
    'result_4nodes/result_2048_Speedup.txt' using 1:2 with linespoints lw 2 lt rgb 'blue' title 'N=2048', \
    'result_4nodes/result_4096_Speedup.txt' using 1:2 with linespoints lw 2 lt rgb 'green' title 'N=4096', \
    'linear_Speedup.txt' using 1:2 with linespoints lw 2 lt rgb 'black' title 'linear'

set output 'result_graphs/8nodes.png'
set title '8 node'
plot 'result_8nodes/result_1024_Speedup.txt' using 1:2 with linespoints lw 2 lt rgb 'red' title 'N=1024', \
    'result_8nodes/result_2048_Speedup.txt' using 1:2 with linespoints lw 2 lt rgb 'blue' title 'N=2048', \
    'result_8nodes/result_4096_Speedup.txt' using 1:2 with linespoints lw 2 lt rgb 'green' title 'N=4096', \
    'linear_Speedup.txt' using 1:2 with linespoints lw 2 lt rgb 'black' title 'linear'