/* 
    Simple Example to show how code works on the
    program stack only. Run this code using
    https://pythontutor.com/c.html#mode=edit to
    see an example of how the memory is managed.
*/

#include <stdio.h>

void repeat(int count) {
    for (int i = 0; i < count; ++i) {
        printf("Repeat #%d\n", i + 1);
    }
}

char* repeat_letter(int count, char letter) {
    char string[count + 1];
    for (int i = 0; i < count; ++i) {
        string[i] = letter;
    }
    string[count] = '\0';

    // This doesn't work because string is destroyed
    //  once the function returns. Verify this with
    //  the visualization link at the top of the file.
    printf("location: %p\n", string);
    return string;
}

int main(int argc, char *argv[]) {
    int my_count = 5;
    repeat(my_count);

    char * repeat_string = repeat_letter(my_count, 'a');
    printf("location: %p\n", repeat_string);
    // The statement below is likely a segfault as 
    //  the memory from the repeat_letter function
    //  is on the stack and that has been removed when
    //  the function returns.
    //printf("%s\n", repeat_string);
    return 0;
}
