#
# RTX Makefile for RTX v1.0
# Authors: Doug Sherk, James Anselm, Eugene Chung
# Targets: g++ (gcc 4.3.3), g++ (gcc 4.1.2), MSVC 2010 RTM (10.0.30319.1)
#

params = -W -Wextra -Werror -Wall -pedantic

all: rtx kbd crt

rtx:	main.o \
	kernel.o rtx.o \
	tracebuf.o pcb.o msgenv.o memory.o process.o \
	process_null.o process_a.o process_b.o process_c.o \
		process_wallclock.o process_cci.o process_welcome.o \
	i_process_timer.o i_process_keyboard.o i_process_crt.o \
		i_process_terminate.o
	g++ main.o kernel.o rtx.o tracebuf.o pcb.o msgenv.o memory.o process.o process_null.o process_a.o process_b.o process_c.o process_wallclock.o process_cci.o process_welcome.o i_process_timer.o i_process_keyboard.o i_process_crt.o i_process_terminate.o $(params) -o rtx

kbd: helper_process_keyboard.o
	g++ helper_process_keyboard.o $(params) -o kbd

crt: helper_process_crt.o
	g++ helper_process_crt.o $(params) -o crt

helper_process_keyboard.o: helper_process_keyboard.cpp
	g++ $(params) -c helper_process_keyboard.cpp

helper_process_crt.o: helper_process_crt.cpp
	g++ $(params) -c helper_process_crt.cpp

main.o: main.cpp
	g++ $(params) -c main.cpp

kernel.o: kernel.cpp
	g++ $(params) -c kernel.cpp

rtx.o: rtx.cpp
	g++ $(params) -c rtx.cpp

tracebuf.o: tracebuf.cpp
	g++ $(params) -c tracebuf.cpp

pcb.o: pcb.cpp
	g++ $(params) -c pcb.cpp

msgenv.o: msgenv.cpp
	g++ $(params) -c msgenv.cpp

memory.o: memory.cpp
	g++ $(params) -c memory.cpp

process.o: process.cpp
	g++ $(params) -c process.cpp

process_null.o: process_null.cpp
	g++ $(params) -c process_null.cpp

process_a.o: process_a.cpp
	g++ $(params) -c process_a.cpp

process_b.o: process_b.cpp
	g++ $(params) -c process_b.cpp

process_c.o: process_c.cpp
	g++ $(params) -c process_c.cpp

process_wallclock.o: process_wallclock.cpp
	g++ $(params) -c process_wallclock.cpp

process_cci.o: process_cci.cpp
	g++ $(params) -c process_cci.cpp

process_welcome.o: process_welcome.cpp
	g++ $(params) -c process_welcome.cpp

i_process_timer.o: i_process_timer.cpp
	g++ $(params) -c i_process_timer.cpp

i_process_keyboard.o: i_process_keyboard.cpp
	g++ $(params) -c i_process_keyboard.cpp

i_process_crt.o: i_process_crt.cpp
	g++ $(params) -c i_process_crt.cpp

i_process_terminate.o: i_process_terminate.cpp
	g++ $(params) -c i_process_terminate.cpp

clean:
	rm -f main.o kernel.o rtx.o tracebuf.o pcb.o msgenv.o memory.o process.o process_null.o process_a.o process_b.o process_c.o process_wallclock.o process_cci.o process_welcome.o i_process_timer.o i_process_keyboard.o i_process_crt.o i_process_terminate.o helper_process_keyboard.o helper_process_crt.o
