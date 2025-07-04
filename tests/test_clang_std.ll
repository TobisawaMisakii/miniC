; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@e = dso_local constant float 0x4005BF0A80000000, align 4

; Function Attrs: noinline nounwind optnone uwtable
define dso_local float @my_fabs(float %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  store float %0, float* %3, align 4
  %4 = load float, float* %3, align 4
  %5 = fcmp ogt float %4, 0.000000e+00
  br i1 %5, label %6, label %8

6:                                                ; preds = %1
  %7 = load float, float* %3, align 4
  store float %7, float* %2, align 4
  br label %11

8:                                                ; preds = %1
  %9 = load float, float* %3, align 4
  %10 = fneg float %9
  store float %10, float* %2, align 4
  br label %11

11:                                               ; preds = %8, %6
  %12 = load float, float* %2, align 4
  ret float %12
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local float @my_pow(float %0, i32 %1) #0 {
  %3 = alloca float, align 4
  %4 = alloca float, align 4
  %5 = alloca i32, align 4
  %6 = alloca float, align 4
  store float %0, float* %4, align 4
  store i32 %1, i32* %5, align 4
  %7 = load i32, i32* %5, align 4
  %8 = icmp slt i32 %7, 0
  br i1 %8, label %9, label %15

9:                                                ; preds = %2
  %10 = load float, float* %4, align 4
  %11 = load i32, i32* %5, align 4
  %12 = sub nsw i32 0, %11
  %13 = call float @my_pow(float %10, i32 %12)
  %14 = fdiv float 1.000000e+00, %13
  store float %14, float* %3, align 4
  br label %35

15:                                               ; preds = %2
  store float 1.000000e+00, float* %6, align 4
  br label %16

16:                                               ; preds = %27, %15
  %17 = load i32, i32* %5, align 4
  %18 = icmp ne i32 %17, 0
  br i1 %18, label %19, label %33

19:                                               ; preds = %16
  %20 = load i32, i32* %5, align 4
  %21 = srem i32 %20, 2
  %22 = icmp ne i32 %21, 0
  br i1 %22, label %23, label %27

23:                                               ; preds = %19
  %24 = load float, float* %6, align 4
  %25 = load float, float* %4, align 4
  %26 = fmul float %24, %25
  store float %26, float* %6, align 4
  br label %27

27:                                               ; preds = %23, %19
  %28 = load float, float* %4, align 4
  %29 = load float, float* %4, align 4
  %30 = fmul float %28, %29
  store float %30, float* %4, align 4
  %31 = load i32, i32* %5, align 4
  %32 = sdiv i32 %31, 2
  store i32 %32, i32* %5, align 4
  br label %16

33:                                               ; preds = %16
  %34 = load float, float* %6, align 4
  store float %34, float* %3, align 4
  br label %35

35:                                               ; preds = %33, %9
  %36 = load float, float* %3, align 4
  ret float %36
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local float @my_sqrt(float %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  %4 = alloca float, align 4
  %5 = alloca i32, align 4
  store float %0, float* %3, align 4
  %6 = load float, float* %3, align 4
  %7 = fcmp ogt float %6, 1.000000e+02
  br i1 %7, label %8, label %15

8:                                                ; preds = %1
  %9 = load float, float* %3, align 4
  %10 = fdiv float %9, 1.000000e+02
  %11 = call float @my_sqrt(float %10)
  %12 = fpext float %11 to double
  %13 = fmul double 1.000000e+01, %12
  %14 = fptrunc double %13 to float
  store float %14, float* %2, align 4
  br label %42

15:                                               ; preds = %1
  %16 = load float, float* %3, align 4
  %17 = fdiv float %16, 8.000000e+00
  %18 = fpext float %17 to double
  %19 = fadd double %18, 5.000000e-01
  %20 = load float, float* %3, align 4
  %21 = fmul float 2.000000e+00, %20
  %22 = load float, float* %3, align 4
  %23 = fadd float 4.000000e+00, %22
  %24 = fdiv float %21, %23
  %25 = fpext float %24 to double
  %26 = fadd double %19, %25
  %27 = fptrunc double %26 to float
  store float %27, float* %4, align 4
  store i32 10, i32* %5, align 4
  br label %28

28:                                               ; preds = %31, %15
  %29 = load i32, i32* %5, align 4
  %30 = icmp ne i32 %29, 0
  br i1 %30, label %31, label %40

31:                                               ; preds = %28
  %32 = load float, float* %4, align 4
  %33 = load float, float* %3, align 4
  %34 = load float, float* %4, align 4
  %35 = fdiv float %33, %34
  %36 = fadd float %32, %35
  %37 = fdiv float %36, 2.000000e+00
  store float %37, float* %4, align 4
  %38 = load i32, i32* %5, align 4
  %39 = sub nsw i32 %38, 1
  store i32 %39, i32* %5, align 4
  br label %28

40:                                               ; preds = %28
  %41 = load float, float* %4, align 4
  store float %41, float* %2, align 4
  br label %42

42:                                               ; preds = %40, %8
  %43 = load float, float* %2, align 4
  ret float %43
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local float @F1(float %0) #0 {
  %2 = alloca float, align 4
  store float %0, float* %2, align 4
  %3 = load float, float* %2, align 4
  %4 = fdiv float 1.000000e+00, %3
  ret float %4
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local float @F2(float %0) #0 {
  %2 = alloca float, align 4
  store float %0, float* %2, align 4
  %3 = load float, float* %2, align 4
  %4 = load float, float* %2, align 4
  %5 = fmul float %3, %4
  %6 = fsub float 1.000000e+00, %5
  %7 = call float @my_sqrt(float %6)
  %8 = fdiv float 1.000000e+00, %7
  ret float %8
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local float @simpson(float %0, float %1, i32 %2) #0 {
  %4 = alloca float, align 4
  %5 = alloca float, align 4
  %6 = alloca float, align 4
  %7 = alloca i32, align 4
  %8 = alloca float, align 4
  store float %0, float* %5, align 4
  store float %1, float* %6, align 4
  store i32 %2, i32* %7, align 4
  %9 = load float, float* %5, align 4
  %10 = load float, float* %6, align 4
  %11 = load float, float* %5, align 4
  %12 = fsub float %10, %11
  %13 = fdiv float %12, 2.000000e+00
  %14 = fadd float %9, %13
  store float %14, float* %8, align 4
  %15 = load i32, i32* %7, align 4
  %16 = icmp eq i32 %15, 1
  br i1 %16, label %17, label %32

17:                                               ; preds = %3
  %18 = load float, float* %5, align 4
  %19 = call float @F1(float %18)
  %20 = load float, float* %8, align 4
  %21 = call float @F1(float %20)
  %22 = fmul float 4.000000e+00, %21
  %23 = fadd float %19, %22
  %24 = load float, float* %6, align 4
  %25 = call float @F1(float %24)
  %26 = fadd float %23, %25
  %27 = load float, float* %6, align 4
  %28 = load float, float* %5, align 4
  %29 = fsub float %27, %28
  %30 = fmul float %26, %29
  %31 = fdiv float %30, 6.000000e+00
  store float %31, float* %4, align 4
  br label %51

32:                                               ; preds = %3
  %33 = load i32, i32* %7, align 4
  %34 = icmp eq i32 %33, 2
  br i1 %34, label %35, label %50

35:                                               ; preds = %32
  %36 = load float, float* %5, align 4
  %37 = call float @F2(float %36)
  %38 = load float, float* %8, align 4
  %39 = call float @F2(float %38)
  %40 = fmul float 4.000000e+00, %39
  %41 = fadd float %37, %40
  %42 = load float, float* %6, align 4
  %43 = call float @F2(float %42)
  %44 = fadd float %41, %43
  %45 = load float, float* %6, align 4
  %46 = load float, float* %5, align 4
  %47 = fsub float %45, %46
  %48 = fmul float %44, %47
  %49 = fdiv float %48, 6.000000e+00
  store float %49, float* %4, align 4
  br label %51

50:                                               ; preds = %32
  store float 0.000000e+00, float* %4, align 4
  br label %51

51:                                               ; preds = %50, %35, %17
  %52 = load float, float* %4, align 4
  ret float %52
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local float @asr5(float %0, float %1, float %2, float %3, i32 %4) #0 {
  %6 = alloca float, align 4
  %7 = alloca float, align 4
  %8 = alloca float, align 4
  %9 = alloca float, align 4
  %10 = alloca float, align 4
  %11 = alloca i32, align 4
  %12 = alloca float, align 4
  %13 = alloca float, align 4
  %14 = alloca float, align 4
  store float %0, float* %7, align 4
  store float %1, float* %8, align 4
  store float %2, float* %9, align 4
  store float %3, float* %10, align 4
  store i32 %4, i32* %11, align 4
  %15 = load float, float* %7, align 4
  %16 = load float, float* %8, align 4
  %17 = load float, float* %7, align 4
  %18 = fsub float %16, %17
  %19 = fdiv float %18, 2.000000e+00
  %20 = fadd float %15, %19
  store float %20, float* %12, align 4
  %21 = load float, float* %7, align 4
  %22 = load float, float* %12, align 4
  %23 = load i32, i32* %11, align 4
  %24 = call float @simpson(float %21, float %22, i32 %23)
  store float %24, float* %13, align 4
  %25 = load float, float* %12, align 4
  %26 = load float, float* %8, align 4
  %27 = load i32, i32* %11, align 4
  %28 = call float @simpson(float %25, float %26, i32 %27)
  store float %28, float* %14, align 4
  %29 = load float, float* %13, align 4
  %30 = load float, float* %14, align 4
  %31 = fadd float %29, %30
  %32 = load float, float* %10, align 4
  %33 = fsub float %31, %32
  %34 = call float @my_fabs(float %33)
  %35 = load float, float* %9, align 4
  %36 = fmul float 1.500000e+01, %35
  %37 = fcmp ole float %34, %36
  br i1 %37, label %38, label %52

38:                                               ; preds = %5
  %39 = load float, float* %13, align 4
  %40 = load float, float* %14, align 4
  %41 = fadd float %39, %40
  %42 = fpext float %41 to double
  %43 = load float, float* %13, align 4
  %44 = load float, float* %14, align 4
  %45 = fadd float %43, %44
  %46 = load float, float* %10, align 4
  %47 = fsub float %45, %46
  %48 = fpext float %47 to double
  %49 = fdiv double %48, 1.500000e+01
  %50 = fadd double %42, %49
  %51 = fptrunc double %50 to float
  store float %51, float* %6, align 4
  br label %68

52:                                               ; preds = %5
  %53 = load float, float* %7, align 4
  %54 = load float, float* %12, align 4
  %55 = load float, float* %9, align 4
  %56 = fdiv float %55, 2.000000e+00
  %57 = load float, float* %13, align 4
  %58 = load i32, i32* %11, align 4
  %59 = call float @asr5(float %53, float %54, float %56, float %57, i32 %58)
  %60 = load float, float* %12, align 4
  %61 = load float, float* %8, align 4
  %62 = load float, float* %9, align 4
  %63 = fdiv float %62, 2.000000e+00
  %64 = load float, float* %14, align 4
  %65 = load i32, i32* %11, align 4
  %66 = call float @asr5(float %60, float %61, float %63, float %64, i32 %65)
  %67 = fadd float %59, %66
  store float %67, float* %6, align 4
  br label %68

68:                                               ; preds = %52, %38
  %69 = load float, float* %6, align 4
  ret float %69
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local float @asr4(float %0, float %1, float %2, i32 %3) #0 {
  %5 = alloca float, align 4
  %6 = alloca float, align 4
  %7 = alloca float, align 4
  %8 = alloca i32, align 4
  store float %0, float* %5, align 4
  store float %1, float* %6, align 4
  store float %2, float* %7, align 4
  store i32 %3, i32* %8, align 4
  %9 = load float, float* %5, align 4
  %10 = load float, float* %6, align 4
  %11 = load float, float* %7, align 4
  %12 = load float, float* %5, align 4
  %13 = load float, float* %6, align 4
  %14 = load i32, i32* %8, align 4
  %15 = call float @simpson(float %12, float %13, i32 %14)
  %16 = load i32, i32* %8, align 4
  %17 = call float @asr5(float %9, float %10, float %11, float %15, i32 %16)
  ret float %17
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local float @eee(float %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  %4 = alloca float, align 4
  store float %0, float* %3, align 4
  %5 = load float, float* %3, align 4
  %6 = fpext float %5 to double
  %7 = fcmp ogt double %6, 1.000000e-03
  br i1 %7, label %8, label %15

8:                                                ; preds = %1
  %9 = load float, float* %3, align 4
  %10 = fdiv float %9, 2.000000e+00
  %11 = call float @eee(float %10)
  store float %11, float* %4, align 4
  %12 = load float, float* %4, align 4
  %13 = load float, float* %4, align 4
  %14 = fmul float %12, %13
  store float %14, float* %2, align 4
  br label %35

15:                                               ; preds = %1
  %16 = load float, float* %3, align 4
  %17 = fadd float 1.000000e+00, %16
  %18 = load float, float* %3, align 4
  %19 = load float, float* %3, align 4
  %20 = fmul float %18, %19
  %21 = fdiv float %20, 2.000000e+00
  %22 = fadd float %17, %21
  %23 = load float, float* %3, align 4
  %24 = call float @my_pow(float %23, i32 3)
  %25 = fdiv float %24, 6.000000e+00
  %26 = fadd float %22, %25
  %27 = load float, float* %3, align 4
  %28 = call float @my_pow(float %27, i32 4)
  %29 = fdiv float %28, 2.400000e+01
  %30 = fadd float %26, %29
  %31 = load float, float* %3, align 4
  %32 = call float @my_pow(float %31, i32 5)
  %33 = fdiv float %32, 1.200000e+02
  %34 = fadd float %30, %33
  store float %34, float* %2, align 4
  br label %35

35:                                               ; preds = %15, %8
  %36 = load float, float* %2, align 4
  ret float %36
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local float @my_exp(float %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  %4 = alloca i32, align 4
  %5 = alloca float, align 4
  %6 = alloca float, align 4
  store float %0, float* %3, align 4
  %7 = load float, float* %3, align 4
  %8 = fcmp olt float %7, 0.000000e+00
  br i1 %8, label %9, label %14

9:                                                ; preds = %1
  %10 = load float, float* %3, align 4
  %11 = fneg float %10
  %12 = call float @my_exp(float %11)
  %13 = fdiv float 1.000000e+00, %12
  store float %13, float* %2, align 4
  br label %28

14:                                               ; preds = %1
  %15 = load float, float* %3, align 4
  %16 = fptosi float %15 to i32
  store i32 %16, i32* %4, align 4
  %17 = load float, float* %3, align 4
  %18 = load i32, i32* %4, align 4
  %19 = sitofp i32 %18 to float
  %20 = fsub float %17, %19
  store float %20, float* %3, align 4
  %21 = load i32, i32* %4, align 4
  %22 = call float @my_pow(float 0x4005BF0A80000000, i32 %21)
  store float %22, float* %5, align 4
  %23 = load float, float* %3, align 4
  %24 = call float @eee(float %23)
  store float %24, float* %6, align 4
  %25 = load float, float* %5, align 4
  %26 = load float, float* %6, align 4
  %27 = fmul float %25, %26
  store float %27, float* %2, align 4
  br label %28

28:                                               ; preds = %14, %9
  %29 = load float, float* %2, align 4
  ret float %29
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local float @my_ln(float %0) #0 {
  %2 = alloca float, align 4
  store float %0, float* %2, align 4
  %3 = load float, float* %2, align 4
  %4 = call float @asr4(float 1.000000e+00, float %3, float 0x3E45798EE0000000, i32 1)
  ret float %4
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local float @my_log(float %0, float %1) #0 {
  %3 = alloca float, align 4
  %4 = alloca float, align 4
  store float %0, float* %3, align 4
  store float %1, float* %4, align 4
  %5 = load float, float* %4, align 4
  %6 = call float @my_ln(float %5)
  %7 = load float, float* %3, align 4
  %8 = call float @my_ln(float %7)
  %9 = fdiv float %6, %8
  ret float %9
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local float @my_powf(float %0, float %1) #0 {
  %3 = alloca float, align 4
  %4 = alloca float, align 4
  store float %0, float* %3, align 4
  store float %1, float* %4, align 4
  %5 = load float, float* %4, align 4
  %6 = load float, float* %3, align 4
  %7 = call float @my_ln(float %6)
  %8 = fmul float %5, %7
  %9 = call float @my_exp(float %8)
  ret float %9
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca float, align 4
  %4 = alloca float, align 4
  store i32 0, i32* %1, align 4
  %5 = call i32 (...) @getint()
  store i32 %5, i32* %2, align 4
  br label %6

6:                                                ; preds = %70, %0
  %7 = load i32, i32* %2, align 4
  %8 = icmp ne i32 %7, 0
  br i1 %8, label %9, label %74

9:                                                ; preds = %6
  %10 = call i32 (...) @getfloat()
  %11 = sitofp i32 %10 to float
  store float %11, float* %3, align 4
  %12 = call i32 (...) @getfloat()
  %13 = sitofp i32 %12 to float
  store float %13, float* %4, align 4
  %14 = load float, float* %3, align 4
  %15 = call float @my_fabs(float %14)
  %16 = fpext float %15 to double
  %17 = call i32 (double, ...) bitcast (i32 (...)* @putfloat to i32 (double, ...)*)(double %16)
  %18 = call i32 (i32, ...) bitcast (i32 (...)* @putch to i32 (i32, ...)*)(i32 32)
  %19 = load float, float* %3, align 4
  %20 = call float @my_pow(float %19, i32 2)
  %21 = fpext float %20 to double
  %22 = call i32 (double, ...) bitcast (i32 (...)* @putfloat to i32 (double, ...)*)(double %21)
  %23 = call i32 (i32, ...) bitcast (i32 (...)* @putch to i32 (i32, ...)*)(i32 32)
  %24 = load float, float* %3, align 4
  %25 = call float @my_sqrt(float %24)
  %26 = fpext float %25 to double
  %27 = call i32 (double, ...) bitcast (i32 (...)* @putfloat to i32 (double, ...)*)(double %26)
  %28 = call i32 (i32, ...) bitcast (i32 (...)* @putch to i32 (i32, ...)*)(i32 32)
  %29 = load float, float* %3, align 4
  %30 = call float @my_exp(float %29)
  %31 = fpext float %30 to double
  %32 = call i32 (double, ...) bitcast (i32 (...)* @putfloat to i32 (double, ...)*)(double %31)
  %33 = call i32 (i32, ...) bitcast (i32 (...)* @putch to i32 (i32, ...)*)(i32 32)
  %34 = load float, float* %3, align 4
  %35 = fcmp ogt float %34, 0.000000e+00
  br i1 %35, label %36, label %41

36:                                               ; preds = %9
  %37 = load float, float* %3, align 4
  %38 = call float @my_ln(float %37)
  %39 = fpext float %38 to double
  %40 = call i32 (double, ...) bitcast (i32 (...)* @putfloat to i32 (double, ...)*)(double %39)
  br label %43

41:                                               ; preds = %9
  %42 = call i32 (i32, ...) bitcast (i32 (...)* @putch to i32 (i32, ...)*)(i32 45)
  br label %43

43:                                               ; preds = %41, %36
  %44 = call i32 (i32, ...) bitcast (i32 (...)* @putch to i32 (i32, ...)*)(i32 32)
  %45 = load float, float* %3, align 4
  %46 = fcmp ogt float %45, 0.000000e+00
  br i1 %46, label %47, label %56

47:                                               ; preds = %43
  %48 = load float, float* %4, align 4
  %49 = fcmp ogt float %48, 0.000000e+00
  br i1 %49, label %50, label %56

50:                                               ; preds = %47
  %51 = load float, float* %3, align 4
  %52 = load float, float* %4, align 4
  %53 = call float @my_log(float %51, float %52)
  %54 = fpext float %53 to double
  %55 = call i32 (double, ...) bitcast (i32 (...)* @putfloat to i32 (double, ...)*)(double %54)
  br label %58

56:                                               ; preds = %47, %43
  %57 = call i32 (i32, ...) bitcast (i32 (...)* @putch to i32 (i32, ...)*)(i32 45)
  br label %58

58:                                               ; preds = %56, %50
  %59 = call i32 (i32, ...) bitcast (i32 (...)* @putch to i32 (i32, ...)*)(i32 32)
  %60 = load float, float* %3, align 4
  %61 = fcmp ogt float %60, 0.000000e+00
  br i1 %61, label %62, label %68

62:                                               ; preds = %58
  %63 = load float, float* %3, align 4
  %64 = load float, float* %4, align 4
  %65 = call float @my_powf(float %63, float %64)
  %66 = fpext float %65 to double
  %67 = call i32 (double, ...) bitcast (i32 (...)* @putfloat to i32 (double, ...)*)(double %66)
  br label %70

68:                                               ; preds = %58
  %69 = call i32 (i32, ...) bitcast (i32 (...)* @putch to i32 (i32, ...)*)(i32 45)
  br label %70

70:                                               ; preds = %68, %62
  %71 = call i32 (i32, ...) bitcast (i32 (...)* @putch to i32 (i32, ...)*)(i32 10)
  %72 = load i32, i32* %2, align 4
  %73 = sub nsw i32 %72, 1
  store i32 %73, i32* %2, align 4
  br label %6

74:                                               ; preds = %6
  ret i32 0
}

declare dso_local i32 @getint(...) #1

declare dso_local i32 @getfloat(...) #1

declare dso_local i32 @putfloat(...) #1

declare dso_local i32 @putch(...) #1

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.0-4ubuntu1 "}
