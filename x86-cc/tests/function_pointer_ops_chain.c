struct ops {
 int (*call)(int a,int b);
};
struct device {
 struct ops *ops;
};

int add(int a,int b)
{
 return a+b;
}

int main(void)
{
 struct ops o;
 struct device d;
 struct device *p;
 o.call=add;
 d.ops=&o;
 p=&d;
 return p->ops->call(20,22);
}
