# ExtraC
## Some of the bad parts of Python mixed with C

Every ExtraC program can only contain the following characters:

    ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz \n\t()0123456789,\

All instances of `//` are replaced by `\\`, and `\\` is the comment symbol. All `-`s are removed. If it contains anything else, the program terminates with an error. Otherwise, this is normal C, with a lot of `#define` statements prior to the program execution.

Here's "Hello, World!":

    printf(quote(Hello)CHAR CHAR quote(World)CHAR,44,32,33)

How to execute the program:

    ruby extrac.rb <filename>

## More example programs

Part of ExtraC's standard library is written in ExtraC. Here is `range`:

    function(
        range, returns an array pointer,   \
        takes a number named min,          \
        takes another number named max     \
    ) does
        arraylen is max minus min plus 1
        new(array, result)
        let the counter be 0
        let the upperbound be arraylen
        until(the counter equals the length(of the result)) do
            setpos(result, counter, min plus counter)
            increment counter
        end
        return the result
    end

Pretty readable, right? Well, opinions may differ, but this language should obviously replace Java, C++, and Python.