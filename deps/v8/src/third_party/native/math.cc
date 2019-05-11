#include "src/third_party/native/math.h"
#include "src/v8memory.h"
#include "src/globals.h"
#include "src/base/ieee754.h"

namespace v8 {
namespace internal {
namespace wasm {

void sigmoid(Address mem, Address data) {
  const double* res = reinterpret_cast<double*>(data) + 1;
  WriteUnalignedValue<double>(reinterpret_cast<Address>(res), 
      1 / (1 + base::ieee754::exp(-ReadUnalignedValue<double>(data))));
}

}
}
}

