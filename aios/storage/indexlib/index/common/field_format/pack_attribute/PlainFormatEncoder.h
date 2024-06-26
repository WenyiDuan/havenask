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

#include "autil/Log.h"
#include "autil/NoCopyable.h"
#include "indexlib/index/common/field_format/pack_attribute/AttributeReferenceTyped.h"

namespace indexlibv2::index {

class PlainFormatEncoder : private autil::NoCopyable
{
public:
    using AttributeFieldData = std::pair<autil::StringView, int32_t>;

public:
    PlainFormatEncoder(uint32_t fixAttrSize, const std::vector<std::shared_ptr<AttributeReference>>& fixLenAttributes,
                       const std::vector<std::shared_ptr<AttributeReference>>& varLenAttributes);
    ~PlainFormatEncoder();

public:
    // pack data with encoded count
    [[nodiscard]] bool Encode(const autil::StringView& encodePackValue, char* buffer, size_t bufferSize,
                              autil::StringView& plainDataValue);

    uint32_t GetEncodeSimHash(const autil::StringView& encodePackValue) const;

    // plain value without encoded count
    [[nodiscard]] bool Decode(const autil::StringView& plainValue, autil::mem_pool::Pool* pool,
                              autil::StringView& packValue) const;

    bool DecodeDataValues(const autil::StringView& plainValue, std::vector<AttributeFieldData>& dataValues);

    autil::StringView EncodeDataValues(const std::vector<AttributeFieldData>& dataValues, autil::mem_pool::Pool* pool);

private:
    autil::StringView InnerEncode(const autil::StringView& encodePackValue, char* buffer, size_t bufferSize) const;

private:
    size_t _fixAttrSize;
    std::vector<std::shared_ptr<AttributeReference>> _fixLenAttributes;
    std::vector<std::shared_ptr<AttributeReference>> _varLenAttributes;

private:
    AUTIL_LOG_DECLARE();
};

} // namespace indexlibv2::index
