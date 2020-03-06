find:
	cl find.c
clear:
	del *obj
	del *exe	
	del *asm

	
// Tests:	
1a:
	find operating -i single_words_test.txt
1b:
	find language -i sentences_test.txt
2a:
	find con -i single_words_test.txt
2b:
	find con -i sentences_test.txt	
3a:
	find ing -i single_words_test.txt
3b:
	find ing -i sentences_test.txt	
4a:
	find pli -i single_words_test.txt
4b:
	find pli -i sentences_test.txt	
5a:
	find system -i single_words_test.txt -r helloo
5b:
	find systems -i sentences_test.txt -r goodbye
6a:
	find pli -i single_words_test.txt -r XX
6b:
	find pli -i sentences_test.txt -r XX
7a:
	find rather -i single_words_test.txt -c
7b:
	find ja -i sentences_test.txt -c
8a:
	find THE -i single_words_test.txt -r XX -c
8b:
	find one -i sentences_test.txt -r XXX -c
9a:
	find e -i single_words_test.txt -r X	
9b:
	find e -i sentences_test.txt -r X
10a:
	find Cat -i single_words_test.txt -c
10b:
	find CaT -i sentences_test.txt -c
11a:
	find ING -i single_words_test.txt -r ED -c
11b:
	find ING -i sentences_test.txt -r ED -c
	
