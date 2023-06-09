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

#include "indexlib/util/Bitmap.h"
#include "indexlib/util/Singleton.h"

namespace indexlib { namespace util {

class KmonitorTagvNormalizer : public util::Singleton<KmonitorTagvNormalizer>
{
public:
    KmonitorTagvNormalizer();
    ~KmonitorTagvNormalizer();

    KmonitorTagvNormalizer(const KmonitorTagvNormalizer&) = delete;
    KmonitorTagvNormalizer& operator=(const KmonitorTagvNormalizer&) = delete;
    KmonitorTagvNormalizer(KmonitorTagvNormalizer&&) = delete;
    KmonitorTagvNormalizer& operator=(KmonitorTagvNormalizer&&) = delete;

public:
    // invalid char will be replace by '_'
    std::string Normalize(const std::string& str, char rep = '_');

private:
    void InitValidCharBitmap();
    bool IsValidChar(char a) const { return _bitmap.Test((uint8_t)a); }

private:
    Bitmap _bitmap;
};

typedef std::shared_ptr<KmonitorTagvNormalizer> KmonitorTagvNormalizerPtr;

}} // namespace indexlib::util