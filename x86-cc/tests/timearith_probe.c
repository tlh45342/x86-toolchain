typedef long time_t;
time_t f(time_t x){ return x / 4 + 3; }
int main(void){ time_t x; x=100000; return f(x)==25003?42:1; }
