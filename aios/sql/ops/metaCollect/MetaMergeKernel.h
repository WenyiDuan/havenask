/*
 * Copyright 2014-present Alibaba Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <string>

#include "navi/common.h"
#include "navi/engine/Kernel.h"
#include "navi/engine/KernelConfigContext.h"
#include "sql/proto/SqlSearchInfoCollector.h"

namespace navi {
class KernelComputeContext;
class KernelDefBuilder;
class KernelInitContext;
} // namespace navi

namespace sql {

class MetaMergeKernel : public navi::Kernel {
public:
    MetaMergeKernel();
    ~MetaMergeKernel();
    MetaMergeKernel(const MetaMergeKernel &) = delete;
    MetaMergeKernel &operator=(const MetaMergeKernel &) = delete;

public:
    void def(navi::KernelDefBuilder &builder) const override;
    bool config(navi::KernelConfigContext &ctx) override;
    navi::ErrorCode init(navi::KernelInitContext &ctx) override;
    navi::ErrorCode compute(navi::KernelComputeContext &ctx) override;

public:
    static const std::string KERNEL_ID;
    static const std::string INPUT_PORT;
    static const std::string OUTPUT_PORT;

private:
    SqlSearchInfoCollectorPtr _collector;
};

} // namespace sql
