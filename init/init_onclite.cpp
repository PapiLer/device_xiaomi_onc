/*
  Copyright (C) 2020 The Android Open Source Project

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 */

#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <sys/sysinfo.h>
#include <unistd.h>

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "vendor_init.h"
#include "property_service.h"


using android::base::GetProperty;
using std::string;


void property_override(string prop, string value) {
    auto pi = (prop_info*) __system_property_find(prop.c_str());

    if (pi != nullptr)
        __system_property_update(pi, value.c_str(), value.size());
    else
        __system_property_add(prop.c_str(), prop.size(), value.c_str(), value.size());
}


void load_props(string device, string model) {
    string RO_PROP_SOURCES[] = { "", "odm.", "system.", "vendor.", "product.", "bootimage.", "system_ext." };

    for (const string &source : RO_PROP_SOURCES) {
        property_override(string("ro.product.") + source + string("name"), device);
        property_override(string("ro.product.") + source + string("device"), device);
        property_override(string("ro.product.") + source + string("model"), model);
    }
}


void vendor_load_properties() {
    // Show correct device and model name as per boot cert
    string boot_cert = android::base::GetProperty("ro.boot.product.cert", "");

    if (boot_cert == "M1810F6LG" || boot_cert == "M1810F6LH" || boot_cert == "M1810F6LI"
            || boot_cert == "M1810F6LE" || boot_cert == "M1810F6LT" || boot_cert == "M1810F6LC")
        load_props("onclite", "Redmi 7");
    else
        load_props("onc", "Redmi Y3");
}
