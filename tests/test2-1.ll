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
	%l1 = alloca i32, align 4 ; 1:a
	%l2 = alloca i32, align 4 ; 1:b
	%l3 = alloca i32, align 4 ; 2:a
	%l4 = alloca i32, align 4 ; 3:b
	%l5 = alloca i32, align 4 ; 4:a
	store i32 893, i32* %l1, align 4
	store i32 716, i32* %l2, align 4
	store i32 837, i32* %l3, align 4
	%t9 = load i32, i32* %l3, align 4
	%t10 = add i32 %t9, 128
	store i32 %t10, i32* %l3, align 4
	%t12 = load i32, i32* %l2, align 4
	%t13 = load i32, i32* %l3, align 4
	%t14 = add i32 %t12, %t13
	store i32 %t14, i32* %l2, align 4
	store i32 241, i32* %l4, align 4
	%t17 = load i32, i32* %l3, align 4
	%t18 = load i32, i32* %l4, align 4
	%t19 = add i32 %t17, %t18
	%t20 = sub i32 %t19, 412
	store i32 %t20, i32* %l3, align 4
	store i32 771, i32* %l5, align 4
	%t23 = load i32, i32* %l4, align 4
	%t24 = load i32, i32* %l5, align 4
	%t25 = add i32 %t23, %t24
	%t26 = sub i32 %t25, 18
	store i32 %t26, i32* %l4, align 4
	%t28 = load i32, i32* %l4, align 4
	%t29 = add i32 %t28, 66
	store i32 %t29, i32* %l5, align 4
	%t31 = load i32, i32* %l4, align 4
	%t32 = load i32, i32* %l3, align 4
	%t33 = add i32 %t31, %t32
	%t34 = sub i32 %t33, 33
	store i32 %t34, i32* %l4, align 4
	%t36 = load i32, i32* %l4, align 4
	%t37 = sub i32 %t36, 55
	store i32 %t37, i32* %l3, align 4
	%t39 = load i32, i32* %l3, align 4
	%t40 = load i32, i32* %l4, align 4
	%t41 = add i32 %t39, %t40
	%t42 = srem i32 %t41, 21
	store i32 %t42, i32* %l0, align 4
	br label %.L79
	%t44 = load i32, i32* %l2, align 4
	%t45 = load i32, i32* %l3, align 4
	%t46 = add i32 %t44, %t45
	%t47 = sub i32 %t46, 97
	store i32 %t47, i32* %l3, align 4
	%t49 = load i32, i32* %l2, align 4
	%t50 = load i32, i32* %l3, align 4
	%t51 = sub i32 %t49, %t50
	%t52 = srem i32 %t51, 62
	store i32 %t52, i32* %l2, align 4
	%t54 = load i32, i32* %l3, align 4
	%t55 = load i32, i32* %l2, align 4
	%t56 = add i32 %t54, %t55
	%t57 = srem i32 %t56, 17
	store i32 %t57, i32* %l0, align 4
	br label %.L79
	%t59 = load i32, i32* %l3, align 4
	%t60 = load i32, i32* %l2, align 4
	%t61 = add i32 %t59, %t60
	%t62 = srem i32 %t61, 13
	store i32 %t62, i32* %l0, align 4
	br label %.L79
	%t64 = load i32, i32* %l2, align 4
	%t65 = load i32, i32* %l1, align 4
	%t66 = mul i32 %t64, %t65
	%t67 = srem i32 %t66, 83
	store i32 %t67, i32* %l1, align 4
	%t69 = load i32, i32* %l1, align 4
	%t70 = load i32, i32* %l2, align 4
	%t71 = add i32 %t69, %t70
	%t72 = sub i32 %t71, 771
	store i32 %t72, i32* %l2, align 4
	%t74 = load i32, i32* %l1, align 4
	%t75 = load i32, i32* %l2, align 4
	%t76 = add i32 %t74, %t75
	%t77 = srem i32 %t76, 11
	store i32 %t77, i32* %l0, align 4
	br label %.L79
.L79:
	%t80 = load i32, i32* %l0, align 4
	ret i32 %t80
}
