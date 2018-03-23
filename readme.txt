A simple overview of how the implementation of this program should go:

1.	Parse the input commands as stated in huffman.c.  Be sure to
		check for wrong inputs.  Exact error messages will not be
		checked.  For example, if we have:
						./huffman -c ./temp.txt --code
				We need to print out that there is no code file specified, etc.

2.	Write the functions(data structures) to hold the information from the code
		file, based on whether the file is to be compressed or decompressed.
			If a file is to be decompressed, you need to build a binary tree
			to hold the information from the code file
			If a file is to be compressed, you need to use either a linked list
			or array to hold the information from the code file.

3.	Write the functions to either compress or decompress the file.


Also note, you are only doing 1 operation per run of the program.
	If we have:
		./huffman -c ./temp.txt --code ./temp.code
		Then the main function should:
			1. Grab the ./temp.txt as the input file
			2. Grab the ./temp.code as the code file
			3. Set the output file name as "out.huf"
			4. Call buildLinkedList() (or similar function)
			5. Call compressFile() (or similar function)
			6. free malloc'd variables
			7. Return


HINT for storing the binary representations of certain bytes:
	USE UNSIGNED CHARS


This homework is all about self-dependency.  Questions to debug will not be answered.
Questions about logistics might be answered.