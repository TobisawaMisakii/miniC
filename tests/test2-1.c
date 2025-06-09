//test domain of global var define and local define
int a = 3;
int b = 5;

int main(){
    int a = 5;
	if(b >= 3)
        a = 1;
    return a + b;
}