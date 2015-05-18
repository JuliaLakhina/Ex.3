#define _CRT_SECURE_NO_WARNINGS
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "md5.cpp"
#include <Windows.h>
using namespace std;
using namespace boost::filesystem;
namespace pt = boost::property_tree;

void search(path dir_path)
{
	ofstream f("AbFiles.tsv");
	if (is_directory(dir_path) && exists(dir_path))
	{

		recursive_directory_iterator end;
		for (recursive_directory_iterator it(dir_path); it != end; ++it)
			if (is_regular_file(it->path()))
			{

				stringstream result;
				string a;
				ifstream myfile;
				myfile.open(it->path().string(), ios::binary);
				result << myfile.rdbuf();
				a = result.str();
				f << it->path().filename().string() << "\n" << it->path() << "\n" <<  file_size(it->path()) << "\n" <<  md5(a) << endl;
				f << endl;
				k = k + file_size(it->path());

				boost::property_tree::ptree tree;


				cout << "Do you want to save in json?" << endl;
				string c;

				if (c == "yes")
				{
					int i = 1;
					+
						+	//General size
						+int sizesize = 0;
					for (Fileinfo it : vec_finfo) {
						tree.put("File" + std::to_string(i), it->path);
						tree.put("Size" + std::to_string(i), file_size);
						tree.put("Hash" + std::to_string(i), a);
						i++;
						+
					}

					std::stringstream ss;
					boost::property_tree::write_json(ss, tree);
					const std::string result = ss.str();
					cout << result << endl;
					std::ofstream ofs("result.json");
					boost::property_tree::write_json(ofs, tree, true);
					ofs.close();

				}

				}
				else
				{
					cout << dir_path << " does not exist\n";
				}


			f.close();
			return;
};
void checkIn(path dir_path)
{
	ifstream f;
	f.open("AbFiles.tsv", ios::in);
	string str, a;
	vector <string> filename;
	vector <string> hash;
	vector <string> savfilename;
	vector <string> savhash;
	vector <int> flagok;
	while (!f.eof()){
		getline(f, str);
		a = str;
		savfilename.push_back(a);
		getline(f, str);
		getline(f, str);
		getline(f, str);
		a = str;
		savhash.push_back(a);
		getline(f, str);

	}
	f.close();
	if (is_directory(dir_path) && exists(dir_path))
	{

		recursive_directory_iterator end;
		for (recursive_directory_iterator it(dir_path); it != end; ++it)
			if (is_regular_file(it->path()))
			{

				stringstream result;
				string a;
				ifstream myfile;
				myfile.open(it->path().string(), ios::binary);
				result << myfile.rdbuf();
				a = result.str();
				hash.push_back(md5(a));
				filename.push_back(it->path().filename().string());
				flagok.push_back(0);
			}
	}
	else
	{
		cout << dir_path << " does not exist\n";
	}
	int flag = 0;
	for (int i = 0; i < savfilename.size() - 1; ++i)
	{
		for (int j = 0; j < filename.size(); ++j)
		{
			if ((savfilename[i] == filename[j]) & (savhash[i] == hash[j])& (flagok[j]==0))
			{
				flag = 1;flagok[j] = 1; break;
			}
			if ((savfilename[i] == filename[j]) & (savhash[i] != hash[j])& (flagok[j] == 0))
			{
				flagok[j] = 1;
				cout << "file " << savfilename[i] << " " << "was changed" << endl;
				flag = 1; break;
			}
			flag = 0;
		}
		if (flag == 0)
		{
			cout << "file " << savfilename[i] << " " << "was deleted" << endl;
		}
	}
	for (int i = 0; i < flagok.size(); ++i)
	{
		if (flagok[i] == 0){
			cout << filename[i] << " " << "was added" << endl;
		}
	}
	return;
};

int main(int argc, char* argv[1])
{
	setlocale(LC_ALL, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	identifier;
	
	cout << "If you want to search your files enter 1" << "\n" << "If you want to check your files enter 2" << endl;
	int y;
	cin >> y;
	cout << "Enter the directory path:\n" << std::endl;
	string dir_path;
	cin >> dir_path;
	if (exists(dir_path)){
		if (y == 1)
		{
			search(dir_path);
			cout << "search completed" << endl;
		}
		if (y == 2)
		{
			checkIn(dir_path);
			cout << "Other files did not change" << endl;
		}
	}
	else {
		cout << dir_path << " does not exist\n";
	}

	goto identifier;

	system("pause");
	return 0;
}
