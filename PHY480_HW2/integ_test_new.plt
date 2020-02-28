# record the time and date the graph was generated
set timestamp

# titles and labels
set title 'Comparing Integration Algorithms'
set xlabel 'log10(N)'
set ylabel 'relative error'

# move the legend to a free space
set key left

# set the x and y axis scales (already logs)

# fit the curve
f(x) = a*x + b
fit [2:5] f(x) "integ.dat" using ($1):($2) via a,b

h(x) = c*x + d
fit [2:5] h(x) "integ.dat" using ($1):($3) via c,d 

# set the terminal type to be the screen
set term qt

# plot the data as well as the fit, with appropriate titles 
plot "integ.dat" using ($1):($2) title "Simpson Rule", \
     "integ.dat" using ($1):($3) title "Milne Rule", \
     a*x+b title "Simpson Fit", \
     c*x+d title "Milne Fit"

#set xrange [1.5:6.5]
#set yrange [-45:-5]

