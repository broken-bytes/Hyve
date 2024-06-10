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

define %struct.int16 @addInt16(%struct.int16 %a, %struct.int16 %b) {
entry:
    %a_val = extractvalue %struct.int16 %a, 0
    %b_val = extractvalue %struct.int16 %b, 0
    %result = add i16 %a_val, %b_val
    %ret = insertvalue %struct.int16 undef, i16 %result, 0
    ret %struct.int16 %ret
}

define %struct.int32 @addInt32(%struct.int32 %a, %struct.int32 %b) {
entry:
    %a_val = extractvalue %struct.int32 %a, 0
    %b_val = extractvalue %struct.int32 %b, 0
    %result = add i32 %a_val, %b_val
    %ret = insertvalue %struct.int32 undef, i32 %result, 0
    ret %struct.int32 %ret
}

define %struct.int64 @addInt64(%struct.int64 %a, %struct.int64 %b) {
entry:
    %a_val = extractvalue %struct.int64 %a, 0
    %b_val = extractvalue %struct.int64 %b, 0
    %result = add i64 %a_val, %b_val
    %ret = insertvalue %struct.int64 undef, i64 %result, 0
    ret %struct.int64 %ret
}

define %struct.float @addFloat(%struct.float %a, %struct.float %b) {
entry:
    %a_val = extractvalue %struct.float %a, 0
    %b_val = extractvalue %struct.float %b, 0
    %result = fadd float %a_val, %b_val
    %ret = insertvalue %struct.float undef, float %result, 0
    ret %struct.float %ret
}

define %struct.double @addDouble(%struct.double %a, %struct.double %b) {
entry:
    %a_val = extractvalue %struct.double %a, 0
    %b_val = extractvalue %struct.double %b, 0
    %result = fadd double %a_val, %b_val
    %ret = insertvalue %struct.double undef, double %result, 0
    ret %struct.double %ret
}