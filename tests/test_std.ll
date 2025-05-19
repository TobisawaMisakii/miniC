define i32 @main() {
	%l0 = alloca i32, align 4
	%l1 = alloca i32, align 4 ; variable: a
	store i32 5, i32* %l1, align 4
	%t2 = load i32, i32* %l1, align 4
	store i32 %t2, i32* %l0, align 4
	%t3 = load i32, i32* %l0, align 4
	ret i32 %t3
}
declare i32 @getint(...);
declare i32 @getch(...);
declare void @putint(i32);
declare void @putch(i32);
declare void @putstr(i8*);
declare i32 @getarray(i32*);
declare void @putarray(i32, i32*);
declare float @getfloat(...);
declare void @putfloat(float);
declare i32 @getfarray(float*);
declare void @putfarray(i32, float*);
