struct ops {
 int (*call)(int a,int b);
};

int add(int a,int b)
{
 return a+b;
}

int main(void)
{
 struct ops o;
 o.call=add;
 return o.call(20,22);
}
