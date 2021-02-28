s1c1-build:
	gcc s1c1_hex_to_b64.c -o s1c1.o

s1c1: s1c1-build
	./s1c1.o "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"


s1c2-build:
	gcc s1c2_xoring.c -o s1c2.o

s1c2: s1c2-build
	./s1c2.o "1c0111001f010100061a024b53535009181c" "686974207468652062756c6c277320657965"


s1c3-build:
	gcc s1c3_single_char_xor.c -o s1c3.o

s1c3: s1c3-build
	./s1c3.o "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"


s1c4-build:
	gcc s1c4.c -o s1c4.o

s1c4: s1c4-build
	./s1c4.o


s1c5-build:
	gcc s1c5.c -o s1c5.o 

s1c5: s1c5-build
	./s1c5.o "./s1c5.txt" "ICE"


s1c6-shell:
	$(shell base64 -d s1c6.txt > s1c6_decoded.txt)

s1c6-build: s1c6-shell
	gcc -g s1c6.c -o s1c6.o 

s1c6: s1c6-build
	./s1c6.o "./s1c6.txt"


s1c7-shell:
	$(shell curl https://cryptopals.com/static/challenge-data/7.txt > s1c7.txt)
	$(shell base64 -d s1c7.txt > s1c7_decoded.txt)
s1c7-build:s1c7-shell
	gcc -g s1c7.c -lssl -lcrypto -o s1c7.o 
s1c7:s1c7-build
	./s1c7.o

s1c8-shell:
	$(shell curl https://cryptopals.com/static/challenge-data/8.txt > s1c8.txt)
s1c8-build:
	gcc -g s1c8.c -o s1c8.o
s1c8:s1c8-build
	./s1c8.o
