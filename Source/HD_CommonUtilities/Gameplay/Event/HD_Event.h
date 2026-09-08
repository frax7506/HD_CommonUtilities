#pragma once

#include "HD_Types.h"

#define DECLARE_EVENT(aEventEnumType, aEventEnumEntry) static aEventEnumType GetStaticType() { return aEventEnumType::aEventEnumEntry; }
#define DECLARE_EVENT_ENUM(aEventEnumType, ...) enum class aEventEnumType : u8 { Invalid, __VA_ARGS__, Count }
