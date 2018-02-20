run: disable_aslr bin/main
	./bin/main

bin/main:
	mkdir -p bin
	gcc -std=c99 -fno-stack-protector -o bin/main -g main.c

disable_aslr:
	@echo "This program is about to disable ASLR to allow for buffer overflow experimentation."
	@echo "[Press enter if you're okay with that]"
	@read _
	echo 0 | sudo tee /proc/sys/kernel/randomize_va_space

clean:
	rm -r ./bin/
