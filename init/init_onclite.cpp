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
   Copyright (c) 2016, The CyanogenMod Project
   Copyright (C) 2019 The LineageOS Project.
   Copyright (C) 2020-2021 The MoKee Open Source Project
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <cstdlib>
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
using android::base::GetProperty;
using std::string;

void property_override(string prop, string value)
{
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

void vendor_load_properties()
{
    string device, model, desc;

    string region = GetProperty("ro.boot.hwcountry", "");
    string hwversion = GetProperty("ro.boot.hwversion", "");

    if (region == "India" && hwversion == "1.19.0") {
        device = "onc";
        model = "Redmi Y3";
    } else {
        device = "onclite";
        model = "Redmi 7";
    }

    // Override all partitions' props
    string prop_partitions[] = { "", "odm.", "product.", "system.",
                    "system_ext.", "bootimage.", "vendor." };

    for (const string &prop : prop_partitions) {
        property_override(string("ro.product.") + prop + string("name"), device);
        property_override(string("ro.product.") + prop + string("device"), device);
        property_override(string("ro.product.") + prop + string("model"), model);
        property_override(string("ro.") + prop + string("build.product"), device);
    }

    // Set dalvik heap configuration
    string heapstartsize, heapgrowthlimit, heapsize, heapminfree,
            heapmaxfree, heaptargetutilization;

    struct sysinfo sys;
    sysinfo(&sys);

    if (sys.totalram > 3072ull * 1024 * 1024) {
        // Set for 4GB RAM
        // from - phone-xxhdpi-4096-dalvik-heap.mk
        heapstartsize = "8m";
        heapgrowthlimit = "256m";
        heapsize = "512m";
        heaptargetutilization = "0.6";
        heapminfree = "4m";
        heapmaxfree = "16m";
    } else if (sys.totalram > 2048ull * 1024 * 1024) {
        // Set for 3GB RAM
        // from - phone-xhdpi-2048-dalvik-heap.mk
        heapstartsize = "8m";
        heapgrowthlimit = "192m";
        heapsize = "512m";
        heaptargetutilization = "0.75";
        heapminfree = "2m";
        heapmaxfree = "8m";
    } else {
        // Set for 2GB RAM
        // from go_defaults_common.prop
        heapstartsize = "8m";
        heapgrowthlimit = "128m";
        heapsize = "256m";
        heaptargetutilization = "0.75";
        heapminfree = "2m";
        heapmaxfree = "8m";
    }

    property_override("dalvik.vm.heapstartsize", heapstartsize);
    property_override("dalvik.vm.heapgrowthlimit", heapgrowthlimit);
    property_override("dalvik.vm.heapsize", heapsize);
    property_override("dalvik.vm.heaptargetutilization", heaptargetutilization);
    property_override("dalvik.vm.heapminfree", heapminfree);
    property_override("dalvik.vm.heapmaxfree", heapmaxfree);


    // SafetyNet Workaround
    property_override("ro.boot.verifiedbootstate", "green");
}
