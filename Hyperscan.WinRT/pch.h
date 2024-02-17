#pragma once

// Undefine GetCurrentTime macro to prevent
// conflict with Storyboard::GetCurrentTime
#ifdef GetCurrentTime
#undef GetCurrentTime
#endif // GetCurrentTime

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <hs/hs.h>
#include <wil/cppwinrt_helpers.h>
