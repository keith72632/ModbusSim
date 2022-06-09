SRCS = $(wildcard *.c)

all: ${SRCS}
	gcc $^ -o modbus_sim

run:
	./modbus_sim
	
clean:
	rm a.out modbus_sim