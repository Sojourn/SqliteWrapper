#include <iostream>
#include <SqliteWrapper/SqliteWrapper.h>
#include <memory>

int main(int arc, char **argv)
{
	auto db = sqlite::Connection::Create(":memory:", sqlite::Connection::OPEN_READWRITE);
	db->Exec("create temp table entity(id int primary key);");
	db->Exec("insert into entity(id) values(1);");
	db->Exec("insert into entity(id) values(2);");
	//db->Exec("select * from entity;", [](int argc, char** argv, char** colv) -> bool
	//{
	//	for(auto i = 0; i < argc; i++)
	//	{
	//		std::cout << argv[0] ? argv[0] : nullptr;
	//	}
	//	std::cout << std::endl;
	//	return true;
	//});

	auto stmt = db->Prepare("select * from entity;");
	sqlite::Row *row;

	while(stmt->Step(&row))
	{
		std::string value;
		if(row->GetText(0, &value))
		{
			std::cout << value << std::endl;
		}
	}

	std::system("pause");
	return 0;
}