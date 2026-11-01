struct clockish {
    int sec, min, hour;
    char lead, bytes[4];
};
int main(void)
{
    struct clockish x;
    x.sec = 20;
    x.hour = 22;
    return x.sec + x.hour;
}
