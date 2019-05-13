#include "src/third_party/native/jsNet.h"
#include "src/v8memory.h"
#include "src/globals.h"
#include "src/base/ieee754.h"

namespace v8 {
namespace internal {
namespace wasm {

void jsNet_sigmoid(Address mem, Address data) {
  const byte* stack = reinterpret_cast<byte*>(data);
  const double p1 = ReadUnalignedValue<double>(reinterpret_cast<Address>(stack));
  const int32_t p2 = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(stack + sizeof(double)));
  const int32_t p3 = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(stack + sizeof(double) + sizeof(int32_t)));
  const double val = 1 / (1 + base::ieee754::exp(-p1));
  WriteUnalignedValue<double>(reinterpret_cast<Address>(stack + sizeof(double) + sizeof(int32_t) + sizeof(int32_t)), (p2 ? val*(1-val) : val));
}

}
}
}

