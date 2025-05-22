declare i32 @getint(...);
declare float @getfloat(...);
declare i32 @getch(...);
declare i32 @getarray(i32*);
declare i32 @getfarray(float*);
declare void @putint(i32);
declare void @putfloat(float);
declare void @putch(i32);
declare void @putarray(i32, i32*);
declare void @putfarray(i32, float*);
declare void @putf(i32*);
declare void @starttime(...);
declare void @stoptime(...);
define i32 @main() {
	%l0 = alloca i32, align 4
	%l1 = alloca i32, align 4 ; 1:a
	store i32 10, i32* %l1, align 4
	%t3 = load i32, i32* %l1, align 4
	%t4 = icmp ne i32 %t3, 0
	%t5 = xor i1 %t4, true
	%t6 = xor i1 %t5, true
	%t7 = xor i1 %t6, true
	%t8 = zext i1 %t7 to i32
	%t9 = sub i32 0, %t8
	%t10 = icmp ne i32 %t9, 0
	br i1 %t10, label %.L11, label %.L16
.L11:
	%t12 = sub i32 0, 1
	%t13 = sub i32 0, %t12
	%t14 = sub i32 0, %t13
	store i32 %t14, i32* %l1, align 4
	br label %.L18
.L16:
	store i32 0, i32* %l1, align 4
	br label %.L18
.L18:
	%t19 = load i32, i32* %l1, align 4
	store i32 %t19, i32* %l0, align 4
	br label %.L21
.L21:
	%t22 = load i32, i32* %l0, align 4
	ret i32 %t22
}
