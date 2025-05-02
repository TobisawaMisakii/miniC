define i32 @main()
{
	declare i32 %l0
	declare float %l1 ; 1:a
	declare float %l2 ; 1:b
	declare float %t3
	entry
	%l1 = 3.100000
	%t3 = fadd 1.100000,%l1
	%l2 = %t3
	%l0 = 0
	br label .L4
.L4:
	exit %l0
}
