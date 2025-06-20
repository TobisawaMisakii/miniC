@__HELLO = global [100 x i32] zeroinitializer, align 16
@N4__mE___ = global [6 x [50 x i32]] zeroinitializer, align 16
@saY_HeI10_To = global [40 x i32] zeroinitializer, align 16
@RET = global [5 x i32] zeroinitializer, align 16
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
define i32 @putstr(i32* %t0)
{
	%l1 = alloca i32*, align 8 ; 1:str
	%l2 = alloca i32, align 4
	%l3 = alloca i32, align 4 ; 1:iNd__1X
	store i32* %t0, i32** %l1, align 8
	store i32 0, i32* %l3, align 4
	br label %.L6
.L6:
	%t7 = load i32, i32* %l3, align 4
	%t8 = load i32*, i32** %l1, align 8
	%t9 = mul i32 %t7, 4
	%t10 = getelementptr inbounds i32, i32* %t8, i64 0
	%t11 = bitcast i32* %t10 to i8*
	%t12 = sext i32 %t9 to i64
	%t13 = getelementptr inbounds i8, i8* %t11, i64 %t12
	%t14 = bitcast i8* %t13 to i32*
	%t15 = load i32, i32* %t14, align 4
	%t16 = icmp ne i32 %t15, 0
	br i1 %t16, label %.L17, label %.L30
.L17:
	%t18 = load i32, i32* %l3, align 4
	%t19 = load i32*, i32** %l1, align 8
	%t20 = mul i32 %t18, 4
	%t21 = getelementptr inbounds i32, i32* %t19, i64 0
	%t22 = bitcast i32* %t21 to i8*
	%t23 = sext i32 %t20 to i64
	%t24 = getelementptr inbounds i8, i8* %t22, i64 %t23
	%t25 = bitcast i8* %t24 to i32*
	%t26 = load i32, i32* %t25, align 4
	call void @putch(i32 %t26)
	%t27 = load i32, i32* %l3, align 4
	%t28 = add i32 %t27, 1
	store i32 %t28, i32* %l3, align 4
	br label %.L6
.L30:
	%t31 = load i32, i32* %l3, align 4
	store i32 %t31, i32* %l2, align 4
	br label %.L33
.L33:
	%t34 = load i32, i32* %l2, align 4
	ret i32 %t34
}
define i32 @main()
{
	%l0 = alloca i32, align 4
	%l1 = alloca i32, align 4 ; 1:i
	%l2 = alloca i32, align 4 ; 2:_
	%l3 = alloca i32, align 4 ; 2:__
	%t4 = getelementptr inbounds [100 x i32], [100 x i32]* @__HELLO, i64 0, i64 0
	%t5 = call i32 @putstr()
	store i32 0, i32* %l1, align 4
	br label %.L7
.L7:
	%t8 = icmp ne i32 1, 0
	br i1 %t8, label %.L9, label %.L54
.L9:
	%t10 = load i32, i32* %l1, align 4
	%t11 = sdiv i32 %t10, 6
	store i32 %t11, i32* %l2, align 4
	%t13 = load i32, i32* %l1, align 4
	%t14 = srem i32 %t13, 6
	store i32 %t14, i32* %l3, align 4
	%t16 = load i32, i32* %l2, align 4
	%t17 = load i32, i32* %l3, align 4
	%t18 = icmp ne i32 %t16, %t17
	br i1 %t18, label %.L19, label %.L44
.L19:
	%t20 = load i32, i32* %l2, align 4
	%t21 = add i32 0, %t20
	%t22 = mul i32 %t21, 4
	%t23 = getelementptr inbounds [6 x [50 x i32]], [6 x [50 x i32]]* @N4__mE___, i64 0, i64 0, i64 0
	%t24 = bitcast i32* %t23 to i8*
	%t25 = sext i32 %t22 to i64
	%t26 = getelementptr inbounds i8, i8* %t24, i64 %t25
	%t27 = bitcast i8* %t26 to i32*
	%t28 = load i32, i32* %t27, align 4
	%t29 = call i32 @putstr()
	%t30 = getelementptr inbounds [40 x i32], [40 x i32]* @saY_HeI10_To, i64 0, i64 0
	%t31 = call i32 @putstr()
	%t32 = load i32, i32* %l3, align 4
	%t33 = add i32 0, %t32
	%t34 = mul i32 %t33, 4
	%t35 = getelementptr inbounds [6 x [50 x i32]], [6 x [50 x i32]]* @N4__mE___, i64 0, i64 0, i64 0
	%t36 = bitcast i32* %t35 to i8*
	%t37 = sext i32 %t34 to i64
	%t38 = getelementptr inbounds i8, i8* %t36, i64 %t37
	%t39 = bitcast i8* %t38 to i32*
	%t40 = load i32, i32* %t39, align 4
	%t41 = call i32 @putstr()
	%t42 = getelementptr inbounds [5 x i32], [5 x i32]* @RET, i64 0, i64 0
	%t43 = call i32 @putstr()
	br label %.L44
.L44:
	%t45 = load i32, i32* %l1, align 4
	%t46 = mul i32 %t45, 17
	%t47 = add i32 %t46, 23
	%t48 = srem i32 %t47, 32
	store i32 %t48, i32* %l1, align 4
	%t50 = load i32, i32* %l1, align 4
	%t51 = icmp eq i32 %t50, 0
	br i1 %t51, label %.L52, label %.L53
.L52:
	br label %.L54
.L53:
	br label %.L7
.L54:
	store i32 0, i32* %l0, align 4
	br label %.L56
.L56:
	%t57 = load i32, i32* %l0, align 4
	ret i32 %t57
}
