#include <string>

std::wstring convertWstringPath(const std::string& path) {
	// ����`/`�Ńp�X����؂��Ă�����`\\`�ɕύX����
	std::string normalizedPath = path;
	normalizedPath.replace(path.begin(), path.end(), "/", "\\");
	// �o�b�t�@�̑傫�������߂�
	size_t bufferSize = normalizedPath.length() + 1;
	// string��wchar_t�ɕϊ�����
	std::wstring wStr(bufferSize, L'\0');
	size_t convertedChars = 0;
	// �ϊ������s
	mbstowcs_s(&convertedChars, &wStr[0], bufferSize, normalizedPath.c_str(), bufferSize);
	// ���ۂ̒����ɒ����inull�I�[�������j
	wStr.resize(convertedChars - 1);

	return wStr;
}