// 常量声明
const int MAX = 10;
const float PI = 3.1415926;
const int array1[5] = {1, 2, 3, 4, 5};

// 全局变量声明
int globalVar;
float globalFloatVar;


// 主函数
int main() {
    // 局部变量声明
    int a = 10, b = 20;
    float c = 3.14, d = 2.718;
    float array2[3] = {1.1, 2.2, 3.3};

    // 条件语句
    if (a > b) {
        a = a - b;
    } else {
        a = b - a;
    }

    // 循环语句
    int i = 0;
    while (i < MAX) {
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