#ifndef V8_WASM_WASM_NATIVE_EXTERNAL_REFS_SYSTEM_H_
#define V8_WASM_WASM_NATIVE_EXTERNAL_REFS_SYSTEM_H_

#define WASM_EXTERNAL_REFERENCE_SYSTEM(F, V, P, R) \
  V(F, prints_i32, "prints_i32", P(kWasmI32), R()) \
  V(F, prints_i64, "prints_i64", P(kWasmI64), R()) \
  V(F, prints_f32, "prints_f32", P(kWasmF32), R()) \
  V(F, prints_f64, "prints_f64", P(kWasmF64), R()) \
  V(F, time_ms, "time_ms", P(), R(kWasmI64))

#endif // V8_WASM_WASM_NATIVE_EXTERNAL_REFS_SYSTEM_H_
