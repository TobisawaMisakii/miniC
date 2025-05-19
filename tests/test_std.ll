define i32 @main() {
	%l0 = alloca i32, align 4
	%l1 = alloca i32, align 4 ; variable: a
	%l2 = alloca i32, align 4 ; variable: b
	%l3 = alloca i32, align 4 ; variable: a
	%l4 = alloca i32, align 4 ; variable: b
	%l5 = alloca i32, align 4 ; variable: a
	store i32 893, i32* %l1, align 4
	store i32 716, i32* %l2, align 4
	store i32 837, i32* %l3, align 4
	%t32 = load i32, i32* %l3, align 4
	%t6 = add nsw i32 %t32, 128
	store i32 %t6, i32* %l3, align 4
	%t33 = load i32, i32* %l2, align 4
	%t34 = load i32, i32* %l3, align 4
	%t7 = add nsw i32 %t33, %t34
	store i32 %t7, i32* %l2, align 4
	store i32 241, i32* %l4, align 4
	%t35 = load i32, i32* %l3, align 4
	%t36 = load i32, i32* %l4, align 4
	%t8 = add nsw i32 %t35, %t36
	%t9 = sub nsw i32 %t8, 412
	store i32 %t9, i32* %l3, align 4
	store i32 771, i32* %l5, align 4
	%t37 = load i32, i32* %l4, align 4
	%t38 = load i32, i32* %l5, align 4
	%t10 = add nsw i32 %t37, %t38
	%t11 = sub nsw i32 %t10, 18
	store i32 %t11, i32* %l4, align 4
	%t39 = load i32, i32* %l4, align 4
	%t12 = add nsw i32 %t39, 66
	store i32 %t12, i32* %l5, align 4
	%t40 = load i32, i32* %l4, align 4
	%t41 = load i32, i32* %l3, align 4
	%t13 = add nsw i32 %t40, %t41
	%t14 = sub nsw i32 %t13, 33
	store i32 %t14, i32* %l4, align 4
	%t42 = load i32, i32* %l4, align 4
	%t15 = sub nsw i32 %t42, 55
	store i32 %t15, i32* %l3, align 4
	%t43 = load i32, i32* %l3, align 4
	%t44 = load i32, i32* %l4, align 4
	%t16 = add nsw i32 %t43, %t44
	%t17 = srem i32 %t16, 21
	store i32 %t17, i32* %l0, align 4
	%t45 = load i32, i32* %l0, align 4
	ret i32 %t45
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
