
say_hello:
	echo "Hello World"


com:
	iverilog -g2012 -o day_object day.sv tb_day.sv

sim:
	vvp day_object

wave:
	gtkwave day.vcd

test: say_hello
run:	com	sim

run_gui:	com	sim wave

clean:
	rm day_object
	rm day.vcd
