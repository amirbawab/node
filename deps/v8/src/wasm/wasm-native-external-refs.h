// Copyright 2016 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_WASM_WASM_NATIVE_EXTERNAL_REFS_H_
#define V8_WASM_WASM_NATIVE_EXTERNAL_REFS_H_

#include "src/wasm/value-type.h"
#include "src/v8memory.h"
#include "src/third_party/native/system.h"

namespace v8 {
namespace internal {

class ExternalReference;

namespace wasm {

typedef void (*native_t)(Address, Address);

// Find native function and set its index
bool find_native_function(const char* find_name, FunctionSig* sig, ExternalReference (**ref)());

// List of all the external references used 
// by the native call instruction
#define WASM_EXTERNAL_REFERENCE_LIST(F, V, P, R) \
  WASM_EXTERNAL_REFERENCE_SYSTEM(F, V, P, R)

#define WASM_EXTERNAL_REFERENCE_DECLARATION(F, func, name, params, rets) \
  void func(Address, Address);
WASM_EXTERNAL_REFERENCE_LIST(void, WASM_EXTERNAL_REFERENCE_DECLARATION, void, void)
#undef WASM_EXTERNAL_REFERENCE_DECLARATION

}  // namespace wasm
}  // namespace internal
}  // namespace v8

#endif
