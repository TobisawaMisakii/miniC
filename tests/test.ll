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
define i32 @main()
{
	%l0 = alloca i32, align 4
	%l1 = alloca [3 x [3 x i32]], align 16 ;  1:x
	%t2 = getelementptr inbounds [3 x [3 x i32]], [3 x [3 x i32]]* %l1, i64 0, i32 2
	%t3 = getelementptr inbounds [3 x i32], [3 x i32]* %t2, i64 0, i64 0
	%t4 = call i32 (i32*, ...) bitcast (i32 (...)* @getarray to i32 (i32*, ...)*)(i32* %t3)
	%t5 = getelementptr inbounds [3 x [3 x i32]], [3 x [3 x i32]]* %l1, i64 0, i32 2
	%t6 = getelementptr inbounds [3 x i32], [3 x i32]* %t5, i64 0, i32 1
	%t7 = load i32, i32* %t6, align 4
	store i32 %t7, i32* %l0, align 4
	br label %.L9
.L9:
	%t10 = load i32, i32* %l0, align 4
	ret i32 %t10
}
