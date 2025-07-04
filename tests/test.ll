@e = global float 2.718282, align 4
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
define float @my_fabs(float %t0)
{
	%l1 = alloca float, align 4 ; 1:x
	%l2 = alloca float, align 4
	store float %t0, float* %l1, align 4
	%t4 = load float, float* %l1, align 4
	%t5 = fcmp ogt float %t4, 0
	br i1 %t5, label %.L6, label %.L9
.L6:
	%t7 = load float, float* %l1, align 4
	store float %t7, float* %l2, align 4
	br label %.L13
.L9:
	%t10 = load float, float* %l1, align 4
	%t11 = fsub float 0, %t10
	store float %t11, float* %l2, align 4
	br label %.L13
.L13:
	%t14 = load float, float* %l2, align 4
	ret float %t14
}
define float @my_pow(float %t0, i32 %t1)
{
	%l2 = alloca float, align 4 ; 1:a
	%l3 = alloca i32, align 4 ; 1:n
	%l4 = alloca float, align 4
	%l5 = alloca float, align 4 ; 1:res
	store float %t0, float* %l2, align 4
	store i32 %t1, i32* %l3, align 4
	%t8 = load i32, i32* %l3, align 4
	%t9 = icmp slt i32 %t8, 0
	br i1 %t9, label %.L10, label %.L17
.L10:
	%t11 = load float, float* %l2, align 4
	%t12 = load i32, i32* %l3, align 4
	%t13 = sub i32 0, %t12
	%t14 = call float @my_pow(float %t11, i32 %t13)
	%t15 = fdiv float 1, %t14
	store float %t15, float* %l4, align 4
	br label %.L44
.L17:
	store float 1.000000, float* %l5, align 4
	br label %.L19
.L19:
	%t20 = load i32, i32* %l3, align 4
	%t21 = icmp ne i32 %t20, 0
	br i1 %t21, label %.L22, label %.L41
.L22:
	%t23 = load i32, i32* %l3, align 4
	%t24 = srem i32 %t23, 2
	%t25 = icmp ne i32 %t24, 0
	br i1 %t25, label %.L26, label %.L32
.L26:
	%t27 = load float, float* %l5, align 4
	%t28 = load float, float* %l2, align 4
	store float %t30, float* %l5, align 4
	%t30 = fmul float %t31, %t28
	store float %t30, float* %l5, align 4
	br label %.L32
.L32:
	%t33 = load float, float* %l2, align 4
	%t34 = load float, float* %l2, align 4
	store float %t36, float* %l2, align 4
	%t36 = fmul float %t37, %t34
	store float %t36, float* %l2, align 4
	%t38 = load i32, i32* %l3, align 4
	%t39 = sdiv i32 %t38, 2
	store i32 %t39, i32* %l3, align 4
	br label %.L19
.L41:
	%t42 = load float, float* %l5, align 4
	store float %t42, float* %l4, align 4
	br label %.L44
.L44:
	%t45 = load float, float* %l4, align 4
	ret float %t45
}
define float @my_sqrt(float %t0)
{
	%l1 = alloca float, align 4 ; 1:x
	%l2 = alloca float, align 4
	%l3 = alloca float, align 4 ; 1:t
	%l4 = alloca i32, align 4 ; 1:c
	store float %t0, float* %l1, align 4
	%t6 = load float, float* %l1, align 4
	%t7 = fcmp ogt float %t6, 100
	br i1 %t7, label %.L8, label %.L15
.L8:
	%t9 = load float, float* %l1, align 4
	%t10 = fdiv float %t9, 100
	%t11 = call float @my_sqrt(float %t10)
	store float %t13, float* %l2, align 4
	%t13 = fmul float %t14, %t11
	store float %t13, float* %l2, align 4
	br label %.L46
.L15:
	%t16 = load float, float* %l1, align 4
	%t17 = fdiv float %t16, 8
	%t18 = fadd float %t17, 0.500000
	%t19 = load float, float* %l1, align 4
	%t20 = sitofp i32 2 to float
	%t21 = fmul float %t20, %t19
	%t22 = load float, float* %l1, align 4
	%t23 = fadd float %t24, %t22
	%t24 = sitofp i32 4 to float
	%t25 = fdiv float %t21, %t23
	%t26 = fadd float %t18, %t25
	store float %t26, float* %l3, align 4
	store i32 10, i32* %l4, align 4
	br label %.L29
.L29:
	%t30 = load i32, i32* %l4, align 4
	%t31 = icmp ne i32 %t30, 0
	br i1 %t31, label %.L32, label %.L43
.L32:
	%t33 = load float, float* %l3, align 4
	%t34 = load float, float* %l1, align 4
	%t35 = load float, float* %l3, align 4
	%t36 = fdiv float %t34, %t35
	%t37 = fadd float %t33, %t36
	%t38 = fdiv float %t37, 2
	store float %t38, float* %l3, align 4
	%t40 = load i32, i32* %l4, align 4
	%t41 = sub i32 %t40, 1
	store i32 %t41, i32* %l4, align 4
	br label %.L29
.L43:
	%t44 = load float, float* %l3, align 4
	store float %t44, float* %l2, align 4
	br label %.L46
.L46:
	%t47 = load float, float* %l2, align 4
	ret float %t47
}
define float @F1(float %t0)
{
	%l1 = alloca float, align 4 ; 1:x
	%l2 = alloca float, align 4
	store float %t0, float* %l1, align 4
	%t4 = load float, float* %l1, align 4
	%t5 = fdiv float 1, %t4
	store float %t5, float* %l2, align 4
	br label %.L7
.L7:
	%t8 = load float, float* %l2, align 4
	ret float %t8
}
define float @F2(float %t0)
{
	%l1 = alloca float, align 4 ; 1:x
	%l2 = alloca float, align 4
	store float %t0, float* %l1, align 4
	%t4 = load float, float* %l1, align 4
	%t5 = load float, float* %l1, align 4
	%t8 = sitofp i32 1 to float
	%t7 = fmul float %t8, %t5
	%t8 = sitofp i32 1 to float
	%t9 = fsub float %t8, %t7
	%t10 = call float @my_sqrt(float %t9)
	%t11 = fdiv float 1, %t10
	store float %t11, float* %l2, align 4
	br label %.L13
.L13:
	%t14 = load float, float* %l2, align 4
	ret float %t14
}
define float @simpson(float %t0, float %t1, i32 %t2)
{
	%l3 = alloca float, align 4 ; 1:a
	%l4 = alloca float, align 4 ; 1:b
	%l5 = alloca i32, align 4 ; 1:flag
	%l6 = alloca float, align 4
	%l7 = alloca float, align 4 ; 1:c
	store float %t0, float* %l3, align 4
	store float %t1, float* %l4, align 4
	store i32 %t2, i32* %l5, align 4
	%t11 = load float, float* %l3, align 4
	%t12 = load float, float* %l4, align 4
	%t13 = load float, float* %l3, align 4
	%t14 = fsub float %t12, %t13
	%t15 = fdiv float %t14, 2
	%t16 = fadd float %t11, %t15
	store float %t16, float* %l7, align 4
	%t18 = load i32, i32* %l5, align 4
	%t19 = icmp eq i32 %t18, 1
	br i1 %t19, label %.L20, label %.L38
.L20:
	%t21 = load float, float* %l3, align 4
	%t22 = call float @F1(float %t21)
	%t23 = load float, float* %l7, align 4
	%t24 = call float @F1(float %t23)
	%t25 = sitofp i32 4 to float
	%t26 = fmul float %t25, %t24
	%t27 = fadd float %t22, %t26
	%t28 = load float, float* %l4, align 4
	%t29 = call float @F1(float %t28)
	%t30 = fadd float %t27, %t29
	%t31 = load float, float* %l4, align 4
	%t32 = load float, float* %l3, align 4
	%t33 = fsub float %t31, %t32
	store float %t36, float* %l6, align 4
	%t35 = fmul float %t37, %t33
	%t36 = fdiv float %t35, 6
	store float %t36, float* %l6, align 4
	br label %.L61
.L38:
	%t39 = load i32, i32* %l5, align 4
	%t40 = icmp eq i32 %t39, 2
	br i1 %t40, label %.L41, label %.L59
.L41:
	%t42 = load float, float* %l3, align 4
	%t43 = call float @F2(float %t42)
	%t44 = load float, float* %l7, align 4
	%t45 = call float @F2(float %t44)
	%t46 = sitofp i32 4 to float
	%t47 = fmul float %t46, %t45
	%t48 = fadd float %t43, %t47
	%t49 = load float, float* %l4, align 4
	%t50 = call float @F2(float %t49)
	%t51 = fadd float %t48, %t50
	%t52 = load float, float* %l4, align 4
	%t53 = load float, float* %l3, align 4
	%t54 = fsub float %t52, %t53
	store float %t57, float* %l6, align 4
	%t56 = fmul float %t58, %t54
	%t57 = fdiv float %t56, 6
	store float %t57, float* %l6, align 4
	br label %.L61
.L59:
	store i32 0, float* %l6, align 4
	br label %.L61
.L61:
	%t62 = load float, float* %l6, align 4
	ret float %t62
}
define float @asr5(float %t0, float %t1, float %t2, float %t3, i32 %t4)
{
	%l5 = alloca float, align 4 ; 1:a
	%l6 = alloca float, align 4 ; 1:b
	%l7 = alloca float, align 4 ; 1:eps
	%l8 = alloca float, align 4 ; 1:A
	%l9 = alloca i32, align 4 ; 1:flag
	%l10 = alloca float, align 4
	%l11 = alloca float, align 4 ; 1:c
	%l12 = alloca float, align 4 ; 1:L
	%l13 = alloca float, align 4 ; 1:R
	store float %t0, float* %l5, align 4
	store float %t1, float* %l6, align 4
	store float %t2, float* %l7, align 4
	store float %t3, float* %l8, align 4
	store i32 %t4, i32* %l9, align 4
	%t19 = load float, float* %l5, align 4
	%t20 = load float, float* %l6, align 4
	%t21 = load float, float* %l5, align 4
	%t22 = fsub float %t20, %t21
	%t23 = fdiv float %t22, 2
	%t24 = fadd float %t19, %t23
	store float %t24, float* %l11, align 4
	%t26 = load float, float* %l5, align 4
	%t27 = load float, float* %l11, align 4
	%t28 = load i32, i32* %l9, align 4
	%t29 = call float @simpson(float %t26, float %t27, i32 %t28)
	store float %t29, float* %l12, align 4
	%t31 = load float, float* %l11, align 4
	%t32 = load float, float* %l6, align 4
	%t33 = load i32, i32* %l9, align 4
	%t34 = call float @simpson(float %t31, float %t32, i32 %t33)
	store float %t34, float* %l13, align 4
	%t36 = load float, float* %l12, align 4
	%t37 = load float, float* %l13, align 4
	%t38 = fadd float %t36, %t37
	%t39 = load float, float* %l8, align 4
	%t40 = fsub float %t38, %t39
	%t41 = call float @my_fabs(float %t40)
	%t42 = load float, float* %l7, align 4
	%t43 = sitofp i32 15 to float
	%t44 = fmul float %t43, %t42
	%t45 = fcmp ole float %t41, %t44
	br i1 %t45, label %.L46, label %.L58
.L46:
	%t47 = load float, float* %l12, align 4
	%t48 = load float, float* %l13, align 4
	%t49 = fadd float %t47, %t48
	%t50 = load float, float* %l12, align 4
	%t51 = load float, float* %l13, align 4
	%t52 = fadd float %t50, %t51
	%t53 = load float, float* %l8, align 4
	%t54 = fsub float %t52, %t53
	%t55 = fdiv float %t54, 15.000000
	%t56 = fadd float %t49, %t55
	store float %t56, float* %l10, align 4
	br label %.L75
.L58:
	%t59 = load float, float* %l5, align 4
	%t60 = load float, float* %l11, align 4
	%t61 = load float, float* %l7, align 4
	%t62 = fdiv float %t61, 2
	%t63 = load float, float* %l12, align 4
	%t64 = load i32, i32* %l9, align 4
	%t65 = call float @asr5(float %t59, float %t60, float %t62, float %t63, i32 %t64)
	%t66 = load float, float* %l11, align 4
	%t67 = load float, float* %l6, align 4
	%t68 = load float, float* %l7, align 4
	%t69 = fdiv float %t68, 2
	%t70 = load float, float* %l13, align 4
	%t71 = load i32, i32* %l9, align 4
	%t72 = call float @asr5(float %t66, float %t67, float %t69, float %t70, i32 %t71)
	%t73 = fadd float %t65, %t72
	store float %t73, float* %l10, align 4
	br label %.L75
.L75:
	%t76 = load float, float* %l10, align 4
	ret float %t76
}
define float @asr4(float %t0, float %t1, float %t2, i32 %t3)
{
	%l4 = alloca float, align 4 ; 1:a
	%l5 = alloca float, align 4 ; 1:b
	%l6 = alloca float, align 4 ; 1:eps
	%l7 = alloca i32, align 4 ; 1:flag
	%l8 = alloca float, align 4
	store float %t0, float* %l4, align 4
	store float %t1, float* %l5, align 4
	store float %t2, float* %l6, align 4
	store i32 %t3, i32* %l7, align 4
	%t13 = load float, float* %l4, align 4
	%t14 = load float, float* %l5, align 4
	%t15 = load float, float* %l6, align 4
	%t16 = load float, float* %l4, align 4
	%t17 = load float, float* %l5, align 4
	%t18 = load i32, i32* %l7, align 4
	%t19 = call float @simpson(float %t16, float %t17, i32 %t18)
	%t20 = load i32, i32* %l7, align 4
	%t21 = call float @asr5(float %t13, float %t14, float %t15, float %t19, i32 %t20)
	store float %t21, float* %l8, align 4
	br label %.L23
.L23:
	%t24 = load float, float* %l8, align 4
	ret float %t24
}
define float @eee(float %t0)
{
	%l1 = alloca float, align 4 ; 1:x
	%l2 = alloca float, align 4
	%l3 = alloca float, align 4 ; 2:ee
	store float %t0, float* %l1, align 4
	%t5 = load float, float* %l1, align 4
	%t6 = fcmp ogt float %t5, 0.001000
	br i1 %t6, label %.L7, label %.L17
.L7:
	%t8 = load float, float* %l1, align 4
	%t9 = fdiv float %t8, 2
	%t10 = call float @eee(float %t9)
	store float %t10, float* %l3, align 4
	%t12 = load float, float* %l3, align 4
	%t13 = load float, float* %l3, align 4
	store float %t15, float* %l2, align 4
	%t15 = fmul float %t16, %t13
	store float %t15, float* %l2, align 4
	br label %.L40
.L17:
	%t18 = load float, float* %l1, align 4
	%t19 = fadd float %t20, %t18
	%t20 = sitofp i32 1 to float
	%t21 = load float, float* %l1, align 4
	%t22 = load float, float* %l1, align 4
	%t27 = load float, float* %l1, align 4
	%t24 = fmul float %t27, %t22
	%t25 = fdiv float %t24, 2
	%t26 = fadd float %t19, %t25
	%t27 = load float, float* %l1, align 4
	%t28 = call float @my_pow(float %t27, i32 3)
	%t29 = fdiv float %t28, 6
	%t30 = fadd float %t26, %t29
	%t31 = load float, float* %l1, align 4
	%t32 = call float @my_pow(float %t31, i32 4)
	%t33 = fdiv float %t32, 24
	%t34 = fadd float %t30, %t33
	%t35 = load float, float* %l1, align 4
	%t36 = call float @my_pow(float %t35, i32 5)
	%t37 = fdiv float %t36, 120
	%t38 = fadd float %t34, %t37
	store float %t38, float* %l2, align 4
	br label %.L40
.L40:
	%t41 = load float, float* %l2, align 4
	ret float %t41
}
define float @my_exp(float %t0)
{
	%l1 = alloca float, align 4 ; 1:x
	%l2 = alloca float, align 4
	%l3 = alloca i32, align 4 ; 1:n
	%l4 = alloca float, align 4 ; 1:e1
	%l5 = alloca float, align 4 ; 1:e2
	store float %t0, float* %l1, align 4
	%t7 = load float, float* %l1, align 4
	%t8 = fcmp olt float%t7, 0
	br i1 %t8, label %.L9, label %.L15
.L9:
	%t10 = load float, float* %l1, align 4
	%t11 = fsub float 0, %t10
	%t12 = call float @my_exp(float %t11)
	%t13 = fdiv float 1, %t12
	store float %t13, float* %l2, align 4
	br label %.L34
.L15:
	%t16 = load float, float* %l1, align 4
	store float %t16, i32* %l3, align 4
	%t18 = load float, float* %l1, align 4
	%t19 = load i32, i32* %l3, align 4
	%t20 = sitofp i32 %t19 to float
	%t21 = fsub float %t18, %t20
	store float %t21, float* %l1, align 4
	%t23 = load i32, i32* %l3, align 4
	%t24 = call float @my_pow(float 2.718282, i32 %t23)
	store float %t24, float* %l4, align 4
	%t26 = load float, float* %l1, align 4
	%t27 = call float @eee(float %t26)
	store float %t27, float* %l5, align 4
	%t29 = load float, float* %l4, align 4
	%t30 = load float, float* %l5, align 4
	store float %t32, float* %l2, align 4
	%t32 = fmul float %t33, %t30
	store float %t32, float* %l2, align 4
	br label %.L34
.L34:
	%t35 = load float, float* %l2, align 4
	ret float %t35
}
define float @my_ln(float %t0)
{
	%l1 = alloca float, align 4 ; 1:x
	%l2 = alloca float, align 4
	store float %t0, float* %l1, align 4
	%t4 = load float, float* %l1, align 4
	%t5 = call float @asr4(float 1, float %t4, float 0.000000, i32 1)
	store float %t5, float* %l2, align 4
	br label %.L7
.L7:
	%t8 = load float, float* %l2, align 4
	ret float %t8
}
define float @my_log(float %t0, float %t1)
{
	%l2 = alloca float, align 4 ; 1:a
	%l3 = alloca float, align 4 ; 1:N
	%l4 = alloca float, align 4
	store float %t0, float* %l2, align 4
	store float %t1, float* %l3, align 4
	%t7 = load float, float* %l3, align 4
	%t8 = call float @my_ln(float %t7)
	%t9 = load float, float* %l2, align 4
	%t10 = call float @my_ln(float %t9)
	%t11 = fdiv float %t8, %t10
	store float %t11, float* %l4, align 4
	br label %.L13
.L13:
	%t14 = load float, float* %l4, align 4
	ret float %t14
}
define float @my_powf(float %t0, float %t1)
{
	%l2 = alloca float, align 4 ; 1:a
	%l3 = alloca float, align 4 ; 1:x
	%l4 = alloca float, align 4
	store float %t0, float* %l2, align 4
	store float %t1, float* %l3, align 4
	%t7 = load float, float* %l3, align 4
	%t8 = load float, float* %l2, align 4
	%t9 = call float @my_ln(float %t8)
	store float %t12, float* %l4, align 4
	%t11 = fmul float %t13, %t9
	%t12 = call float @my_exp(float %t11)
	store float %t12, float* %l4, align 4
	br label %.L14
.L14:
	%t15 = load float, float* %l4, align 4
	ret float %t15
}
define i32 @main()
{
	%l0 = alloca i32, align 4
	%l1 = alloca i32, align 4 ; 1:num
	%l2 = alloca float, align 4 ; 2:x
	%l3 = alloca float, align 4 ; 2:y
	%t4 = call i32 (...) @getint()
	store i32 %t4, i32* %l1, align 4
	br label %.L6
.L6:
	%t7 = load i32, i32* %l1, align 4
	%t8 = icmp ne i32 %t7, 0
	br i1 %t8, label %.L9, label %.L51
.L9:
	%t10 = call float (...) @getfloat()
	store float %t10, float* %l2, align 4
	%t12 = call float (...) @getfloat()
	store float %t12, float* %l3, align 4
	%t14 = load float, float* %l2, align 4
	%t15 = call float @my_fabs(float %t14)
	call void @putfloat(float %t15)
	call void @putch(i32 32)
	%t16 = load float, float* %l2, align 4
	%t17 = call float @my_pow(float %t16, i32 2)
	call void @putfloat(float %t17)
	call void @putch(i32 32)
	%t18 = load float, float* %l2, align 4
	%t19 = call float @my_sqrt(float %t18)
	call void @putfloat(float %t19)
	call void @putch(i32 32)
	%t20 = load float, float* %l2, align 4
	%t21 = call float @my_exp(float %t20)
	call void @putfloat(float %t21)
	call void @putch(i32 32)
	%t22 = load float, float* %l2, align 4
	%t23 = fcmp ogt float %t22, 0
	br i1 %t23, label %.L24, label %.L27
.L24:
	%t25 = load float, float* %l2, align 4
	%t26 = call float @my_ln(float %t25)
	call void @putfloat(float %t26)
	br label %.L28
.L27:
	call void @putch(i32 45)
	br label %.L28
.L28:
	call void @putch(i32 32)
	%t29 = load float, float* %l2, align 4
	%t30 = fcmp ogt float %t29, 0
	br i1 %t30, label %.L31, label %.L38
.L31:
	%t32 = load float, float* %l3, align 4
	%t33 = fcmp ogt float %t32, 0
	br i1 %t33, label %.L34, label %.L38
.L34:
	%t35 = load float, float* %l2, align 4
	%t36 = load float, float* %l3, align 4
	%t37 = call float @my_log(float %t35, float %t36)
	call void @putfloat(float %t37)
	br label %.L39
.L38:
	call void @putch(i32 45)
	br label %.L39
.L39:
	call void @putch(i32 32)
	%t40 = load float, float* %l2, align 4
	%t41 = fcmp ogt float %t40, 0
	br i1 %t41, label %.L42, label %.L46
.L42:
	%t43 = load float, float* %l2, align 4
	%t44 = load float, float* %l3, align 4
	%t45 = call float @my_powf(float %t43, float %t44)
	call void @putfloat(float %t45)
	br label %.L47
.L46:
	call void @putch(i32 45)
	br label %.L47
.L47:
	call void @putch(i32 10)
	%t48 = load i32, i32* %l1, align 4
	%t49 = sub i32 %t48, 1
	store i32 %t49, i32* %l1, align 4
	br label %.L6
.L51:
	store i32 0, i32* %l0, align 4
	br label %.L53
.L53:
	%t54 = load i32, i32* %l0, align 4
	ret i32 %t54
}
