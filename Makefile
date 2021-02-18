s1c1-build:
	gcc s1c1_hex_to_b64.c -o s1c1.o

s1c1: s1c1-build
	./s1c1 "4d656e6f6e"
