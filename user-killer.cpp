#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <locale.h>


using namespace std;

#define TEMP_FILE "data.bin"
#define servidor "<Nome do Servidor>"

vector<string> readUsers() {
	vector<string> data;
		
	ifstream infile;
	infile.open(TEMP_FILE);
	
	while (!infile.eof()) {
		string line;
		getline(infile, line);
		if (line[1] == ' ') 
			line[1] = '#';
		data.push_back(line);
	}
	
	infile.close();
	
	return data;
}

vector<string> split(const string &input) {
	istringstream buffer(input);
	
	vector<string> result(
		(istream_iterator<string>(buffer)),
		istream_iterator<string>()
	);
	
	return result;
}

string getID(string userToKill, vector<string> arr) {
	for (int i = 1; i < arr.size(); i++) {
		vector<string> line = split(arr[i]); 
		if (line.size() > 2 && line[1].compare(userToKill) == 0)
			return line[2];
	}
	
	return "";
}

int main(int argc, char* argv[]) {
	
	setlocale(LC_ALL, "");
	
	cout << "User Killer - 2017 Versão 1.0" << endl;
	cout << "Autores: Lucas Teles e Eduardo Miranda" << endl;
	cout << "Futura Comunicação e Desenvolvimento" << endl << endl; 
	
	string userToKill;
	char command[50];
	
	if (argc < 2) {
		system("color 47");
		cout << "Uso não autorizado, contacte seu administrador de rede!" << endl << endl;
		system("pause");
		return 1;
	} else {
		string aux (argv[1]);
		
		if (aux.compare("--lucilei") == 0) {
			cout << "Informe o nome do usuário: " << endl;
			cin >> userToKill;
		} else {
			cout << "Alvo: " << argv[1] << endl;
			userToKill = argv[1];
		} 
	}

	cout << endl << "Procurando usuário..." << endl;
	
	sprintf(command, "query session /server:" << servidor << "> %s", TEMP_FILE);
	system(command);
	
//	if (system(command) > 0) {
//		cout << endl << "Erro! Não foi possível comunicar com o servidor!'" << endl;
//		system("pause");
//		
//		return 1;
//	}
	
	string id = ( getID(userToKill, readUsers()) );
	
	if (id.empty()) {
		cout << endl << "Usuário não encontrado!" << endl << endl;
		system("pause");
		return 1;
	}
	
	cout << "Derrubando..." << endl;
	
	sprintf(command, "logoff %s /server:ts-server", id.c_str());
	if (system(command) == 0) {
		cout << endl << "Usuário " << userToKill << " derrubado!" << endl << endl;
		system("pause");
		
		return 0;
	} else {
		cout << endl << "Erro! Não foi possível derrubar o usuário.'" << endl;
		system("pause");
		
		return 1;
	}
}
