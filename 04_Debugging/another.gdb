set pagination off
set logging off

start
watch I
condition 2 I.current >= 28 && I.current <= 35
c
while R
	echo @@@
	printf " start = %d\n", R->start
	echo @@@
	printf " stop = %d\n", R->stop
	echo @@@
	printf " step = %d\n", R->step
	echo @@@
	printf " current = %d\n", R->current
	c
end
quit
