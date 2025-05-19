int add(int a, int b[])
{
    return a+b[0];
}
int main(){
    int a = 3;
    int b[3][4];
    b[0][0]=1;
    return add(a,b[0]);
}
