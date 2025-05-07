build:
	gcc -o tema1 main.c stiva.c lista.c operatii_browser.c browser.h -g
run: build
	./tema1
clean:
	rm -f tema1
	
