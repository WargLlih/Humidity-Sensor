setup: SHELL:=/bin/bash
setup:
	wget https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py

	python -m venv venv
	. venv/bin/activate && \
		python -m pip install -U pip && \
		python get-platformio.py || \
		python get-platformio.py --verbose
	
	. venv/bin/activate && pip install platformio

build:
	. venv/bin/activate && \
		pio run

upload:
	. venv/bin/activate && \
		pio run -t upload

clang-config:
	. venv/bin/activate && \
		pio run -t compiledb

clean:
	rm -rf venv
	rm -f get-platformio.py*
