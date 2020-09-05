#pragma once
#include <rapidjson.h>
#include <document.h>
#include <stringbuffer.h>
#include <writer.h>
#include <iostream>
#include <fstream>
#include <string>
#include <QString>
#include <vector>
class Myjson
{
public:
	Myjson(const QString& filePath);
	~Myjson();
	int32_t OpenFile();
	void StartReadArray(const int32_t& arrayIndex);
	rapidjson::Value::ConstObject GetNextObject();
	bool HasNextObject();
	QString GetCurrentArrayName();
	int32_t GetNumOfArray();
	int32_t GetNumOfObject(int32_t arryIndex = -1);
private:
	QString m_qsJsonFilePath;
	rapidjson::Document m_docDocument;
	int32_t m_nCurrentObjectIndex; //当前所在的object下标
	int32_t m_nCurrentArrayIndex;  //当前array所在下标
	std::vector<rapidjson::Value::ConstMemberIterator> m_vecArrayIter; //存放第一层array节点
};