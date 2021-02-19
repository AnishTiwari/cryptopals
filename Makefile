s1c1-build:
	gcc s1c1_hex_to_b64.c -o s1c1.o

s1c1: s1c1-build
	./s1c1.o "4d656e6f6e"


s1c2-build:
	gcc s1c2_xoring.c -o s1c2.o

s1c2: s1c2-build
	./s1c2.o "1c0111001f010100061a024b53535009181c" "686974207468652062756c6c277320657965"

