#include "src/wasm/wasm-native-external-refs.h"
#include "src/external-reference.h"
#include "src/signature.h"
#include <vector>

namespace v8 {
namespace internal {
namespace wasm {

bool find_native_function(const char* find_name, FunctionSig* sig, ExternalReference (**ref)()) {
#define ARGS_TO_VECTOR(...) {__VA_ARGS__}
#define FIND_NATIVE_FUNCTION(F, function, name, p, r)                                       \
  if(strcmp(name, find_name) == 0) {                                                        \
    std::vector<ValueType> params = p;                                                      \
    std::vector<ValueType> rets = r;                                                        \
    if(params.size() != sig->parameter_count() || rets.size() != sig->return_count()) {     \
      return false;                                                                         \
    }                                                                                       \
    for(size_t i=0; i < params.size(); i++) {                                               \
      if(params[i] != sig->GetParam(i)) {                                                   \
        return false;                                                                       \
      }                                                                                     \
    }                                                                                       \
    for(size_t i=0; i < rets.size(); i++) {                                                 \
      if(rets[i] != sig->GetReturn(i)) {                                                    \
        return false;                                                                       \
      }                                                                                     \
    }                                                                                       \
    *ref = ExternalReference::wasm_##function;                                              \
    return true;                                                                            \
  }
WASM_EXTERNAL_REFERENCE_LIST(void, FIND_NATIVE_FUNCTION, ARGS_TO_VECTOR, ARGS_TO_VECTOR)
#undef FIND_NATIVE_FUNCTION
#undef ARGS_TO_VECTOR
  return false;
}

}  // namespace wasm
}  // namespace internal
}  // namespace v8
