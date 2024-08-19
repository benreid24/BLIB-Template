#ifndef PROPERTIES_HPP
#define PROPERTIES_HPP

#include <BLIB/Engine/Configuration.hpp>
#include <BLIB/Engine/Properties.hpp>
#include <BLIB/Engine/Property.hpp>
#include <BLIB/Util/NonCopyable.hpp>
#include <Constants.hpp>
#include <string>

/**
 * @brief Common core application properties here. We may want to load these from a file or they may
 *        simply be constants. Some properties may be loaded into the engine configuration store
 */
class {
public:
    BLIB_PROPERTY(DataDirectory, std::string, "app.config.data_dir", "");

    BLIB_PROPERTY(MusicPath, std::string, "blib.playlist.song_path", Constants::DefaultMusicPath);

    BLIB_PROPERTY(SpritesheetPath, std::string, "blib.animation.spritesheet_path",
                  Constants::DefaultSpritesheetPath);

    bool load() {
        if (!bl::engine::Configuration::load(
                bl::util::FileUtil::joinPath(DataDirectory.get(), Constants::ConfigFilePath))) {
            BL_LOG_WARN << "Properties file not found, using defaults";
        }
        bl::engine::Properties::syncFromConfig();

        if (DataDirectory.get().empty()) {
            DataDirectory.set(bl::util::FileUtil::getDataDirectory(Constants::AppName));
        }

        // TODO - validate state here

        return true;
    }

    bool save() {
        bl::engine::Properties::syncToConfig();
        return bl::engine::Configuration::save(
            bl::util::FileUtil::joinPath(DataDirectory.get(), Constants::ConfigFilePath));
    }

} Properties;

#endif
