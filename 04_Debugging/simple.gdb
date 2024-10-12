set logging off
start
watch I
condition 2 I.current == 5
c
echo @@@
p R->start
echo @@@
p R->stop
echo @@@
p R->step
echo @@@
p R->current
