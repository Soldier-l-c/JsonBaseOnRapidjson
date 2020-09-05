#include "json.h"
Myjson::Myjson(const QString& jsonFilepath):m_qsJsonFilePath(jsonFilepath)
{
	m_nCurrentArrayIndex = 0;
	m_nCurrentObjectIndex = 0;
}

QString Myjson::GetCurrentArrayName()
{
	if (m_nCurrentArrayIndex >= m_vecArrayIter.size())return "";
	return m_vecArrayIter[m_nCurrentArrayIndex]->name.GetString();
}

int32_t Myjson::GetNumOfArray()
{
	return m_vecArrayIter.size();
}

int32_t Myjson::OpenFile()
{
	std::ifstream in(m_qsJsonFilePath.toStdString().c_str());
	if (!in.is_open()) {
		fprintf(stderr, "fail to read json file: %s\n", m_qsJsonFilePath.toStdString().c_str());
		return -1;
	}
	std::string json_content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	in.close();

	m_docDocument.Parse(json_content.c_str());
	if (!m_docDocument.IsObject())
	{
		return -1;
	}

	for (auto iter = m_docDocument.MemberBegin(); iter != m_docDocument.MemberEnd(); ++iter)
	{
		assert(iter->value.IsArray());
		m_vecArrayIter.push_back(iter);
	}

}

/*未解决安全问题*/
rapidjson::Value::ConstObject Myjson::GetNextObject()
{
	assert(m_vecArrayIter[m_nCurrentArrayIndex]->value.GetArray()[m_nCurrentObjectIndex].IsObject());
	return m_vecArrayIter[m_nCurrentArrayIndex]->value.GetArray()[m_nCurrentObjectIndex++].GetObject();
}

int32_t Myjson::GetNumOfObject(int32_t arryIndex)
{
	if (arryIndex < 0)arryIndex = m_nCurrentArrayIndex;
	if (arryIndex >= m_vecArrayIter.size())return 0;
	return m_vecArrayIter[arryIndex]->value.GetArray().Size();
}

void Myjson::StartReadArray(const int32_t& arrayIndex)
{
	m_nCurrentArrayIndex = arrayIndex;
	m_nCurrentObjectIndex = 0;
}

bool Myjson::HasNextObject()
{
	if (m_nCurrentArrayIndex >= m_vecArrayIter.size())return false;
	return m_nCurrentObjectIndex >=0 && m_nCurrentObjectIndex < m_vecArrayIter[m_nCurrentArrayIndex]->value.GetArray().Size();
}

Myjson::~Myjson()
{
}