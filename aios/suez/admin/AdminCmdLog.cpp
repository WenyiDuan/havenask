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
#include "suez/admin/AdminCmdLog.h"

#include <iosfwd>

#include "alog/Logger.h"
#include "autil/Log.h"

using namespace std;

AUTIL_DECLARE_AND_SETUP_LOGGER(suez, AdminCmdLog);

namespace suez {

AdminCmdLog::AdminCmdLog() { _success = false; }

AdminCmdLog::~AdminCmdLog() { log(); }

void AdminCmdLog::log() {
    AUTIL_LOG(INFO,
              "operate=[%s], success=[%d], request=[%s], cost=[%dms]",
              _operateCmd.c_str(),
              _success,
              _request.c_str(),
              _cost);
}

} // namespace suez
