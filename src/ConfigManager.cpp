#include "ConfigManager.h"

#include <fstream>
#include <filesystem>

ConfigManager::ConfigManager() {}
ConfigManager::~ConfigManager() {}

void ConfigManager::init() {
	try {
		for (filesystem::directory_entry const& entry : filesystem::directory_iterator(filesystem::absolute(CONFIG_FOLDER))) {
			enterConfigFile(entry.path().string());
		}
	}
	catch (std::filesystem::filesystem_error e) {
		std::cerr << e.what() << '\n';
	}

	/*for (unordered_map<string, ConfigItem>::iterator it = cfg.begin(); it != cfg.end(); ++it) {
		std::cout << it->first << ": \"" << it->second.s << "\"\n";
	}*/
}
void ConfigManager::destruct() {

}

void ConfigManager::enterConfigFile(string path) {
	ifstream fs(path);
	string name, sval;
	ConfigItem item;

	while (!fs.eof()) {
		fs >> item.type >> name;
		getline(fs, sval, '\n');
		sval = sval.substr(1);
		item.s = sval;
		if (item.type == 'i') { item.i = stoi(sval); }
		else if (item.type == 'f') { item.f = stof(sval); }
		cfg.insert({ name, item });
	}
	fs.close();
}	

