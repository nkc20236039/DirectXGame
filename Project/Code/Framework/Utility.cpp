#include <string>

std::wstring convertWstringPath(const std::string& path) {
	// もし`/`でパスが区切られていたら`\\`に変更する
	std::string normalizedPath = path;
	normalizedPath.replace(path.begin(), path.end(), "/", "\\");
	// バッファの大きさを求める
	size_t bufferSize = normalizedPath.length() + 1;
	// stringをwchar_tに変換する
	std::wstring wStr(bufferSize, L'\0');
	size_t convertedChars = 0;
	// 変換を実行
	mbstowcs_s(&convertedChars, &wStr[0], bufferSize, normalizedPath.c_str(), bufferSize);
	// 実際の長さに調整（null終端を除く）
	wStr.resize(convertedChars - 1);

	return wStr;
}