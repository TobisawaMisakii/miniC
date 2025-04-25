

// int globalVariable = 10;  // 全局变量，带初始化表达式
// const int globalConstant = 20;  // 全局常量，带初始化表达式

// int f()
// {
//  int functionVariable = 50;  // 局部变量，带初始化表达式
//  const int functionConstant = 60;  // 局部常量，带初始化表达式
//  return functionVariable + functionConstant;	
// }
int main()
{
	// int localVariable = 30;  // 局部变量，带初始化表达式
    // const int localConstant = 40;  // 局部常量，带初始化表达式
    // return f();
    int a = 2;
    int b;
    b = 2;
    return a;
}

// int main()
// {
//     int a[10], b[10];
//     int i = 0;
//     while (i < 10)
//     {
//         a[i] = i;
//         i = i + 1;
//     }
// 	i = 0;
//     while (i < 10)
//     {
//         if (a[i] % 2 == 0)
// 		{
// 			b[i] = a[i] * 2;
// 		} else {
//             b[i] = a[i] / 3;
//         }
// 		i = i + 1;
//     }
//     return b[0];
// }

// int sbzqr(int a, float b)
// {
//     int i = 0;
//     while (i < 10)
//     {
//         a = a + i;
//         i = i + 1;
//     }
//     return b;
// }

// 当前前端存在的问题：
// 1. relExp addExp eqExp左值不对 (已解决)
// 2. formal-params的类型不对（float被识别为void） (已解决)
