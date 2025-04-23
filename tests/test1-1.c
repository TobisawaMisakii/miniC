int main()
{
    int a[10], b[10];
    int i = 0;
    while (i < 10)
    {
        a[i] = i;
        i = i + 1;
    }
	i = 0;
    while (i < 10)
    {
        if (a[i] % 2 == 0)
		{
			b[i] = a[i] * 2;
		} else {
            b[i] = a[i] / 3;
        }
		i = i + 1;
    }
    return b[0];
}

int sbzqr(int a, float b)
{
    int i = 0;
    while (i < 10)
    {
        a = a + i;
        i = i + 1;
    }
    return b;
}

// 当前前端存在的问题：
// 1. relExp addExp eqExp左值不对 (已解决)
// 2. formal-params的类型不对（float被识别为void） (已解决)
