#
# Copyright (C) 2019-2020 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/product_launched_with_p.mk)

# Inherit from device side
$(call inherit-product, device/xiaomi/onclite/device.mk)

# Inherit some common ConquerOS stuff.
$(call inherit-product, vendor/ssos/config/common.mk)

# Device identifier. This must come after all inclusions.
PRODUCT_NAME := ssos_onclite
PRODUCT_DEVICE := onclite
PRODUCT_BRAND := Xiaomi
PRODUCT_MODEL := Redmi 7
PRODUCT_MANUFACTURER := Xiaomi

# Face Unlock
TARGET_FACE_UNLOCK_SUPPORTED := false
TARGET_BOOT_ANIMATION_RES := 720

PRODUCT_PRODUCT_PROPERTIES += \
    ro.ssos.cpu=SD632

# GApps
#TARGET_USE_GAPPS := false
#ifeq ($(TARGET_USE_GAPPS),true)
#PRODUCT_PACKAGES += \
#    GAppsExclude
#endif
