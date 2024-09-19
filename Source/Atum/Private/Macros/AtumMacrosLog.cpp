// © 2023 Kaya Adrian.

#include "Macros/AtumMacrosLog.h"

#include "Settings/AtumSettingsDev.h"


#define LOCTEXT_NAMESPACE "AtumMacrosLog"

DEFINE_LOG_CATEGORY(LogAtum)

namespace
{
	/**
	 * Checks if the runtime module is allowed to log messages
	 * 
	 * @return Can messages be logged?
	 */
	[[nodiscard]]
	FORCEINLINE bool AreLogsEnabled() noexcept { return GetDefault<UAtumSettingsDev>()->IsLogAtumEnabled(); }
}
const IsLogAtumEnabledCheck IsLogAtumEnabled = &AreLogsEnabled;

#undef LOCTEXT_NAMESPACE
