; low_level.ll

%struct.int8 = type { i8 }
%struct.int16 = type { i16 }
%struct.int32 = type { i32 }
%struct.int64 = type { i64 }
%struct.float = type { float }
%struct.double = type { double }
%struct.char = type { i8 }

define %struct.int8 @addInt8(%struct.int8 %a, %struct.int8 %b) {
entry:
    %a_val = extractvalue %struct.int8 %a, 0
    %b_val = extractvalue %struct.int8 %b, 0
    %result = add i8 %a_val, %b_val
    %ret = insertvalue %struct.int8 undef, i8 %result, 0
    ret %struct.int8 %ret
}

define %struct.int8 @initInt(i8 %value) {
entry:
    %ret = alloca %struct.int8
    %ret_val = getelementptr %struct.int8, %struct.int8* %ret, i8 0, i8 0
    store i8 %value, i8* %ret_val
    %ret_load = load %struct.int8, %struct.int8* %ret
    ret %struct.int8 %ret_load
}

; Define a function to get the value of an _Int
define i8 @getIntValue(%struct.int8* %a) {
entry:
    %a_val = getelementptr %struct.int8, %struct.int8* %a, i8 0, i8 0
    %a_load = load i8, i8* %a_val
    ret i8 %a_load
}

define void @setIntValue(%struct.int8* %a, i8 %value) {
entry:
    %a_val = getelementptr %struct.int8, %struct.int8* %a, i8 0, i8 0
    store i8 %value, i8* %a_val
    ret void
}

define %struct.int16 @addInt16(%struct.int16 %a, %struct.int16 %b) {
entry:
    %a_val = extractvalue %struct.int16 %a, 0
    %b_val = extractvalue %struct.int16 %b, 0
    %result = add i16 %a_val, %b_val
    %ret = insertvalue %struct.int16 undef, i16 %result, 0
    ret %struct.int16 %ret
}

%struct.int16 @initInt16(i16 %value) {
entry:
    %ret = alloca %struct.int16
    %ret_val = getelementptr %struct.int16, %struct.int16* %ret, i16 0, i16 0
    store i16 %value, i16* %ret_val
    %ret_load = load %struct.int16, %struct.int16* %ret
    ret %struct.int16 %ret_load
}

define i16 @getInt16Value(%struct.int16* %a) {
entry:
    %a_val = getelementptr %struct.int16, %struct.int16* %a, i16 0, i16 0
    %a_load = load i16, i16* %a_val
    ret i16 %a_load
}

define void @setInt16Value(%struct.int16* %a, i16 %value) {
entry:
    %a_val = getelementptr %struct.int16, %struct.int16* %a, i16 0, i16 0
    store i16 %value, i16* %a_val
    ret void
}

define %struct.int32 @addInt32(%struct.int32 %a, %struct.int32 %b) {
entry:
    %a_val = extractvalue %struct.int32 %a, 0
    %b_val = extractvalue %struct.int32 %b, 0
    %result = add i32 %a_val, %b_val
    %ret = insertvalue %struct.int32 undef, i32 %result, 0
    ret %struct.int32 %ret
}

define %struct.int32 @initInt32(i32 %value) {
entry:
    %ret = alloca %struct.int32
    %ret_val = getelementptr %struct.int32, %struct.int32* %ret, i32 0, i32 0
    store i32 %value, i32* %ret_val
    %ret_load = load %struct.int32, %struct.int32* %ret
    ret %struct.int32 %ret_load
}

define i32 @getInt32Value(%struct.int32* %a) {
entry:
    %a_val = getelementptr %struct.int32, %struct.int32* %a, i32 0, i32 0
    %a_load = load i32, i32* %a_val
    ret i32 %a_load
}

define void @setInt32Value(%struct.int32* %a, i32 %value) {
entry:
    %a_val = getelementptr %struct.int32, %struct.int32* %a, i32 0, i32 0
    store i32 %value, i32* %a_val
    ret void
}

define %struct.int64 @addInt64(%struct.int64 %a, %struct.int64 %b) {
entry:
    %a_val = extractvalue %struct.int64 %a, 0
    %b_val = extractvalue %struct.int64 %b, 0
    %result = add i64 %a_val, %b_val
    %ret = insertvalue %struct.int64 undef, i64 %result, 0
    ret %struct.int64 %ret
}

define %struct.int64 @initInt64(i64 %value) {
entry:
    %ret = alloca %struct.int64
    %ret_val = getelementptr %struct.int64, %struct.int64* %ret, i64 0, i64 0
    store i64 %value, i64* %ret_val
    %ret_load = load %struct.int64, %struct.int64* %ret
    ret %struct.int64 %ret_load
}

define i64 @getInt64Value(%struct.int64* %a) {
entry:
    %a_val = getelementptr %struct.int64, %struct.int64* %a, i64 0, i64 0
    %a_load = load i64, i64* %a_val
    ret i64 %a_load
}

define void @setInt64Value(%struct.int64* %a, i64 %value) {
entry:
    %a_val = getelementptr %struct.int64, %struct.int64* %a, i64 0, i64 0
    store i64 %value, i64* %a_val
    ret void
}

define %struct.float @addFloat(%struct.float %a, %struct.float %b) {
entry:
    %a_val = extractvalue %struct.float %a, 0
    %b_val = extractvalue %struct.float %b, 0
    %result = fadd float %a_val, %b_val
    %ret = insertvalue %struct.float undef, float %result, 0
    ret %struct.float %ret
}

define %struct.float @initFloat(float %value) {
entry:
    %ret = alloca %struct.float
    %ret_val = getelementptr %struct.float, %struct.float* %ret, float 0, float 0
    store float %value, float* %ret_val
    %ret_load = load %struct.float, %struct.float* %ret
    ret %struct.float %ret_load
}

define float @getFloatValue(%struct.float* %a) {
entry:
    %a_val = getelementptr %struct.float, %struct.float* %a, float 0, float 0
    %a_load = load float, float* %a_val
    ret float %a_load
}

define void @setFloatValue(%struct.float* %a, float %value) {
entry:
    %a_val = getelementptr %struct.float, %struct.float* %a, float 0, float 0
    store float %value, float* %a_val
    ret void
}

define %struct.double @addDouble(%struct.double %a, %struct.double %b) {
entry:
    %a_val = extractvalue %struct.double %a, 0
    %b_val = extractvalue %struct.double %b, 0
    %result = fadd double %a_val, %b_val
    %ret = insertvalue %struct.double undef, double %result, 0
    ret %struct.double %ret
}

define %struct.double @initDouble(double %value) {
entry:
    %ret = alloca %struct.double
    %ret_val = getelementptr %struct.double, %struct.double* %ret, double 0, double 0
    store double %value, double* %ret_val
    %ret_load = load %struct.double, %struct.double* %ret
    ret %struct.double %ret_load
}

define double @getDoubleValue(%struct.double* %a) {
entry:
    %a_val = getelementptr %struct.double, %struct.double* %a, double 0, double 0
    %a_load = load double, double* %a_val
    ret double %a_load
}

define void @setDoubleValue(%struct.double* %a, double %value) {
entry:
    %a_val = getelementptr %struct.double, %struct.double* %a, double 0, double 0
    store double %value, double* %a_val
    ret void
}
