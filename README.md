## find.exe version 1.0 - Command Line Application 
### author:  Klaudia Jaros
#### please read this document before using find.exe
	

### What is find.exe ?
=======================
 It is a command line application which allows you to search a given .txt file for a specified word. 
 Find.exe has two built-in features: 
 1) Word replacement mode, which allows you to find a given word within your txt document and replace it with another.
    This mode creates a copy of the original file called "output.txt" and saves it with the changes to the word.
 2) Case insensitive mode, this mode ignores case while searching for a given word. 

### Requirements:
========================
 - Windows OS and Microsoft Compiler / Visual Studio Developer Command Prompt

### How to install it?
========================
 Open your Microsoft Compiler and use the command: nmake find ,
 to compile the application and produce find.exe. You are ready to use the application now.

### How to use it ?
========================
 Use the command:  find <word_to_find> -i <file_to_search> for the standard search mode, case sensitive.
 Example:  find and -i my_document.txt
 Caution:  
 - The word you want to find must be entered right after calling find as above. 
 - After calling -i, you must provide your .txt document next, with the .txt extension, as above.

### Optional arguments:
========================
 -r  used to replace <word_to_find> with another word specified by the user <replacement_word>
 Command:  find <word_to_find> -i <file_to_search> -r <replacement_word>
 Example:  find and -i my_document.txt -r or
 Caution: 
 - After calling -r, you must provide the replacement word right after, as shown above.

 -c  used to enable the case-insensitive mode, to ignore case while searching for words 
 Command:  find <word_to_find> -i <file_to_search> -c
 Example: find and -i my_document.txt -c
	  find and -i my_document.txt -r or -c

 The order of your arguments doesn't matter unless specified above. 

### Uninstall the application:
=============================
 Open your Microsoft Compiler and use the command: nmake clear
