float add(float a, float b[])
{
    return a+b[0];
}
int main()
{
    float a[10];
    float b[2][2];
    // const int c = 1;
    b[0][0] = 2.0;
    a[0]=add(0.1, b[0]);
    return 2;//add(a[1], b[0][0])
}
