#include <iostream>
#include "base/files/file_util.h"
#include "base/files/file_path.h"
#include "base/path_service.h"
#include "base/values.h"
#include "base/json/json_writer.h"

int main(int argc, char** argv) {


	int code = -1;
	std::string msg = "≤‚ ‘";
	std::map<std::string, std::string> data;
	data["aa"] = "bb";
	data["cc"] = "dd";
	base::DictionaryValue root_dict;
	root_dict.SetInteger("code", code);
	root_dict.SetString("msg", msg);

	if (!data.empty()) {
		scoped_ptr<base::DictionaryValue> data_dict(new base::DictionaryValue());
		for (auto &item : data) {
			data_dict->SetString(item.first, item.second);
		}

		root_dict.Set("data", std::move(data_dict));
	}
	std::string str;
	base::JSONWriter::Write(root_dict, &str);

	return 0;
}