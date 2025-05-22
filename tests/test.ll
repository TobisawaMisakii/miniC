define i32 @main()
{
	declare i32 %l0
	declare i32 %l1[3][5] ;  1:a
	declare i32 %l2[3] ;  1:b
	declare i32 %l3
	declare i32 %t4
	declare i32 %t5
	declare i32 %t6
	declare i32* %t7
	declare i32 %t8
	declare i32* %t9
	declare i32 %t10
	declare i32* %t11
	entry
	%t4 = mul 0, 5
	%t5 = add %t4, 0
	%t6 = mul %t5, 4
	%t7 = add %l1, %t6
	*%t7 = 2
	%t8 = mul 0, 4
	%t9 = add %l2, %t8
	*%t9 = 1
	%t10 = mul 0, 4
	%t11 = add %l2, %t10
	%l3 = *%t11
	%l0 = %l3
	br label .L12
.L12:
	exit %l0
}
