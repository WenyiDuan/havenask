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
#ifndef __INDEXLIB_ATTRIBUTE_VALUE_INITIALIZER_H
#define __INDEXLIB_ATTRIBUTE_VALUE_INITIALIZER_H

#include <memory>

#include "autil/ConstString.h"
#include "autil/mem_pool/Pool.h"
#include "indexlib/common_define.h"
#include "indexlib/indexlib.h"

namespace indexlib { namespace common {

class AttributeValueInitializer
{
public:
    AttributeValueInitializer() {}
    virtual ~AttributeValueInitializer() {}

public:
    virtual bool GetInitValue(docid_t docId, char* buffer, size_t bufLen) const = 0;

    virtual bool GetInitValue(docid_t docId, autil::StringView& value, autil::mem_pool::Pool* memPool) const = 0;

private:
    IE_LOG_DECLARE();
};

DEFINE_SHARED_PTR(AttributeValueInitializer);
}} // namespace indexlib::common

#endif //__INDEXLIB_ATTRIBUTE_VALUE_INITIALIZER_H