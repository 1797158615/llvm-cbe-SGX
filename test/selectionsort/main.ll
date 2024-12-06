; ModuleID = 'main.c'
source_filename = "main.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [26 x i8] c"Enter number of elements\0A\00", align 1, !dbg !0
@.str.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1, !dbg !7
@.str.2 = private unnamed_addr constant [19 x i8] c"Enter %d integers\0A\00", align 1, !dbg !12
@.str.3 = private unnamed_addr constant [33 x i8] c"Sorted list in ascending order:\0A\00", align 1, !dbg !17
@.str.4 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1, !dbg !22

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !37 {
  %1 = alloca i32, align 4
  %2 = alloca [100 x i32], align 16
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  call void @llvm.dbg.declare(metadata ptr %2, metadata !42, metadata !DIExpression()), !dbg !46
  call void @llvm.dbg.declare(metadata ptr %3, metadata !47, metadata !DIExpression()), !dbg !48
  call void @llvm.dbg.declare(metadata ptr %4, metadata !49, metadata !DIExpression()), !dbg !50
  call void @llvm.dbg.declare(metadata ptr %5, metadata !51, metadata !DIExpression()), !dbg !52
  call void @llvm.dbg.declare(metadata ptr %6, metadata !53, metadata !DIExpression()), !dbg !54
  call void @llvm.dbg.declare(metadata ptr %7, metadata !55, metadata !DIExpression()), !dbg !56
  %8 = call i32 (ptr, ...) @printf(ptr noundef @.str), !dbg !57
  %9 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str.1, ptr noundef %3), !dbg !58
  %10 = load i32, ptr %3, align 4, !dbg !59
  %11 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, i32 noundef %10), !dbg !60
  store i32 0, ptr %4, align 4, !dbg !61
  br label %12, !dbg !63

12:                                               ; preds = %21, %0
  %13 = load i32, ptr %4, align 4, !dbg !64
  %14 = load i32, ptr %3, align 4, !dbg !66
  %15 = icmp slt i32 %13, %14, !dbg !67
  br i1 %15, label %16, label %24, !dbg !68

16:                                               ; preds = %12
  %17 = load i32, ptr %4, align 4, !dbg !69
  %18 = sext i32 %17 to i64, !dbg !70
  %19 = getelementptr inbounds [100 x i32], ptr %2, i64 0, i64 %18, !dbg !70
  %20 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str.1, ptr noundef %19), !dbg !71
  br label %21, !dbg !71

21:                                               ; preds = %16
  %22 = load i32, ptr %4, align 4, !dbg !72
  %23 = add nsw i32 %22, 1, !dbg !72
  store i32 %23, ptr %4, align 4, !dbg !72
  br label %12, !dbg !73, !llvm.loop !74

24:                                               ; preds = %12
  store i32 0, ptr %4, align 4, !dbg !77
  br label %25, !dbg !79

25:                                               ; preds = %75, %24
  %26 = load i32, ptr %4, align 4, !dbg !80
  %27 = load i32, ptr %3, align 4, !dbg !82
  %28 = sub nsw i32 %27, 1, !dbg !83
  %29 = icmp slt i32 %26, %28, !dbg !84
  br i1 %29, label %30, label %78, !dbg !85

30:                                               ; preds = %25
  %31 = load i32, ptr %4, align 4, !dbg !86
  store i32 %31, ptr %6, align 4, !dbg !88
  %32 = load i32, ptr %4, align 4, !dbg !89
  %33 = add nsw i32 %32, 1, !dbg !91
  store i32 %33, ptr %5, align 4, !dbg !92
  br label %34, !dbg !93

34:                                               ; preds = %51, %30
  %35 = load i32, ptr %5, align 4, !dbg !94
  %36 = load i32, ptr %3, align 4, !dbg !96
  %37 = icmp slt i32 %35, %36, !dbg !97
  br i1 %37, label %38, label %54, !dbg !98

38:                                               ; preds = %34
  %39 = load i32, ptr %6, align 4, !dbg !99
  %40 = sext i32 %39 to i64, !dbg !102
  %41 = getelementptr inbounds [100 x i32], ptr %2, i64 0, i64 %40, !dbg !102
  %42 = load i32, ptr %41, align 4, !dbg !102
  %43 = load i32, ptr %5, align 4, !dbg !103
  %44 = sext i32 %43 to i64, !dbg !104
  %45 = getelementptr inbounds [100 x i32], ptr %2, i64 0, i64 %44, !dbg !104
  %46 = load i32, ptr %45, align 4, !dbg !104
  %47 = icmp sgt i32 %42, %46, !dbg !105
  br i1 %47, label %48, label %50, !dbg !106

48:                                               ; preds = %38
  %49 = load i32, ptr %5, align 4, !dbg !107
  store i32 %49, ptr %6, align 4, !dbg !108
  br label %50, !dbg !109

50:                                               ; preds = %48, %38
  br label %51, !dbg !110

51:                                               ; preds = %50
  %52 = load i32, ptr %5, align 4, !dbg !111
  %53 = add nsw i32 %52, 1, !dbg !111
  store i32 %53, ptr %5, align 4, !dbg !111
  br label %34, !dbg !112, !llvm.loop !113

54:                                               ; preds = %34
  %55 = load i32, ptr %6, align 4, !dbg !115
  %56 = load i32, ptr %4, align 4, !dbg !117
  %57 = icmp ne i32 %55, %56, !dbg !118
  br i1 %57, label %58, label %74, !dbg !119

58:                                               ; preds = %54
  %59 = load i32, ptr %4, align 4, !dbg !120
  %60 = sext i32 %59 to i64, !dbg !122
  %61 = getelementptr inbounds [100 x i32], ptr %2, i64 0, i64 %60, !dbg !122
  %62 = load i32, ptr %61, align 4, !dbg !122
  store i32 %62, ptr %7, align 4, !dbg !123
  %63 = load i32, ptr %6, align 4, !dbg !124
  %64 = sext i32 %63 to i64, !dbg !125
  %65 = getelementptr inbounds [100 x i32], ptr %2, i64 0, i64 %64, !dbg !125
  %66 = load i32, ptr %65, align 4, !dbg !125
  %67 = load i32, ptr %4, align 4, !dbg !126
  %68 = sext i32 %67 to i64, !dbg !127
  %69 = getelementptr inbounds [100 x i32], ptr %2, i64 0, i64 %68, !dbg !127
  store i32 %66, ptr %69, align 4, !dbg !128
  %70 = load i32, ptr %7, align 4, !dbg !129
  %71 = load i32, ptr %6, align 4, !dbg !130
  %72 = sext i32 %71 to i64, !dbg !131
  %73 = getelementptr inbounds [100 x i32], ptr %2, i64 0, i64 %72, !dbg !131
  store i32 %70, ptr %73, align 4, !dbg !132
  br label %74, !dbg !133

74:                                               ; preds = %58, %54
  br label %75, !dbg !134

75:                                               ; preds = %74
  %76 = load i32, ptr %4, align 4, !dbg !135
  %77 = add nsw i32 %76, 1, !dbg !135
  store i32 %77, ptr %4, align 4, !dbg !135
  br label %25, !dbg !136, !llvm.loop !137

78:                                               ; preds = %25
  %79 = call i32 (ptr, ...) @printf(ptr noundef @.str.3), !dbg !139
  store i32 0, ptr %4, align 4, !dbg !140
  br label %80, !dbg !142

80:                                               ; preds = %90, %78
  %81 = load i32, ptr %4, align 4, !dbg !143
  %82 = load i32, ptr %3, align 4, !dbg !145
  %83 = icmp slt i32 %81, %82, !dbg !146
  br i1 %83, label %84, label %93, !dbg !147

84:                                               ; preds = %80
  %85 = load i32, ptr %4, align 4, !dbg !148
  %86 = sext i32 %85 to i64, !dbg !149
  %87 = getelementptr inbounds [100 x i32], ptr %2, i64 0, i64 %86, !dbg !149
  %88 = load i32, ptr %87, align 4, !dbg !149
  %89 = call i32 (ptr, ...) @printf(ptr noundef @.str.4, i32 noundef %88), !dbg !150
  br label %90, !dbg !150

90:                                               ; preds = %84
  %91 = load i32, ptr %4, align 4, !dbg !151
  %92 = add nsw i32 %91, 1, !dbg !151
  store i32 %92, ptr %4, align 4, !dbg !151
  br label %80, !dbg !152, !llvm.loop !153

93:                                               ; preds = %80
  ret i32 0, !dbg !155
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @printf(ptr noundef, ...) #2

declare i32 @__isoc99_scanf(ptr noundef, ...) #2

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.dbg.cu = !{!27}
!llvm.module.flags = !{!29, !30, !31, !32, !33, !34, !35}
!llvm.ident = !{!36}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(scope: null, file: !2, line: 6, type: !3, isLocal: true, isDefinition: true)
!2 = !DIFile(filename: "main.c", directory: "/home/yxk/llvm-cbe/test/selectionsort", checksumkind: CSK_MD5, checksum: "34823317201206e270fd4d4060d32b7f")
!3 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 208, elements: !5)
!4 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!5 = !{!6}
!6 = !DISubrange(count: 26)
!7 = !DIGlobalVariableExpression(var: !8, expr: !DIExpression())
!8 = distinct !DIGlobalVariable(scope: null, file: !2, line: 7, type: !9, isLocal: true, isDefinition: true)
!9 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 24, elements: !10)
!10 = !{!11}
!11 = !DISubrange(count: 3)
!12 = !DIGlobalVariableExpression(var: !13, expr: !DIExpression())
!13 = distinct !DIGlobalVariable(scope: null, file: !2, line: 9, type: !14, isLocal: true, isDefinition: true)
!14 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 152, elements: !15)
!15 = !{!16}
!16 = !DISubrange(count: 19)
!17 = !DIGlobalVariableExpression(var: !18, expr: !DIExpression())
!18 = distinct !DIGlobalVariable(scope: null, file: !2, line: 28, type: !19, isLocal: true, isDefinition: true)
!19 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 264, elements: !20)
!20 = !{!21}
!21 = !DISubrange(count: 33)
!22 = !DIGlobalVariableExpression(var: !23, expr: !DIExpression())
!23 = distinct !DIGlobalVariable(scope: null, file: !2, line: 31, type: !24, isLocal: true, isDefinition: true)
!24 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 32, elements: !25)
!25 = !{!26}
!26 = !DISubrange(count: 4)
!27 = distinct !DICompileUnit(language: DW_LANG_C11, file: !2, producer: "Ubuntu clang version 17.0.6 (++20231209124227+6009708b4367-1~exp1~20231209124336.77)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, globals: !28, splitDebugInlining: false, nameTableKind: None)
!28 = !{!0, !7, !12, !17, !22}
!29 = !{i32 7, !"Dwarf Version", i32 5}
!30 = !{i32 2, !"Debug Info Version", i32 3}
!31 = !{i32 1, !"wchar_size", i32 4}
!32 = !{i32 8, !"PIC Level", i32 2}
!33 = !{i32 7, !"PIE Level", i32 2}
!34 = !{i32 7, !"uwtable", i32 2}
!35 = !{i32 7, !"frame-pointer", i32 2}
!36 = !{!"Ubuntu clang version 17.0.6 (++20231209124227+6009708b4367-1~exp1~20231209124336.77)"}
!37 = distinct !DISubprogram(name: "main", scope: !2, file: !2, line: 3, type: !38, scopeLine: 3, spFlags: DISPFlagDefinition, unit: !27, retainedNodes: !41)
!38 = !DISubroutineType(types: !39)
!39 = !{!40}
!40 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!41 = !{}
!42 = !DILocalVariable(name: "array", scope: !37, file: !2, line: 4, type: !43)
!43 = !DICompositeType(tag: DW_TAG_array_type, baseType: !40, size: 3200, elements: !44)
!44 = !{!45}
!45 = !DISubrange(count: 100)
!46 = !DILocation(line: 4, column: 7, scope: !37)
!47 = !DILocalVariable(name: "n", scope: !37, file: !2, line: 4, type: !40)
!48 = !DILocation(line: 4, column: 19, scope: !37)
!49 = !DILocalVariable(name: "c", scope: !37, file: !2, line: 4, type: !40)
!50 = !DILocation(line: 4, column: 22, scope: !37)
!51 = !DILocalVariable(name: "d", scope: !37, file: !2, line: 4, type: !40)
!52 = !DILocation(line: 4, column: 25, scope: !37)
!53 = !DILocalVariable(name: "position", scope: !37, file: !2, line: 4, type: !40)
!54 = !DILocation(line: 4, column: 28, scope: !37)
!55 = !DILocalVariable(name: "swap", scope: !37, file: !2, line: 4, type: !40)
!56 = !DILocation(line: 4, column: 38, scope: !37)
!57 = !DILocation(line: 6, column: 3, scope: !37)
!58 = !DILocation(line: 7, column: 3, scope: !37)
!59 = !DILocation(line: 9, column: 33, scope: !37)
!60 = !DILocation(line: 9, column: 3, scope: !37)
!61 = !DILocation(line: 11, column: 10, scope: !62)
!62 = distinct !DILexicalBlock(scope: !37, file: !2, line: 11, column: 3)
!63 = !DILocation(line: 11, column: 8, scope: !62)
!64 = !DILocation(line: 11, column: 15, scope: !65)
!65 = distinct !DILexicalBlock(scope: !62, file: !2, line: 11, column: 3)
!66 = !DILocation(line: 11, column: 19, scope: !65)
!67 = !DILocation(line: 11, column: 17, scope: !65)
!68 = !DILocation(line: 11, column: 3, scope: !62)
!69 = !DILocation(line: 12, column: 24, scope: !65)
!70 = !DILocation(line: 12, column: 18, scope: !65)
!71 = !DILocation(line: 12, column: 5, scope: !65)
!72 = !DILocation(line: 11, column: 23, scope: !65)
!73 = !DILocation(line: 11, column: 3, scope: !65)
!74 = distinct !{!74, !68, !75, !76}
!75 = !DILocation(line: 12, column: 26, scope: !62)
!76 = !{!"llvm.loop.mustprogress"}
!77 = !DILocation(line: 14, column: 10, scope: !78)
!78 = distinct !DILexicalBlock(scope: !37, file: !2, line: 14, column: 3)
!79 = !DILocation(line: 14, column: 8, scope: !78)
!80 = !DILocation(line: 14, column: 15, scope: !81)
!81 = distinct !DILexicalBlock(scope: !78, file: !2, line: 14, column: 3)
!82 = !DILocation(line: 14, column: 20, scope: !81)
!83 = !DILocation(line: 14, column: 22, scope: !81)
!84 = !DILocation(line: 14, column: 17, scope: !81)
!85 = !DILocation(line: 14, column: 3, scope: !78)
!86 = !DILocation(line: 15, column: 16, scope: !87)
!87 = distinct !DILexicalBlock(scope: !81, file: !2, line: 14, column: 33)
!88 = !DILocation(line: 15, column: 14, scope: !87)
!89 = !DILocation(line: 17, column: 14, scope: !90)
!90 = distinct !DILexicalBlock(scope: !87, file: !2, line: 17, column: 5)
!91 = !DILocation(line: 17, column: 16, scope: !90)
!92 = !DILocation(line: 17, column: 12, scope: !90)
!93 = !DILocation(line: 17, column: 10, scope: !90)
!94 = !DILocation(line: 17, column: 21, scope: !95)
!95 = distinct !DILexicalBlock(scope: !90, file: !2, line: 17, column: 5)
!96 = !DILocation(line: 17, column: 25, scope: !95)
!97 = !DILocation(line: 17, column: 23, scope: !95)
!98 = !DILocation(line: 17, column: 5, scope: !90)
!99 = !DILocation(line: 18, column: 17, scope: !100)
!100 = distinct !DILexicalBlock(scope: !101, file: !2, line: 18, column: 11)
!101 = distinct !DILexicalBlock(scope: !95, file: !2, line: 17, column: 33)
!102 = !DILocation(line: 18, column: 11, scope: !100)
!103 = !DILocation(line: 18, column: 35, scope: !100)
!104 = !DILocation(line: 18, column: 29, scope: !100)
!105 = !DILocation(line: 18, column: 27, scope: !100)
!106 = !DILocation(line: 18, column: 11, scope: !101)
!107 = !DILocation(line: 19, column: 20, scope: !100)
!108 = !DILocation(line: 19, column: 18, scope: !100)
!109 = !DILocation(line: 19, column: 9, scope: !100)
!110 = !DILocation(line: 20, column: 5, scope: !101)
!111 = !DILocation(line: 17, column: 29, scope: !95)
!112 = !DILocation(line: 17, column: 5, scope: !95)
!113 = distinct !{!113, !98, !114, !76}
!114 = !DILocation(line: 20, column: 5, scope: !90)
!115 = !DILocation(line: 21, column: 9, scope: !116)
!116 = distinct !DILexicalBlock(scope: !87, file: !2, line: 21, column: 9)
!117 = !DILocation(line: 21, column: 21, scope: !116)
!118 = !DILocation(line: 21, column: 18, scope: !116)
!119 = !DILocation(line: 21, column: 9, scope: !87)
!120 = !DILocation(line: 22, column: 20, scope: !121)
!121 = distinct !DILexicalBlock(scope: !116, file: !2, line: 21, column: 24)
!122 = !DILocation(line: 22, column: 14, scope: !121)
!123 = !DILocation(line: 22, column: 12, scope: !121)
!124 = !DILocation(line: 23, column: 24, scope: !121)
!125 = !DILocation(line: 23, column: 18, scope: !121)
!126 = !DILocation(line: 23, column: 13, scope: !121)
!127 = !DILocation(line: 23, column: 7, scope: !121)
!128 = !DILocation(line: 23, column: 16, scope: !121)
!129 = !DILocation(line: 24, column: 25, scope: !121)
!130 = !DILocation(line: 24, column: 13, scope: !121)
!131 = !DILocation(line: 24, column: 7, scope: !121)
!132 = !DILocation(line: 24, column: 23, scope: !121)
!133 = !DILocation(line: 25, column: 5, scope: !121)
!134 = !DILocation(line: 26, column: 3, scope: !87)
!135 = !DILocation(line: 14, column: 29, scope: !81)
!136 = !DILocation(line: 14, column: 3, scope: !81)
!137 = distinct !{!137, !85, !138, !76}
!138 = !DILocation(line: 26, column: 3, scope: !78)
!139 = !DILocation(line: 28, column: 3, scope: !37)
!140 = !DILocation(line: 30, column: 10, scope: !141)
!141 = distinct !DILexicalBlock(scope: !37, file: !2, line: 30, column: 3)
!142 = !DILocation(line: 30, column: 8, scope: !141)
!143 = !DILocation(line: 30, column: 15, scope: !144)
!144 = distinct !DILexicalBlock(scope: !141, file: !2, line: 30, column: 3)
!145 = !DILocation(line: 30, column: 19, scope: !144)
!146 = !DILocation(line: 30, column: 17, scope: !144)
!147 = !DILocation(line: 30, column: 3, scope: !141)
!148 = !DILocation(line: 31, column: 26, scope: !144)
!149 = !DILocation(line: 31, column: 20, scope: !144)
!150 = !DILocation(line: 31, column: 5, scope: !144)
!151 = !DILocation(line: 30, column: 23, scope: !144)
!152 = !DILocation(line: 30, column: 3, scope: !144)
!153 = distinct !{!153, !147, !154, !76}
!154 = !DILocation(line: 31, column: 28, scope: !141)
!155 = !DILocation(line: 33, column: 3, scope: !37)
