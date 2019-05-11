#include "src/third_party/native/system.h"
#include "src/v8memory.h"
#include "src/globals.h"
#include <chrono>
#include <iostream>

namespace v8 {
namespace internal {
namespace wasm {

#define PRINT_STACK_FUNC(sfx, type) \
void prints_##sfx(Address mem, Address data) { \
  std::cout << ReadUnalignedValue<type>(data) << std::endl; \
}
PRINT_STACK_FUNC(i32, int32_t)
PRINT_STACK_FUNC(i64, int64_t)
PRINT_STACK_FUNC(f32, float)
PRINT_STACK_FUNC(f64, double)

#define PRINT_MEMORY_FUNC(sfx, type) \
void printm_##sfx(Address mem, Address data) { \
  int32_t *dataI32 = reinterpret_cast<int32_t*>(data); \
  int32_t offset = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(dataI32)); \
  int32_t size = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(++dataI32)); \
  type* lmem = reinterpret_cast<type*>(reinterpret_cast<byte*>(mem) + offset); \
  while(size-- > 0) { \
    std::cout << *(lmem++) << " "; \
  } \
  std::cout << std::endl;\
}
PRINT_MEMORY_FUNC(i32, int32_t)
PRINT_MEMORY_FUNC(i64, int64_t)
PRINT_MEMORY_FUNC(f32, float)
PRINT_MEMORY_FUNC(f64, double)

void time_ms(Address mem, Address data) {
  WriteUnalignedValue<int64_t>(data, std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()).count());
}

}
}
}

