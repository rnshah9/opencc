#include "Exception.hpp"
#include "UTF8Util.hpp"
#include <climits>
#include <stdint.h>
#include <stdio.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::string str = provider.ConsumeRandomLengthString();
  const char* cstr = str.c_str();
  size_t maxByteLength = provider.ConsumeIntegral<size_t>();

  try {
    opencc::UTF8Util::TruncateUTF8(cstr, maxByteLength);
  } catch (opencc::InvalidUTF8 err) {
  }

  return 0;
}