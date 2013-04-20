setup:

configure:
	./waf configure

compile: configure
	./waf build

install: compile
	${LIBPEBBLE_HOME}/p.py --lightblue load build/pebble-mori.pbw

reinstall: compile
	${LIBPEBBLE_HOME}/p.py --lightblue reinstall build/pebble-mori.pbw


