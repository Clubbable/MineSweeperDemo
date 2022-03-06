#include "PluginTabManager.h"
#include "PluginShared.h"

#include "PluginStyle.h"
#include "MinesweeperWidget.h"

#include "Widgets/Docking/SDockTab.h"

void FPluginTabManager::Startup()
{
	TabId = TEXT(PLUGIN_NAME "Tab");

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TabId, FOnSpawnTab::CreateRaw(this, &FPluginTabManager::SpawnTab))
		.SetDisplayName(PLUGIN_LOCTEXT("TabName", PLUGIN_NAME))
		.SetTooltipText(PLUGIN_LOCTEXT("TabTooltip", PLUGIN_NAME))
		.SetIcon(FSlateIcon(FPluginStyle::GetStyleSetName(), "TabIcon"))
		.SetMenuType(ETabSpawnerMenuType::Hidden) // https://answers.unrealengine.com/questions/164648/view.html
	;
}

void FPluginTabManager::Shutdown()
{
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TabId);
}

TSharedRef<SDockTab> FPluginTabManager::SpawnTab(const FSpawnTabArgs& TabSpawnArgs)
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SMinesweeperWidget)
			.TabManager(SharedThis(this))
		];

	return SpawnedTab;
}
