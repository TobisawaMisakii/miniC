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
	%l1 = alloca i32, align 4 ; 1:flag
	store i32 0, i32* %l1, align 4
	%t3 = load i32, i32* %l1, align 4
	%t4 = icmp eq i32 %t3, 0
	br i1 %t4, label %.L5, label %.L11
.L5:
	%t6 = load i32, i32* %l1, align 4
	%t7 = icmp eq i32 %t6, 0
	%t8 = icmp eq i1 %t7, 0
	%t9 = zext i1 %t8 to i32
	store i32 %t9, i32* %l1, align 4
	br label %.L11
.L11:
	%t12 = load i32, i32* %l1, align 4
	store i32 %t12, i32* %l0, align 4
	br label %.L14
.L14:
	%t15 = load i32, i32* %l0, align 4
	ret i32 %t15
}
