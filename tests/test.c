
const int a = 1;
int main()
{
    const int b = 2;
    int array[a][b];
    array[0][0] = 2;
	return array[0][0];
}