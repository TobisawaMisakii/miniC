@a = global i32 1, align 4
@b = global i32 0, align 4
@c = global i32 1, align 4
@d = global i32 2, align 4
@e = global i32 4, align 4
declare i32 @getint(...);
declare float @getfloat(...);
declare i32 @getch(...);
declare i32 @getarray(i32);
declare i32 @getfarray(float);
declare void @putint(i32);
declare void @putfloat(float);
declare void @putch(i32);
declare void @putarray(i32, i32);
declare void @putfarray(i32, float);
declare void @putf(i32);
declare void @starttime(...);
declare void @stoptime(...);
define i32 @main()
{
	%l0 = alloca i32, align 4
	%l1 = alloca i32, align 4 ; 1:flag
	store i32 0, i32* %l1, align 4
	%t3 = load i32, i32* @a, align 4
	%t4 = load i32, i32* @b, align 4
	%t5 = mul i32 %t3, %t4
	%t6 = load i32, i32* @c, align 4
	%t7 = sdiv i32 %t5, %t6
	%t8 = load i32, i32* @e, align 4
	%t9 = load i32, i32* @d, align 4
	%t10 = add i32 %t8, %t9
	%t11 = icmp eq i32 %t7, %t10
	br i1 %t11, label %.L12, label %.L24
.L12:
	%t13 = load i32, i32* @a, align 4
	%t14 = load i32, i32* @a, align 4
	%t15 = load i32, i32* @b, align 4
	%t16 = add i32 %t14, %t15
	%t17 = mul i32 %t13, %t16
	%t18 = load i32, i32* @c, align 4
	%t19 = add i32 %t17, %t18
	%t20 = load i32, i32* @d, align 4
	%t21 = load i32, i32* @e, align 4
	%t22 = add i32 %t20, %t21
	%t23 = icmp sle i32 %t19, %t22
	br i1 %t23, label %.L36, label %.L24
.L24:
	%t25 = load i32, i32* @a, align 4
	%t26 = load i32, i32* @b, align 4
	%t27 = load i32, i32* @c, align 4
	%t28 = mul i32 %t26, %t27
	%t29 = sub i32 %t25, %t28
	%t30 = load i32, i32* @d, align 4
	%t31 = load i32, i32* @a, align 4
	%t32 = load i32, i32* @c, align 4
	%t33 = sdiv i32 %t31, %t32
	%t34 = sub i32 %t30, %t33
	%t35 = icmp eq i32 %t29, %t34
	br i1 %t35, label %.L36, label %.L38
.L36:
	store i32 1, i32* %l1, align 4
	br label %.L38
.L38:
	%t39 = load i32, i32* %l1, align 4
	call void @putint(i32 %t39)
	%t40 = load i32, i32* %l1, align 4
	store i32 %t40, i32* %l0, align 4
	br label %.L42
.L42:
	%t43 = load i32, i32* %l0, align 4
	ret i32 %t43
}
