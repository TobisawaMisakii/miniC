int main()
{
    int i = 0;
	while (i < 5)
	{
		i = i + 1;
		if (i == 2)
		{
			continue;
		}
		break;
		while (i != 1)
		{
			putint(i);
		}
		
	}
    return i;
}
// int main()
// {
//     float a[2], b[2][3], n;
//     a[0] = 1.1;
//     b[1][1] = 1.2;
//     n = b[1][1]-a[0];
//     return 0;
// }