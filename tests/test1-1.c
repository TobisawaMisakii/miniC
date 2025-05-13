int add(int a,int b)
{
    return a+b;
}
int sub()
{
    return 1;
}
int main()
{
    int a[10];
    int b[2][2];
    // const int c = 1;
    a[1] = 1;
    b[0][0]=2;
    return sub()+add(a[1], b[0][0]);//add(a[1], b[0][0])
}