# cmake config

config:
	cmake --preset debug
	
build:config
	cmake --build --preset debug

download:build
	openocd -f  ./03cmsis-dap.cfg -c  "program  build/mydemo.bin 0x08000000 verify reset  exit"
clean:
	rm -rf build
