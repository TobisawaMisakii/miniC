// 常量声明
const int MAX = 10;
const float PI = 3.1415926;
const int array1[5][2] = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}};

// 全局变量声明
int globalVar;
float globalFloatVar;

/*
* 测试多行注释
* abcsscascav
*/

// 主函数
int main() {
    // 局部变量声明
    int a = 0x10, b = 020;
    float c = 3.14e-2, d = 2.718;
    float array2[3] = {1.1, 2.2, 3.3};

    // 条件语句
    if (a > b || !1) {
        a = a % b;
    } else {
        a = b / a[8][6][7];
    }

    // 循环语句
    int i = 0;
    while (i <= MAX) {
        i = i + 1;
    }

    // 函数调用
    printArray(array1, 5);
    int sum = add(a, b);
    float product = multiply(c, d);

    // 数组操作
    while(i < 5) {
		i = i + 1;
        array1[i] = array1[i] * 2;
    }

    return 0;
}

// 函数定义
void printArray(int arr[], int size) {
    int i;
    while (i < size) {
		print(arr[i]);
		i = i + 1;
	}
	{
        ;
    }
}

int add(int a, int b) {
    return a + b;
}

float multiply(float a, float b) {
    return a * b;
}