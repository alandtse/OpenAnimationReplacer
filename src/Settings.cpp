#include "Settings.h"
#include <Simpleini.h>

void ReadBoolSetting(const CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, bool& a_setting)
{
	const char* bFound = nullptr;
	bFound = a_ini.GetValue(a_sectionName, a_settingName);
	if (bFound) {
		a_setting = a_ini.GetBoolValue(a_sectionName, a_settingName);
	}
}

void ReadFloatSetting(const CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, float& a_setting)
{
	const char* bFound = nullptr;
	bFound = a_ini.GetValue(a_sectionName, a_settingName);
	if (bFound) {
		a_setting = static_cast<float>(a_ini.GetDoubleValue(a_sectionName, a_settingName));
	}
}

void ReadUInt16Setting(const CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, uint16_t& a_setting)
{
	const char* bFound = nullptr;
	bFound = a_ini.GetValue(a_sectionName, a_settingName);
	if (bFound) {
		a_setting = static_cast<uint16_t>(a_ini.GetLongValue(a_sectionName, a_settingName));
	}
}

void ReadUInt32Setting(const CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, uint32_t& a_setting)
{
	const char* bFound = nullptr;
	bFound = a_ini.GetValue(a_sectionName, a_settingName);
	if (bFound) {
		a_setting = static_cast<uint32_t>(a_ini.GetLongValue(a_sectionName, a_settingName));
	}
}

void WriteBoolSetting(const char* a_sectionName, const char* a_settingName, const bool& a_setting)
{
	CSimpleIniA ini;
	ini.SetUnicode();

	ini.LoadFile(Settings::iniPath.data());

	ini.SetBoolValue(a_sectionName, a_settingName, a_setting);

	ini.SaveFile(Settings::iniPath.data());
}

void WriteFloatSetting(const char* a_sectionName, const char* a_settingName, const float& a_setting)
{
	CSimpleIniA ini;
	ini.SetUnicode();

	ini.LoadFile(Settings::iniPath.data());

	ini.SetDoubleValue(a_sectionName, a_settingName, a_setting);

	ini.SaveFile(Settings::iniPath.data());
}

void WriteUInt16Setting(const char* a_sectionName, const char* a_settingName, const uint16_t& a_setting)
{
	CSimpleIniA ini;
	ini.SetUnicode();

	ini.LoadFile(Settings::iniPath.data());

	ini.SetLongValue(a_sectionName, a_settingName, a_setting);

	ini.SaveFile(Settings::iniPath.data());
}

void WriteUInt32Setting(const char* a_sectionName, const char* a_settingName, const uint32_t& a_setting)
{
	CSimpleIniA ini;
	ini.SetUnicode();

	ini.LoadFile(Settings::iniPath.data());

	ini.SetLongValue(a_sectionName, a_settingName, a_setting);

	ini.SaveFile(Settings::iniPath.data());
}

void Settings::Initialize()
{
	uToggleUIKeyData[0] = 0x18;
	uToggleUIKeyData[1] = false;
	uToggleUIKeyData[2] = true;
	uToggleUIKeyData[3] = false;
}

void Settings::ReadSettings()
{
	const auto readIni = [&](auto a_path) {
		CSimpleIniA ini;
		ini.SetUnicode();

		if (ini.LoadFile(a_path.data()) >= 0) {
			// General
			ReadUInt16Setting(ini, "General", "uAnimationLimit", uAnimationLimit);
			ReadUInt32Setting(ini, "General", "uHavokHeapSize", uHavokHeapSize);
			ReadBoolSetting(ini, "General", "bAsyncParsing", bAsyncParsing);
			ReadBoolSetting(ini, "General", "bLoadDefaultBehaviorsInMainMenu", bLoadDefaultBehaviorsInMainMenu);

			// Duplicate filtering
			ReadBoolSetting(ini, "Filtering", "bFilterOutDuplicateAnimations", bFilterOutDuplicateAnimations);
			//ReadBoolSetting(ini, "Filtering", "bCacheAnimationFileHashes", bCacheAnimationFileHashes);

			// UI
			ReadBoolSetting(ini, "UI", "bEnableUI", bEnableUI);
			ReadBoolSetting(ini, "UI", "bShowWelcomeBanner", bShowWelcomeBanner);
			ReadUInt32Setting(ini, "UI", "uToggleUIKey", uToggleUIKeyData[0]);
			ReadUInt32Setting(ini, "UI", "uToggleUIKeyCtrl", uToggleUIKeyData[1]);
			ReadUInt32Setting(ini, "UI", "uToggleUIKeyShift", uToggleUIKeyData[2]);
			ReadUInt32Setting(ini, "UI", "uToggleUIKeyAlt", uToggleUIKeyData[3]);
			ReadFloatSetting(ini, "UI", "fUIScale", fUIScale);

			ReadBoolSetting(ini, "UI", "bEnableAnimationQueueProgressBar", bEnableAnimationQueueProgressBar);
			ReadFloatSetting(ini, "UI", "fAnimationQueueLingerTime", fAnimationQueueLingerTime);

			ReadBoolSetting(ini, "UI", "bEnableAnimationLog", bEnableAnimationLog);
			ReadFloatSetting(ini, "UI", "fAnimationLogWidth", fAnimationLogWidth);
			ReadUInt32Setting(ini, "UI", "uAnimationLogSize", uAnimationLogMaxEntries);
			ReadUInt32Setting(ini, "UI", "uAnimationActivateLogMode", uAnimationActivateLogMode);
			ReadUInt32Setting(ini, "UI", "uAnimationEchoLogMode", uAnimationEchoLogMode);
			ReadUInt32Setting(ini, "UI", "uAnimationLoopLogMode", uAnimationLoopLogMode);
			ReadBoolSetting(ini, "UI", "bAnimationLogOnlyActiveGraph", bAnimationLogOnlyActiveGraph);
			ReadBoolSetting(ini, "UI", "bAnimationLogWriteToTextLog", bAnimationLogWriteToTextLog);

			ReadBoolSetting(ini, "UI", "bEnableAnimationEventLog", bEnableAnimationEventLog);
			ReadBoolSetting(ini, "UI", "bAnimationLogOrderDescending", bAnimationLogOrderDescending);
			ReadFloatSetting(ini, "UI", "fAnimationEventLogWidth", fAnimationEventLogWidth);
			ReadFloatSetting(ini, "UI", "fAnimationEventLogHeight", fAnimationEventLogHeight);
			ReadBoolSetting(ini, "UI", "bAnimationEventLogWriteToTextLog", bAnimationEventLogWriteToTextLog);

			ReadFloatSetting(ini, "UI", "fAnimationLogsOffsetX", fAnimationLogsOffsetX);
			ReadFloatSetting(ini, "UI", "fAnimationLogsOffsetY", fAnimationLogsOffsetY);

			// Workarounds
			ReadBoolSetting(ini, "Workarounds", "bLegacyKeepRandomResultsByDefault", bLegacyKeepRandomResultsByDefault);

			// Experimental
			ReadBoolSetting(ini, "Experimental", "bDisablePreloading", bDisablePreloading);
			ReadBoolSetting(ini, "Experimental", "bIncreaseAnimationLimit", bIncreaseAnimationLimit);

			// Debug
			ReadBoolSetting(ini, "Debug", "bEnableDebugDraws", bEnableDebugDraws);

			return true;
		}
		return false;
	};

	logger::info("Reading .ini...");
	if (readIni(iniPath)) {
		logger::info("...success");
	} else {
		logger::info("...ini not found, creating a new one");
		WriteSettings();
	}

	ClampAnimLimit();
}

void Settings::WriteSettings()
{
	logger::info("Writing .ini...");

	CSimpleIniA ini;
	ini.SetUnicode();

	ini.LoadFile(iniPath.data());

	// General
	ini.SetLongValue("General", "uAnimationLimit", uAnimationLimit);
	ini.SetLongValue("General", "uHavokHeapSize", uHavokHeapSize);
	ini.SetBoolValue("General", "bAsyncParsing", bAsyncParsing);
	ini.SetBoolValue("General", "bLoadDefaultBehaviorsInMainMenu", bLoadDefaultBehaviorsInMainMenu);

	// Duplicate filtering
	ini.SetBoolValue("Filtering", "bFilterOutDuplicateAnimations", bFilterOutDuplicateAnimations);
	//ini.SetBoolValue("Filtering", "bCacheAnimationFileHashes", bCacheAnimationFileHashes);

	// UI
	ini.SetBoolValue("UI", "bEnableUI", bEnableUI);
	ini.SetBoolValue("UI", "bShowWelcomeBanner", bShowWelcomeBanner);
	ini.SetLongValue("UI", "uToggleUIKey", uToggleUIKeyData[0]);
	ini.SetLongValue("UI", "uToggleUIKeyCtrl", uToggleUIKeyData[1]);
	ini.SetLongValue("UI", "uToggleUIKeyShift", uToggleUIKeyData[2]);
	ini.SetLongValue("UI", "uToggleUIKeyAlt", uToggleUIKeyData[3]);
	ini.SetDoubleValue("UI", "fUIScale", fUIScale);

	ini.SetBoolValue("UI", "bEnableAnimationQueueProgressBar", bEnableAnimationQueueProgressBar);
	ini.SetDoubleValue("UI", "fAnimationQueueLingerTime", fAnimationQueueLingerTime);

	ini.SetBoolValue("UI", "bEnableAnimationLog", bEnableAnimationLog);
	ini.SetDoubleValue("UI", "fAnimationLogWidth", fAnimationLogWidth);
	ini.SetLongValue("UI", "uAnimationLogSize", uAnimationLogMaxEntries);
	ini.SetLongValue("UI", "uAnimationActivateLogMode", uAnimationActivateLogMode);
	ini.SetLongValue("UI", "uAnimationEchoLogMode", uAnimationEchoLogMode);
	ini.SetLongValue("UI", "uAnimationLoopLogMode", uAnimationLoopLogMode);
	ini.SetBoolValue("UI", "bAnimationLogOnlyActiveGraph", bAnimationLogOnlyActiveGraph);
	ini.SetBoolValue("UI", "bAnimationLogWriteToTextLog", bAnimationLogWriteToTextLog);

	ini.SetBoolValue("UI", "bEnableAnimationEventLog", bEnableAnimationEventLog);
	ini.SetBoolValue("UI", "bAnimationLogOrderDescending", bAnimationLogOrderDescending);
	ini.SetDoubleValue("UI", "fAnimationEventLogWidth", fAnimationEventLogWidth);
	ini.SetDoubleValue("UI", "fAnimationEventLogHeight", fAnimationEventLogHeight);
	ini.SetBoolValue("UI", "bAnimationEventLogWriteToTextLog", bAnimationEventLogWriteToTextLog);

	ini.SetDoubleValue("UI", "fAnimationLogsOffsetX", fAnimationLogsOffsetX);
	ini.SetDoubleValue("UI", "fAnimationLogsOffsetY", fAnimationLogsOffsetY);

	// Workarounds
	ini.SetBoolValue("Workarounds", "bLegacyKeepRandomResultsByDefault", bLegacyKeepRandomResultsByDefault);

	// Experimental
	ini.SetBoolValue("Experimental", "bDisablePreloading", bDisablePreloading);
	ini.SetBoolValue("Experimental", "bIncreaseAnimationLimit", bIncreaseAnimationLimit);

	// Debug
	ini.SetBoolValue("Debug", "bEnableDebugDraws", bEnableDebugDraws);

	ini.SaveFile(iniPath.data());

	logger::info("...success");
}

uint16_t Settings::GetMaxAnimLimit()
{
	return bIncreaseAnimationLimit ? maxAnimLimitIncreased : maxAnimLimitDefault;
}

void Settings::ClampAnimLimit()
{
	uAnimationLimit = std::min(uAnimationLimit, GetMaxAnimLimit());
}
