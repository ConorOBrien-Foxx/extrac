#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
typedef int64_t large;
#define INT "%i"
#define INTREP "%*i"
#define INTLREP "%-*i"
#define LARGE "%"PRId64
#define LARGEREP "%*"PRId64
#define LARGELREP "%-*"PRId64
#define CHAR "%c"
#define CHARREP "%*c"
#define CHARLREP "%-*c"
#define until(e)while(!(e))
#define equals ==
#define is =
#define be =
#define to =
#define let int
#define var char
#define set large
#define decrement --
#define increment ++
#define add +
#define plus +
#define lack (void)
#define times *
#define minus -
#define subtract -
#define divide /
#define modulus %
#define not !
#define multiplied *
#define by /**/
#define do {
#define end }
#define and &
#define or |
#define xor ^
#define print(x) printf("%d%c", x, EOS)
#define show(x) printf("%c%c", x, EOS)
#define disp(x) printf("%g%c", x, EOS)
#define echo(x) string_display(x)
#define out(x) printf("%s", x)
#define puteos putchar(EOS)
#define trace(x) printf(LARGE"%c", x, EOS)
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
    } else {
        fprintf(stderr, "Unknown object target `%s`\n", type);
    }
}
bool is_numeric(char c){
    return c >= '0' && c <= '9';
}
large read_large(){
    string* s = read_line(stdin);
    char c = '0';
    size_t i = 0;
    large res = 0;
    while(is_numeric(s->data[i])){
        res *= 10;
        res += s->data[i] - '0';
        i++;
    }
    string_free(s);
    return res;
}
// various input methods
int read_int(){
    int res;
    scanf("%d", res);
    return res;
}
#define readint read_int()
#define readlarge read_large()
char EOS = ' ';
#define charof(x) (*(#x))
typedef struct { size_t size; int* data; } MEM;
typedef void (*event_t)(void);
#define event(f) void f lack
event_t on_end;
void onend(event_t t){
    on_end = t;
}
int random(x, y){ return rand() % (y - x) + x; }
void no_op(void){}
int main(){
size_t* fe_cs = calloc(256, sizeof(size_t));
size_t fe_c = 0;
#define foreach(name, s) for(name = s->data[fe_cs[++fe_c] = 0]; fe_cs[fe_c] < s->size; name = s->data[++fe_cs[fe_c]])
#define endeach } --fe_c;
#define dotimes(n) for(fe_cs[++fe_c] = n; fe_cs[fe_c] > 0; --fe_cs[fe_c]) {
srand(time(NULL));
MEM* mem = malloc(sizeof(MEM));
mem->size = 1000;
mem->data = calloc(mem->size, sizeof(int));
onend(no_op);
