set pagination off
set logging off

start
watch I
c
c
c
c
c
set $count = 0
while R
	if $count >= 28 && $count <= 35
		echo @@@	
		printf " start = %d\n", R->start
		echo @@@
		printf " stop = %d\n", R->stop
		echo @@@
		printf " step = %d\n", R->step
		echo @@@
		printf " current = %d\n", R->current
	end
	set $count = $count + 1
	c
end
quit
