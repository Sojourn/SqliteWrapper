#include <iostream>
#include <SqliteWrapper/SqliteWrapper.h>
#include <memory>

int main(int arc, char **argv)
{
	auto db = sqlite::Connection::Create(":memory:", sqlite::Connection::OPEN_READWRITE);
	// db->Exec("create temp table entity(id int primary key);");
	//db->Exec("select * from entity;", [](int argc, char** argv, char** colv) -> bool
	//{
	//	for(auto i = 0; i < argc; i++)
	//	{
	//		std::cout << argv[0] ? argv[0] : nullptr;
	//	}
	//	std::cout << std::endl;
	//	return true;
	//});

	sqlite::Row *row;

	auto create = db->Prepare("create temp table entity(id int primary key, name text);");
	create->Step(nullptr);
	
	auto insert = db->Prepare("insert into entity(id, name) values($a, $b);");
	insert->BindInteger(1, 0);
	insert->BindText(2, "Stuff");
	insert->Step(nullptr);

	insert->Reset();
	insert->BindInteger(1, 1);
	insert->BindText(2, "Other stuff");
	insert->Step(&row);

	auto select = db->Prepare("select * from entity;");
	while(select->Step(&row))
	{
		for(size_t i = 0; i < row->ColumnCount(); i++)
		{
			std::string value;
			if(row->GetText(i, &value))
			{
				std::cout << value << " | ";
			}
		}
		std::cout << std::endl;
	}

	std::system("pause");
	return 0;
}