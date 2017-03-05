reset
set terminal png
set output "Graphe-Test.png"
set title textcolor rgb "blue" "Temps d'execution en fonction du nombre de thread"
set grid # Grille de fond
set xtics textcolor rgb "red"; set xlabel textcolor rgb "red" "Nombre de threads" # Colorisation
set ytics textcolor rgb "red"; set ylabel textcolor rgb "red" "Temps d'execution" # Colorisation
set style fill transparent solid 0.3# Colorisation
plot "THREAD.dat" using 1:2 with lines
