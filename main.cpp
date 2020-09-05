#include "json.h"
int main()
{
	Myjson json("test.json");
	json.OpenFile();
	json.StartReadArray(0);
	std::string strArrayName = json.GetCurrentArrayName();
	while (json.HasNextObject())
	{
		rapidjson::Value::ConstObject object = json.GetNextObject();
		std::string strName = object["classify"].GetString();
	}
	
}