; low_level.ll

; Define addition for i8
define i8 @addInt8(i8 %a, i8 %b) {
entry:
    %result = add i8 %a, %b
    ret i8 %result
}

; Define initialization for i8
define i8 @initInt8(i8 %value) {
entry:
    ret i8 %value
}

; Define getting the value for i8
define i8 @getInt8Value(i8 %a) {
entry:
    ret i8 %a
}

; Define setting the value for i8
define void @setInt8Value(i8* %a, i8 %value) {
entry:
    store i8 %value, i8* %a
    ret void
}

; Define addition for i16
define i16 @addInt16(i16 %a, i16 %b) {
entry:
    %result = add i16 %a, %b
    ret i16 %result
}

; Define initialization for i16
define i16 @initInt16(i16 %value) {
entry:
    ret i16 %value
}

; Define getting the value for i16
define i16 @getInt16Value(i16 %a) {
entry:
    ret i16 %a
}

; Define setting the value for i16
define void @setInt16Value(i16* %a, i16 %value) {
entry:
    store i16 %value, i16* %a
    ret void
}

; Define addition for i32
define i32 @addInt32(i32 %a, i32 %b) {
entry:
    %result = add i32 %a, %b
    ret i32 %result
}

; Define initialization for i32
define i32 @initInt32(i32 %value) {
entry:
    ret i32 %value
}

; Define getting the value for i32
define i32 @getInt32Value(i32 %a) {
entry:
    ret i32 %a
}

; Define setting the value for i32
define void @setInt32Value(i32* %a, i32 %value) {
entry:
    store i32 %value, i32* %a
    ret void
}

; Define addition for i64
define i64 @addInt64(i64 %a, i64 %b) {
entry:
    %result = add i64 %a, %b
    ret i64 %result
}

; Define initialization for i64
define i64 @initInt64(i64 %value) {
entry:
    ret i64 %value
}

; Define getting the value for i64
define i64 @getInt64Value(i64 %a) {
entry:
    ret i64 %a
}

; Define setting the value for i64
define void @setInt64Value(i64* %a, i64 %value) {
entry:
    store i64 %value, i64* %a
    ret void
}

; Define addition for float
define float @addFloat(float %a, float %b) {
entry:
    %result = fadd float %a, %b
    ret float %result
}

; Define initialization for float
define float @initFloat(float %value) {
entry:
    ret float %value
}

; Define getting the value for float
define float @getFloatValue(float %a) {
entry:
    ret float %a
}

; Define setting the value for float
define void @setFloatValue(float* %a, float %value) {
entry:
    store float %value, float* %a
    ret void
}

; Define addition for double
define double @addDouble(double %a, double %b) {
entry:
    %result = fadd double %a, %b
    ret double %result
}

; Define initialization for double
define double @initDouble(double %value) {
entry:
    ret double %value
}

; Define getting the value for double
define double @getDoubleValue(double %a) {
entry:
    ret double %a
}

; Define setting the value for double
define void @setDoubleValue(double* %a, double %value) {
entry:
    store double %value, double* %a
    ret void
}