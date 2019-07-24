#ifndef V8_WASM_WASM_NATIVE_EXTERNAL_REFS_MATH_H_
#define V8_WASM_WASM_NATIVE_EXTERNAL_REFS_MATH_H_

#define WASM_EXTERNAL_REFERENCE_MATH(F, V, P, R)               \
  V(F, add_i32, "add_i32", P(kWasmI32, kWasmI32), R(kWasmI32)) \
  V(F, sigmoid, "sigmoid_f64", P(kWasmF64), R(kWasmF64)) \
  V(F, dot_product_f32, "dot_product_f32", P(kWasmI32, kWasmI32, kWasmI32,kWasmI32, kWasmI32, kWasmI32), R()) \
  V(F, dot_product_rt_f32, "dot_product_rt_f32", P(kWasmI32, kWasmI32, kWasmI32,kWasmI32, kWasmI32, kWasmI32), R()) \
  V(F, dot_product_lt_f32, "dot_product_lt_f32", P(kWasmI32, kWasmI32, kWasmI32,kWasmI32, kWasmI32, kWasmI32), R())

#endif
