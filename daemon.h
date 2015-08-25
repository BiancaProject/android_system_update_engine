//
// Copyright (C) 2015 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef UPDATE_ENGINE_DAEMON_H_
#define UPDATE_ENGINE_DAEMON_H_

#include <memory>
#include <string>

#include <chromeos/daemons/dbus_daemon.h>

#include "update_engine/certificate_checker.h"
#include "update_engine/dbus_service.h"
#include "update_engine/real_system_state.h"
#include "update_engine/subprocess.h"

namespace chromeos_update_engine {

class UpdateEngineDaemon : public chromeos::DBusDaemon {
 public:
  UpdateEngineDaemon() = default;

 protected:
  int OnInit() override;

 private:
  // Run from the main loop when the |dbus_adaptor_| object is registered. At
  // this point we can request ownership of the DBus service name and continue
  // initialization.
  void OnDBusRegistered(bool succeeded);

  // The Subprocess singleton class requires a chromeos::MessageLoop in the
  // current thread, so we need to initialize it from this class instead of
  // the main() function.
  Subprocess subprocess_;

  std::unique_ptr<RealSystemState> real_system_state_;
  OpenSSLWrapper openssl_wrapper_;
  std::unique_ptr<UpdateEngineAdaptor> dbus_adaptor_;

  DISALLOW_COPY_AND_ASSIGN(UpdateEngineDaemon);
};

}  // namespace chromeos_update_engine

#endif  // UPDATE_ENGINE_DAEMON_H_