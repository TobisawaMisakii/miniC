int add(int a[][5], int b[], int c)
{
    return a[0][0]+b[0]+c;
}
int main()
{
    int a[3][5];
    int b[3];
    int c=1;
    a[1][1] = 2;
    b[0] = a[1][1]-c;
    return b[0];
}
