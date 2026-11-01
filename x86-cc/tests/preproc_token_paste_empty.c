#define P(A,B) A ## B
int main(void)
{
    int bob = 42;
    return P(bob,);
}
