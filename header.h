#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <time.h>
#include <stdarg.h>
typedef int64_t large;
#define function(name, desc, ...) desc name(__VA_ARGS__)
#define nilad(name, desc) function(name, desc, void)
// access
#define fst(n) (n)[0]
#define snd(n) (n)[1]
#define nth(n,k) (n)[k]
// type specifiers
#define INT "%i"
#define INTREP "%*i"
#define INTLREP "%-*i"
#define LARGE "%"PRId64
#define LARGEREP "%*"PRId64
#define LARGELREP "%-*"PRId64
#define CHAR "%c"
#define CHARREP "%*c"
#define CHARLREP "%-*c"
// more sugar
#define until(e)while(!(e))
#define equals ==
#define is =
#define pointer *
#define be =
#define to =
#define less <
#define greater >
#define sorta(x) x##=
// types
#define let int
#define dbl double
#define var char
#define def string*
#define set large
#define arr array*
#define number int
#define integer large
// more sugar
#define very(x) x x
#define decrement --
#define increment ++
#define added +
#define plus +
#define lack (void)
#define times *
#define multiplied *
#define minus -
#define subtracted -
#define negative -
#define divide /
#define divided /
#define modulus %
#define not !
#define do {
#define does do
#define end }
#define and &
#define or |
#define AND ;
#define xor ^
#define F (double)
#define print(x) printf("%d%c", x, EOS)
#define show(x) printf("%c%c", x, EOS)
#define disp(x) printf("%g%c", x, EOS)
#define echo(x) string_display(x)
#define out(x) printf("%s", x)
#define map(s,f)({for(size_t i = 0; i < s->size; i++) s->data[i] = f(s->data[i]); })
#define length(z) ((z)->size)
#define each(s,f)({for(size_t i = 0; i < s->size; i++){ f(s->data[i]);} })
#define trace(x) printf(LARGE"%c", x, EOS)
#define puteos putchar(EOS)
#define error(x) fprintf(stderr, "Error: %s\n", x)
#define quote(x) #x
#define quit exit(0)
#define getmem(pos) mem[pos]
#define setmem(pos, val) mem[pos] = val
#define false (0 == 1)
#define true (0 == 0)
#define bool int
#define forever while(true)
#define prepend(str, c) string_prepend_char(str, c)
#define append(str, c) string_append_char(str, c)
#define setpos(a, b, c) ((a)->data[b] = c)
#define getpos(a, b) ((a)->data[b])
typedef struct array {
    size_t size;
    double* data;
} array;
array* array_of(size_t s){
    array* res = malloc(sizeof(array));
    res->size = s;
    res->data = malloc(sizeof(double) * res->size);
    return res;
}
array* c(size_t n, ...){
    va_list args;
    va_start(args, n);
    array* res = array_of(n);
    for(size_t i = 0; i < n; i++){
        res->data[i] = (double) va_arg(args, double);
    }
    return res;
}
// string stuff
typedef struct string {
    size_t capacity;
    size_t size;
    char* data;
} string;
void string_init(string* str, const char* source, size_t size){
    str->capacity = 1;
    while(str->capacity <= size){
        str->capacity <<= 1;
    }
    str->data = malloc(sizeof(char) * str->capacity);
    str->size = size;
    
    memcpy(str->data, source, sizeof(char) * size);
}
void string_resize(string* str){
    str->data = realloc(str->data, sizeof(char) * str->capacity);
}
void string_grow(string* str){
    str->capacity *= 2;
    string_resize(str);
}
void string_shrink(string* str){
    if(str->capacity <= 1) return;
    str->capacity /= 2;
    if(str->capacity < str->size)
        str->size = str->capacity;
    string_resize(str);
}
void string_append_char(string* str, char c){
    if(str->size + 1 >= str->capacity){
        string_grow(str);
    }
    str->data[str->size] = c;
    str->size++;
}
void string_prepend_char(string* str, char c){
    if(str->size + 1 >= str->capacity){
        string_grow(str);
    }
    memmove(str->data + 1, str->data, str->size);
    str->data[0] = c;
    str->size++;
}
void string_display(string* str){
    write(1, str->data, str->size);
}
char* string_cstr(string* str){
    char* res = malloc(sizeof(char) * (str->size + 1));
    memcpy(res, str->data, str->size * sizeof(char));
    res[str->size] = '\0';
    return res;
}
void string_free(string* str){
    free(str->data);
    free(str);
}
string* read_line(FILE* f){
    int c;
    string* s = malloc(sizeof(string));
    string_init(s, "", 0);
    
    forever {
        c = fgetc(f);
        if(c == EOF) break;
        string_append_char(s, c);
        if(c == '\n') break;
    }
    
    return s;
}
#define new(type, name) type* name = make_new(#type)
size_t str_len(const char* a){ size_t i = 0; while(a[i]) i++; return i; }
size_t arraylen = 2;
int str_eql(const char* a, const char* b){
    if(str_len(a) != str_len(b)) return false;
    for(size_t i = 0; i < str_len(a); i++){
        if(a[i] != b[i]) return false;
    }
    return true;
}
void* make_new(const char* type){
    if(str_eql(type, "string")){
        string* res = malloc(sizeof(string));
        string_init(res, "", 0);
        return res;
    } else if(str_eql(type, "array")){
        array* res = array_of(arraylen);
        return res;
    } else {
        fprintf(stderr, "Unknown object target `%s`\n", type);
    }
}
bool is_numeric(char c){
    return c >= '0' && c <= '9';
}
bool is_decimal(char c){
    return is_numeric(c) || c == '-' || c == '.';
}
large string_to_large(string* s){
    size_t i = 0;
    large res = 0;
    while(is_numeric(s->data[i])){
        res *= 10;
        res += s->data[i] - '0';
        i++;
    }
}
large read_large(){
    string* s = read_line(stdin);
    large res = string_to_large(s);
    string_free(s);
    return res;
}
// various input methods
int read_int(){
    int res;
    scanf("%d", &res);
    return res;
}
array* read_array(){
    string* k = read_line(stdin);
    // string_display(k);
    // get length
    size_t s, i;
    for(i = s = 0; i < k->size; i++){
        if(!is_numeric(k->data[i])){
            while(!is_numeric(k->data[i])){
                i++;
            }
            s++;
        }
    }
    array* res = array_of(s);
    string* build = malloc(sizeof(string));
    string_init(build, "", 0);
    for(i = s = 0; i < k->size; i++){
        // printf("'%c'\n", k->data[i]);
        if(is_decimal(k->data[i])){
            while(is_decimal(k->data[i])){
                append(build, k->data[i]);
                i++;
            }
            char* temp = string_cstr(build);
            // printf("[%s]\n", temp);
            res->data[s] = atof(temp);
            s++;
            free(temp);
            build->size = 0;
        }
    }
    // printf("%i %i\n", res->size, s);
    // for(s = 0; s < res->size; s++){
        // printf(">>> %g\n", res->data[s]);
    // }
    string_free(build);
    return res;
}
#define reductor(name, start, op) double name(array* arg){\
    double result = start;\
    each(arg, result op##= );\
    return result;\
}
reductor(sum, 0, +);
reductor(prd, 1, *);
#define readint read_int()
#define readlarge read_large()
#define readline read_line(stdin)
#define readarr read_array()
char EOS = ' ';
#define charof(x) (*(#x))
typedef struct { size_t size; int* data; } MEM;
typedef void (*event_t)(void);
#define event(f) void f lack
event_t on_end;
void onend(event_t t){
    on_end = t;
}
int get_random(int x, int y){ return rand() % (y - x) + x; }
#define random get_random
void no_op(void){}
// sugar
#define by      /**/
#define than    /**/
#define returns /**/
#define Returns /**/
#define takes   /**/
#define an      /**/
#define the     /**/
#define a       /**/
#define of      /**/
#define named   /**/
#define another /**/
#define WITH    /*used for joining statements*/
#define BUT     /*used for joining statements*/
