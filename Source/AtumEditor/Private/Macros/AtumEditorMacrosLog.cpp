// © 2023 Kaya Adrian.

#include "Macros/AtumEditorMacrosLog.h"

#include "Settings/AtumSettingsEditor.h"


#define LOCTEXT_NAMESPACE "AtumEditorMacrosLog"

DEFINE_LOG_CATEGORY(LogAtumEditor)

namespace
{
	/**
	 * Checks if the editor module is allowed to log messages
	 * 
	 * @return Can messages be logged?
	 */
	[[nodiscard]]
	FORCEINLINE bool AreLogsEnabled() noexcept { return GetDefault<UAtumSettingsEditor>()->IsLogAtumEditorEnabled(); }
}
const IsLogAtumEditorEnabledCheck IsLogAtumEditorEnabled = &AreLogsEnabled;

#undef LOCTEXT_NAMESPACE
