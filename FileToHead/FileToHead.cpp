#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

int main()
{
    // 读取文件到字节数组
    std::string fileName = "HitBoxex";
    std::string fileExit = ".png";

    std::ifstream file(fileName + fileExit, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size))
    {
        // 处理文件读取错误
        return 1;
    }

    // 将字节数组转换为十六进制字符串
    std::ostringstream oss;
    for (char c : buffer)
    {
        oss << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)c << ", ";
    }
    std::string hexString = oss.str();

    // 将十六进制字符串和数据大小保存到.h文件
    std::ofstream headerFile(fileName + ".h");
    headerFile << "#pragma once\n\n";
    headerFile << "const int " << fileName + "_size = " << buffer.size() << ";\n";
    headerFile << "unsigned char " << fileName + "_buff[] = {\n";
    headerFile << hexString;
    headerFile << "\n};\n";
    headerFile.close();

    return 0;
}
