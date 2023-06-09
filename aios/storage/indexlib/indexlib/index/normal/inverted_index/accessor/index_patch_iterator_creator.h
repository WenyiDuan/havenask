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

#include <memory>

#include "indexlib/common_define.h"
#include "indexlib/indexlib.h"

DECLARE_REFERENCE_CLASS(config, IndexPartitionSchema);
DECLARE_REFERENCE_CLASS(index_base, PartitionData);
DECLARE_REFERENCE_CLASS(index_base, Version);
DECLARE_REFERENCE_CLASS(index, IndexPatchIterator);

namespace indexlib { namespace index {

class IndexPatchIteratorCreator
{
public:
    IndexPatchIteratorCreator();
    ~IndexPatchIteratorCreator();

public:
    static IndexPatchIteratorPtr Create(const config::IndexPartitionSchemaPtr& schema,
                                        const index_base::PartitionDataPtr& partitionData,
                                        bool ignorePatchToOldIncSegment, const index_base::Version& lastLoadVersion,
                                        segmentid_t lastLoadedSegment);

private:
    IE_LOG_DECLARE();
};

DEFINE_SHARED_PTR(IndexPatchIteratorCreator);
}} // namespace indexlib::index