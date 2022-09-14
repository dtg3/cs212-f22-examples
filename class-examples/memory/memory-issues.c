/* 
    Simple Example to show memory issues that
    valgrind can help detect.

    To run with valgrind, compile the program, and then
    use the format:
      valgrind ./memory-issues
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* save_string(const char* string) {
    // strdup will copy a string into a new
    //  memory buffer on the heap and return
    //  the pointer to it
    return strdup(string);
}

// Create a new string exactly the right size for two strings
char* concat_string(const char* left, const char* right) {
    // should have a +1 at the end for null terminator ('\0' or 0)
    size_t new_string_size = strlen(left) + strlen(right);

    // Like malloc, but fills the memory with 0's
    char * combined_string = calloc(new_string_size, sizeof(char));
    
    // If you use malloc (no memory initialization) the strcpy before the
    //  strcat is necessary. Strcat relies on there being a null terminator
    //  to indicate the end of the first string. Strcat will just copy the string
    //  starting at the beginning of the memory buffer and will keep the null.
    strcpy(combined_string, left);
    strcat(combined_string, right);

    return combined_string;
}

int main(int argc, char *argv[]) {
    char *my_string = save_string("foo");
    printf("%s\n", my_string);

    char *combined_string = concat_string(my_string, "bar");
    printf("%s\n", combined_string);

    // Missing the frees to cleanup the memory
    //  we received from save_string and concat_string

    return 0;
}
