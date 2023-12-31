# Compile source files
gcc -c url.c -o url.o
gcc -c bag.c -o bag.o
gcc -c hashtable.c -o hashtable.o
gcc -c webpage.c -o webpage.o
gcc -c pagedir.c -o pagedir.o
gcc -c curl.c -o curl.o
gcc -c crawler.c -o crawler.o

# Link object files to create the executable
gcc -o my_crawler crawler.o url.o bag.o hashtable.o webpage.o pagedir.o curl.o -lm -lcurl


./my_crawler https://engineering.ucsc.edu/ crawled_pages 2


gdb ./my_crawler
run https://engineering.ucsc.edu/ crawled_pages 2

valgrind --leak-check=full ./my_crawler