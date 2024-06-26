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
#include "indexlib/index/normal/attribute/accessor/pack_attribute_writer.h"

#include "indexlib/common/field_format/attribute/attribute_convertor_factory.h"
#include "indexlib/index/normal/attribute/accessor/in_mem_var_num_attribute_reader.h"

using namespace std;
using namespace autil::mem_pool;
using namespace autil;

using namespace indexlib::common;
using namespace indexlib::config;
using namespace indexlib::util;

namespace indexlib { namespace index {
IE_LOG_SETUP(index, PackAttributeWriter);

PackAttributeWriter::PackAttributeWriter(const PackAttributeConfigPtr& packAttrConfig)
    : StringAttributeWriter(packAttrConfig->CreateAttributeConfig())
    , mPackAttrConfig(packAttrConfig)
    , mBuffer(PACK_ATTR_BUFF_INIT_SIZE, &mSimplePool)
{
    mAttrConvertor.reset(AttributeConvertorFactory::GetInstance()->CreatePackAttrConvertor(packAttrConfig));
    mPackAttrFormatter.reset(new PackAttributeFormatter);
    mPackAttrFormatter->Init(mPackAttrConfig);
}

PackAttributeWriter::~PackAttributeWriter() {}

bool PackAttributeWriter::UpdateEncodeFields(docid_t docId, const PackAttributeFields& packAttrFields)
{
    assert(mAccessor);

    AttributeConfigPtr dataConfig = mPackAttrConfig->CreateAttributeConfig();
    InMemVarNumAttributeReader<char> inMemReader(mAccessor, dataConfig->GetCompressType(),
                                                 dataConfig->GetFieldConfig()->GetFixedMultiValueCount(), false);
    MultiChar packValue;
    bool isNull = false;
    if (!inMemReader.Read(docId, packValue, isNull)) {
        IE_LOG(ERROR, "read doc [%d] fail!", docId);
        ERROR_COLLECTOR_LOG(ERROR, "read doc [%d] fail!", docId);
        return false;
    }

    StringView mergeValue =
        mPackAttrFormatter->MergeAndFormatUpdateFields(packValue.data(), packAttrFields, true, mBuffer);
    if (mergeValue.empty()) {
        IE_LOG(ERROR,
               "MergeAndFormat pack attribute fields"
               " for doc [%d] fail!",
               docId);
        ERROR_COLLECTOR_LOG(ERROR,
                            "MergeAndFormat pack attribute fields"
                            " for doc [%d] fail!",
                            docId);
        return false;
    }
    return UpdateField(docId, mergeValue);
}
}} // namespace indexlib::index
