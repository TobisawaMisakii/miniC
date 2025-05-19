define i32 @main() {
	%l0 = alloca i32, align 4
	%l1 = alloca i32, align 4 ; variable: a
	store i32 1, i32* %l1, align 4
	%t4 = load i32, i32* %l1, align 4
	%t2 = icmp eq i32 %t4, 1
	br i1 %t2, label %.L3, label %.L4
.L3:
	store i32 1, i32* %l0, align 4
	br label %.L2
.L4:
	%t5 = load i32, i32* %l1, align 4
	%t3 = icmp eq i32 %t5, 0
	br i1 %t3, label %.L6, label %.L7
.L6:
	store i32 0, i32* %l0, align 4
	br label %.L2
.L7:
	store i32 -1, i32* %l0, align 4
	br label %.L2
.L2:
	%t6 = load i32, i32* %l0, align 4
	ret i32 %t6
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
