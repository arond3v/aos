kernel.bin:
	./x86_64-elf-ld -n -o iso/boot/kernel.bin -T linker.ld temp/*.o

.PHONY: clean
clean:
	rm temp/*.o