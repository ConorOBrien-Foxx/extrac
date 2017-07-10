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
onend(no_op);//sets on_end to default nothing