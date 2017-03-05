reset
set terminal png
set output "La Rochelle.png"
set title textcolor rgb "blue" "Données météorologiques de La Rochelle de 1961 à 1990\n(données issues de http://www.infoclimat.fr)"
set key outside below; set key title "Légende"; set key box reverse; set key box lw 2 lc 4 # Légende
set grid # Grille de fond
set label 1 textcolor rgb "orange" "305 heures" at 2,20 centre; set arrow 1 from 3.5,20 to 6,19.2 # Info
set xtics textcolor rgb "green" border ("Jan" 0, "Fév" 1, "Mar" 2, "Avr" 3, "Mai" 4,"Jun" 5,"Jui" 6, "Aou" 7,"Sep" 8,"Oct" 9,"Nov" 10,"Déc" 11) # Mois sur axe des x
set x2range [-1:12]; set x2tics textcolor rgb "green" border ("1" 0, "2" 1, "3" 2, "4" 3, "5" 4,"6" 5,"7" 6, "8" 7,"9" 8,"10" 9,"11" 10,"12" 11) # Chiffres sur axe des x2
set ytics textcolor rgb "red"; set ylabel textcolor rgb "red" "T. moyennes" # Colorisation
set y2label textcolor rgb "orange" "E. moyen"; set y2tics textcolor rgb "orange"; set y2range [70:350]# Colorisation + échelle axe y2
set style fill transparent solid 0.3# Colorisation
plot [-1:12] [4:22] "a.dat" using 3 axes x1y2 title "Ensoleillement (h/mois)" with boxes lc rgb "yellow",\
"a.dat" using 2 title "Températures (°C)" with linespoints lc rgb "red"


