#include <string>

class EnvVariablesGetter {
 public:
    explicit EnvVariablesGetter() {};
    std::string getValue(std::string const& key);
    std::string getDataPath();
    std::string getTexturesPath();
    std::string getMapsPath();
    std::string getSoundsPath();
    std::string getMusicPath();
};