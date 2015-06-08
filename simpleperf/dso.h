/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SIMPLE_PERF_DSO_H_
#define SIMPLE_PERF_DSO_H_

#include <memory>
#include <set>
#include <string>

struct SymbolEntry {
  std::string name;
  uint64_t addr;
  uint64_t len;
};

struct SymbolComparator {
  bool operator()(const std::unique_ptr<SymbolEntry>& symbol1,
                  const std::unique_ptr<SymbolEntry>& symbol2);
};

struct DsoEntry {
  std::string path;
  std::set<std::unique_ptr<SymbolEntry>, SymbolComparator> symbols;

  const SymbolEntry* FindSymbol(uint64_t offset_in_dso);
};

class DsoFactory {
 public:
  static std::unique_ptr<DsoEntry> LoadKernel();
  static std::unique_ptr<DsoEntry> LoadKernelModule(const std::string& dso_path);
  static std::unique_ptr<DsoEntry> LoadDso(const std::string& dso_path);
};

#endif  // SIMPLE_PERF_DSO_H_
