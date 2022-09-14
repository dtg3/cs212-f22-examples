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

char* repeat_letter_broken(int count, char letter) {
    char string[count + 1];
    for (int i = 0; i < count; ++i) {
        string[i] = letter;
    }
    string[count] = '\0';

    // This doesn't work because string is destroyed
    //  once the function returns. Verify this with
    //  the visualization link at the top of the file.
    printf("%s location: %p\n", __FUNCTION__, string);
    return string;
}

void repeat_letter_working(char *array, int count, char letter) {
    
    for (int i = 0; i < count; ++i) {
        array[i] = letter;
    }
    array[count] = '\0';

    // This doesn't work because string is destroyed
    //  once the function returns. Verify this with
    //  the visualization link at the top of the file.
    printf("%s location: %p\n", __FUNCTION__, array);
}

int main(int argc, char *argv[]) {
    int my_count = 5;
    repeat(my_count);

    char *repeat_string = repeat_letter_broken(my_count, 'a');
    printf("%s location: %p\n", __FUNCTION__, repeat_string);
    // The statement below is likely a segfault as 
    //  the memory from the repeat_letter function
    //  is on the stack and that has been removed when
    //  the function returns.
    //printf("%s\n", repeat_string);

    // We could avoid this by declaring the array here
    //  and passing a pointer to the array when we call the function
    char string_array[my_count + 1];

    repeat_letter_working(string_array, my_count, 'a');
    printf("%s location: %p\n", __FUNCTION__, string_array);
    printf("%s\n", string_array);

    return 0;
}
