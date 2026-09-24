#include <string>
#include <unistd.h>

using namespace std;
inline string media_path(const string& filename) {
    char executable_path[4096] = {};
    ssize_t length = readlink("/proc/self/exe", executable_path,
                              sizeof(executable_path) - 1);
    if (length <= 0) return "../../media/" + filename;

    string path(executable_path, length);
    size_t separator = path.rfind('/');
    if (separator != string::npos) path.resize(separator);
    separator = path.rfind('/');
    if (separator != string::npos) path.resize(separator);
    return path + "/media/" + filename;
}
