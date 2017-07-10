# ExtraC
## Some of the bad parts of Python mixed with C

Every ExtraC program can only contain the following characters:

    ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz \n\t()0123456789,\

If it contains anything else, the program terminates with an error. Otherwise, this is normal C, with a lot of `#define` statements prior to the program execution.

Here's "Hello, World!":

    printf(quote(Hello)CHAR CHAR quote(World)CHAR,44,32,33)

How to execute the program:

    ruby extrac.rb <filename>