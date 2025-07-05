@e = global float 0x4005bf0a80000000, align 4
declare i32 @getint(...);
declare float @getfloat(...);
declare i32 @getch(...);
declare dso_local i32 @getarray(...)
declare dso_local float @getfarray(...)
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
	%t4 = sitofp i32 0 to float
	%t5 = load float, float* %l1, align 4
	%t6 = fcmp ogt float %t5, %t4
	br i1 %t6, label %.L7, label %.L10
.L7:
	%t8 = load float, float* %l1, align 4
	store float %t8, float* %l2, align 4
	br label %.L14
.L10:
	%t11 = load float, float* %l1, align 4
	%t12 = fsub float 0.0, %t11
	store float %t12, float* %l2, align 4
	br label %.L14
.L14:
	%t15 = load float, float* %l2, align 4
	ret float %t15
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
	br i1 %t9, label %.L10, label %.L18
.L10:
	%t11 = sitofp i32 1 to float
	%t12 = load float, float* %l2, align 4
	%t13 = load i32, i32* %l3, align 4
	%t14 = sub i32 0, %t13
	%t15 = call float @my_pow(float %t12, i32 %t14)
	%t16 = fdiv float %t11, %t15
	store float %t16, float* %l4, align 4
	br label %.L43
.L18:
	store float 0x3ff0000000000000, float* %l5, align 4
	br label %.L20
.L20:
	%t21 = load i32, i32* %l3, align 4
	%t22 = icmp ne i32 %t21, 0
	br i1 %t22, label %.L23, label %.L40
.L23:
	%t24 = load i32, i32* %l3, align 4
	%t25 = srem i32 %t24, 2
	%t26 = icmp ne i32 %t25, 0
	br i1 %t26, label %.L27, label %.L32
.L27:
	%t28 = load float, float* %l5, align 4
	%t29 = load float, float* %l2, align 4
	%t30 = fmul float %t28, %t29
	store float %t30, float* %l5, align 4
	br label %.L32
.L32:
	%t33 = load float, float* %l2, align 4
	%t34 = load float, float* %l2, align 4
	%t35 = fmul float %t33, %t34
	store float %t35, float* %l2, align 4
	%t37 = load i32, i32* %l3, align 4
	%t38 = sdiv i32 %t37, 2
	store i32 %t38, i32* %l3, align 4
	br label %.L20
.L40:
	%t41 = load float, float* %l5, align 4
	store float %t41, float* %l4, align 4
	br label %.L43
.L43:
	%t44 = load float, float* %l4, align 4
	ret float %t44
}
define float @my_sqrt(float %t0)
{
	%l1 = alloca float, align 4 ; 1:x
	%l2 = alloca float, align 4
	%l3 = alloca float, align 4 ; 1:t
	%l4 = alloca i32, align 4 ; 1:c
	store float %t0, float* %l1, align 4
	%t6 = sitofp i32 100 to float
	%t7 = load float, float* %l1, align 4
	%t8 = fcmp ogt float %t7, %t6
	br i1 %t8, label %.L9, label %.L16
.L9:
	%t10 = sitofp i32 100 to float
	%t11 = load float, float* %l1, align 4
	%t12 = fdiv float %t11, %t10
	%t13 = call float @my_sqrt(float %t12)
	%t14 = fmul float 0x4024000000000000, %t13
	store float %t14, float* %l2, align 4
	br label %.L49
.L16:
	%t17 = sitofp i32 8 to float
	%t18 = load float, float* %l1, align 4
	%t19 = fdiv float %t18, %t17
	%t20 = fadd float %t19, 0x3fe0000000000000
	%t21 = load float, float* %l1, align 4
	%t22 = sitofp i32 2 to float
	%t23 = fmul float %t22, %t21
	%t24 = load float, float* %l1, align 4
	%t25 = sitofp i32 4 to float
	%t26 = fadd float %t25, %t24
	%t27 = fdiv float %t23, %t26
	%t28 = fadd float %t20, %t27
	store float %t28, float* %l3, align 4
	store i32 10, i32* %l4, align 4
	br label %.L31
.L31:
	%t32 = load i32, i32* %l4, align 4
	%t33 = icmp ne i32 %t32, 0
	br i1 %t33, label %.L34, label %.L46
.L34:
	%t35 = sitofp i32 2 to float
	%t36 = load float, float* %l3, align 4
	%t37 = load float, float* %l1, align 4
	%t38 = load float, float* %l3, align 4
	%t39 = fdiv float %t37, %t38
	%t40 = fadd float %t36, %t39
	%t41 = fdiv float %t40, %t35
	store float %t41, float* %l3, align 4
	%t43 = load i32, i32* %l4, align 4
	%t44 = sub i32 %t43, 1
	store i32 %t44, i32* %l4, align 4
	br label %.L31
.L46:
	%t47 = load float, float* %l3, align 4
	store float %t47, float* %l2, align 4
	br label %.L49
.L49:
	%t50 = load float, float* %l2, align 4
	ret float %t50
}
define float @F1(float %t0)
{
	%l1 = alloca float, align 4 ; 1:x
	%l2 = alloca float, align 4
	store float %t0, float* %l1, align 4
	%t4 = sitofp i32 1 to float
	%t5 = load float, float* %l1, align 4
	%t6 = sitofp i32 1 to float
	%t7 = fsub float %t5, %t6
	%t8 = call float @F1(float %t7)
	%t9 = fdiv float %t4, %t8
	%t10 = sitofp i32 1 to float
	%t11 = fsub float %t10, %t9
	%t12 = sitofp i32 1 to float
	%t13 = fadd float %t11, %t12
	store float %t13, float* %l2, align 4
	br label %.L15
.L15:
	%t16 = load float, float* %l2, align 4
	ret float %t16
}
define float @F2(float %t0)
{
	%l1 = alloca float, align 4 ; 1:x
	%l2 = alloca float, align 4
	store float %t0, float* %l1, align 4
	%t4 = sitofp i32 1 to float
	%t5 = load float, float* %l1, align 4
	%t6 = load float, float* %l1, align 4
	%t7 = fmul float %t5, %t6
	%t8 = sitofp i32 1 to float
	%t9 = fsub float %t8, %t7
	%t10 = call float @my_sqrt(float %t9)
	%t11 = fdiv float %t4, %t10
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
	%t12 = sitofp i32 2 to float
	%t13 = load float, float* %l4, align 4
	%t14 = load float, float* %l3, align 4
	%t15 = fsub float %t13, %t14
	%t16 = fdiv float %t15, %t12
	%t17 = fadd float %t11, %t16
	store float %t17, float* %l7, align 4
	%t19 = load i32, i32* %l5, align 4
	%t20 = icmp eq i32 %t19, 1
	br i1 %t20, label %.L21, label %.L39
.L21:
	%t22 = sitofp i32 6 to float
	%t23 = load float, float* %l3, align 4
	%t24 = call float @F1(float %t23)
	%t25 = load float, float* %l7, align 4
	%t26 = call float @F1(float %t25)
	%t27 = sitofp i32 4 to float
	%t28 = fmul float %t27, %t26
	%t29 = fadd float %t24, %t28
	%t30 = load float, float* %l4, align 4
	%t31 = call float @F1(float %t30)
	%t32 = fadd float %t29, %t31
	%t33 = load float, float* %l4, align 4
	%t34 = load float, float* %l3, align 4
	%t35 = fsub float %t33, %t34
	%t36 = fmul float %t32, %t35
	%t37 = fdiv float %t36, %t22
	store float %t37, float* %l6, align 4
	br label %.L63
.L39:
	%t40 = load i32, i32* %l5, align 4
	%t41 = icmp eq i32 %t40, 2
	br i1 %t41, label %.L42, label %.L60
.L42:
	%t43 = sitofp i32 6 to float
	%t44 = load float, float* %l3, align 4
	%t45 = call float @F2(float %t44)
	%t46 = load float, float* %l7, align 4
	%t47 = call float @F2(float %t46)
	%t48 = sitofp i32 4 to float
	%t49 = fmul float %t48, %t47
	%t50 = fadd float %t45, %t49
	%t51 = load float, float* %l4, align 4
	%t52 = call float @F2(float %t51)
	%t53 = fadd float %t50, %t52
	%t54 = load float, float* %l4, align 4
	%t55 = load float, float* %l3, align 4
	%t56 = fsub float %t54, %t55
	%t57 = fmul float %t53, %t56
	%t58 = fdiv float %t57, %t43
	store float %t58, float* %l6, align 4
	br label %.L63
.L60:
	%t61 = sitofp i32 0 to float
	store float %t61, float* %l6, align 4
	br label %.L63
.L63:
	%t64 = load float, float* %l6, align 4
	ret float %t64
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
	%t20 = sitofp i32 2 to float
	%t21 = load float, float* %l6, align 4
	%t22 = load float, float* %l5, align 4
	%t23 = fsub float %t21, %t22
	%t24 = fdiv float %t23, %t20
	%t25 = fadd float %t19, %t24
	store float %t25, float* %l11, align 4
	%t27 = load float, float* %l5, align 4
	%t28 = load float, float* %l11, align 4
	%t29 = load i32, i32* %l9, align 4
	%t30 = call float @simpson(float %t27, float %t28, i32 %t29)
	store float %t30, float* %l12, align 4
	%t32 = load float, float* %l11, align 4
	%t33 = load float, float* %l6, align 4
	%t34 = load i32, i32* %l9, align 4
	%t35 = call float @simpson(float %t32, float %t33, i32 %t34)
	store float %t35, float* %l13, align 4
	%t37 = load float, float* %l12, align 4
	%t38 = load float, float* %l13, align 4
	%t39 = fadd float %t37, %t38
	%t40 = load float, float* %l8, align 4
	%t41 = fsub float %t39, %t40
	%t42 = call float @my_fabs(float %t41)
	%t43 = load float, float* %l7, align 4
	%t44 = sitofp i32 15 to float
	%t45 = fmul float %t44, %t43
	%t46 = fcmp ole float %t42, %t45
	br i1 %t46, label %.L47, label %.L59
.L47:
	%t48 = load float, float* %l12, align 4
	%t49 = load float, float* %l13, align 4
	%t50 = fadd float %t48, %t49
	%t51 = load float, float* %l12, align 4
	%t52 = load float, float* %l13, align 4
	%t53 = fadd float %t51, %t52
	%t54 = load float, float* %l8, align 4
	%t55 = fsub float %t53, %t54
	%t56 = fdiv float %t55, 0x402e000000000000
	%t57 = fadd float %t50, %t56
	store float %t57, float* %l10, align 4
	br label %.L78
.L59:
	%t60 = load float, float* %l5, align 4
	%t61 = load float, float* %l11, align 4
	%t62 = sitofp i32 2 to float
	%t63 = load float, float* %l7, align 4
	%t64 = fdiv float %t63, %t62
	%t65 = load float, float* %l12, align 4
	%t66 = load i32, i32* %l9, align 4
	%t67 = call float @asr5(float %t60, float %t61, float %t64, float %t65, i32 %t66)
	%t68 = load float, float* %l11, align 4
	%t69 = load float, float* %l6, align 4
	%t70 = sitofp i32 2 to float
	%t71 = load float, float* %l7, align 4
	%t72 = fdiv float %t71, %t70
	%t73 = load float, float* %l13, align 4
	%t74 = load i32, i32* %l9, align 4
	%t75 = call float @asr5(float %t68, float %t69, float %t72, float %t73, i32 %t74)
	%t76 = fadd float %t67, %t75
	store float %t76, float* %l10, align 4
	br label %.L78
.L78:
	%t79 = load float, float* %l10, align 4
	ret float %t79
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
	%t6 = fcmp ogt float %t5, 0x3f50624de0000000
	br i1 %t6, label %.L7, label %.L17
.L7:
	%t8 = sitofp i32 2 to float
	%t9 = load float, float* %l1, align 4
	%t10 = fdiv float %t9, %t8
	%t11 = call float @eee(float %t10)
	store float %t11, float* %l3, align 4
	%t13 = load float, float* %l3, align 4
	%t14 = load float, float* %l3, align 4
	%t15 = fmul float %t13, %t14
	store float %t15, float* %l2, align 4
	br label %.L43
.L17:
	%t18 = load float, float* %l1, align 4
	%t19 = sitofp i32 1 to float
	%t20 = fadd float %t19, %t18
	%t21 = sitofp i32 2 to float
	%t22 = load float, float* %l1, align 4
	%t23 = load float, float* %l1, align 4
	%t24 = fmul float %t22, %t23
	%t25 = fdiv float %t24, %t21
	%t26 = fadd float %t20, %t25
	%t27 = sitofp i32 6 to float
	%t28 = load float, float* %l1, align 4
	%t29 = call float @my_pow(float %t28, i32 3)
	%t30 = fdiv float %t29, %t27
	%t31 = fadd float %t26, %t30
	%t32 = sitofp i32 24 to float
	%t33 = load float, float* %l1, align 4
	%t34 = call float @my_pow(float %t33, i32 4)
	%t35 = fdiv float %t34, %t32
	%t36 = fadd float %t31, %t35
	%t37 = sitofp i32 120 to float
	%t38 = load float, float* %l1, align 4
	%t39 = call float @my_pow(float %t38, i32 5)
	%t40 = fdiv float %t39, %t37
	%t41 = fadd float %t36, %t40
	store float %t41, float* %l2, align 4
	br label %.L43
.L43:
	%t44 = load float, float* %l2, align 4
	ret float %t44
}
define float @my_exp(float %t0)
{
	%l1 = alloca float, align 4 ; 1:x
	%l2 = alloca float, align 4
	%l3 = alloca i32, align 4 ; 1:n
	%l4 = alloca float, align 4 ; 1:e1
	%l5 = alloca float, align 4 ; 1:e2
	store float %t0, float* %l1, align 4
	%t7 = sitofp i32 0 to float
	%t8 = load float, float* %l1, align 4
	%t9 = fcmp olt float%t8, %t7
	br i1 %t9, label %.L10, label %.L17
.L10:
	%t11 = sitofp i32 1 to float
	%t12 = load float, float* %l1, align 4
	%t13 = fsub float 0.0, %t12
	%t14 = call float @my_exp(float %t13)
	%t15 = fdiv float %t11, %t14
	store float %t15, float* %l2, align 4
	br label %.L36
.L17:
	%t18 = fptosi float %t19 to i32
	%t19 = load float, float* %l1, align 4
	store i32 %t18, i32* %l3, align 4
	%t21 = load float, float* %l1, align 4
	%t22 = load i32, i32* %l3, align 4
	%t23 = sitofp i32 %t22 to float
	%t24 = fsub float %t21, %t23
	store float %t24, float* %l1, align 4
	%t26 = load i32, i32* %l3, align 4
	%t27 = call float @my_pow(float 0x4005bf0a80000000, i32 %t26)
	store float %t27, float* %l4, align 4
	%t29 = load float, float* %l1, align 4
	%t30 = call float @eee(float %t29)
	store float %t30, float* %l5, align 4
	%t32 = load float, float* %l4, align 4
	%t33 = load float, float* %l5, align 4
	%t34 = fmul float %t32, %t33
	store float %t34, float* %l2, align 4
	br label %.L36
.L36:
	%t37 = load float, float* %l2, align 4
	ret float %t37
}
define float @my_ln(float %t0)
{
	%l1 = alloca float, align 4 ; 1:x
	%l2 = alloca float, align 4
	store float %t0, float* %l1, align 4
	%t4 = load float, float* %l1, align 4
	%t5 = sitofp i32 1 to float
	%t6 = call float @asr4(float %t5, float %t4, float 0x3e45798ee0000000, i32 1)
	store float %t6, float* %l2, align 4
	br label %.L8
.L8:
	%t9 = load float, float* %l2, align 4
	ret float %t9
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
	%t10 = fmul float %t7, %t9
	%t11 = call float @my_exp(float %t10)
	store float %t11, float* %l4, align 4
	br label %.L13
.L13:
	%t14 = load float, float* %l4, align 4
	ret float %t14
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
	br i1 %t8, label %.L9, label %.L55
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
	%t22 = sitofp i32 0 to float
	%t23 = load float, float* %l2, align 4
	%t24 = fcmp ogt float %t23, %t22
	br i1 %t24, label %.L25, label %.L28
.L25:
	%t26 = load float, float* %l2, align 4
	%t27 = call float @my_ln(float %t26)
	call void @putfloat(float %t27)
	br label %.L29
.L28:
	call void @putch(i32 45)
	br label %.L29
.L29:
	call void @putch(i32 32)
	%t30 = sitofp i32 0 to float
	%t31 = load float, float* %l2, align 4
	%t32 = fcmp ogt float %t31, %t30
	br i1 %t32, label %.L33, label %.L41
.L33:
	%t34 = sitofp i32 0 to float
	%t35 = load float, float* %l3, align 4
	%t36 = fcmp ogt float %t35, %t34
	br i1 %t36, label %.L37, label %.L41
.L37:
	%t38 = load float, float* %l2, align 4
	%t39 = load float, float* %l3, align 4
	%t40 = call float @my_log(float %t38, float %t39)
	call void @putfloat(float %t40)
	br label %.L42
.L41:
	call void @putch(i32 45)
	br label %.L42
.L42:
	call void @putch(i32 32)
	%t43 = sitofp i32 0 to float
	%t44 = load float, float* %l2, align 4
	%t45 = fcmp ogt float %t44, %t43
	br i1 %t45, label %.L46, label %.L50
.L46:
	%t47 = load float, float* %l2, align 4
	%t48 = load float, float* %l3, align 4
	%t49 = call float @my_powf(float %t47, float %t48)
	call void @putfloat(float %t49)
	br label %.L51
.L50:
	call void @putch(i32 45)
	br label %.L51
.L51:
	call void @putch(i32 10)
	%t52 = load i32, i32* %l1, align 4
	%t53 = sub i32 %t52, 1
	store i32 %t53, i32* %l1, align 4
	br label %.L6
.L55:
	store i32 0, i32* %l0, align 4
	br label %.L57
.L57:
	%t58 = load i32, i32* %l0, align 4
	ret i32 %t58
}
