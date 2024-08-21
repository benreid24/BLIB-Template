#include <Core/Properties.hpp>

#include <BLIB/Util/FileUtil.hpp>

namespace core
{
PropertiesStore Properties;

bool PropertiesStore::load() {
    if (!bl::engine::Configuration::load(
            bl::util::FileUtil::joinPath(DataDirectory.get(), Constants::ConfigFilePath))) {
        BL_LOG_WARN << "Properties file not found, using defaults";
    }
    bl::engine::Properties::syncFromConfig();

    if (DataDirectory.get().empty()) {
        DataDirectory.set(bl::util::FileUtil::getDataDirectory(Constants::AppName));
    }

    DataDirectory.syncToConfig();
    bl::engine::Configuration::log();

    // TODO - SETUP_TASK: validate state here

    return true;
}

bool PropertiesStore::save() {
    bl::engine::Properties::syncToConfig();
    return bl::engine::Configuration::save(
        bl::util::FileUtil::joinPath(DataDirectory.get(), Constants::ConfigFilePath));
}

} // namespace core
