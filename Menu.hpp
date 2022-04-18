#include<iostream>
#include <fstream>
#include <string>
using namespace std;

CListaSimple<string>* folders = new CListaSimple<string>();
CListaSimple<string>* contrasenias = new CListaSimple<string>();
CListaSimple<string>* detallesContrasenias = new CListaSimple<string>();
CVector<string>* urls = new CVector<string>();
CVector<string>* usuarios = new CVector<string>();
CVector<string>* claves = new CVector<string>();
CVector<string>* notasT = new CVector<string>();

void menu();

void agregarEspecificacionesContrasenia(string nombre) {
	ofstream archivo;
	string url;
	string usuario;
	string contrasenia;
	string notas;

	cout << "Escriba la url de la pagina web: ";
	cin >> url;
	urls->agregarAlFinal(url);
	cout << "Escriba el usuario ligado a la contraseña: ";
	cin >> usuario;
	usuarios->agregarAlFinal(usuario);
	cout << "Escriba la contrasenia que desea guardar: ";
	cin >> contrasenia;
	claves->agregarAlFinal(contrasenia);
	cout << "Escriba una nota para recordar la contrasenia (separando palabras con _ ): ";
	cin >> notas;
	notasT->agregarAlFinal(notas);

	archivo.open(nombre + ".txt", ios::app);

	if (archivo.is_open()) {
		archivo << url << endl;
		archivo << usuario << endl;
		archivo << contrasenia << endl;
		archivo << notas;

		archivo.close();
	}
}

void agregarContrasenia(string nombreFolder) {
	ofstream archivo;
	string nombre;
	
	cout << "Escriba el nombre con el que desea guardar la contrasenia: ";
	cin >> nombre;

	archivo.open(nombreFolder + ".txt", ios::app);

	if (archivo.is_open()) {
		archivo << nombre << endl;

		archivo.close();
	}
	
	agregarEspecificacionesContrasenia(nombre);
}

void verContrasenias(string nombreFolder) { //arreglar que no se ven los datos de las contrasenias ingresadas
	ifstream archivo;
	string texto;

	archivo.open(nombreFolder + ".txt", ios::in);

	if (archivo.is_open())
	{
		while (!archivo.eof())
		{
			//leeemos linea por linea
			getline(archivo, texto);
			contrasenias->agregarAlFinal(texto);
		}
		contrasenias->imprimeDatos();
	}
	else {
		cout << "\nEl archivo no existe";
	}
	contrasenias->vaciarLista();
}

void verDetallesContrasenia() {
	ifstream archivo;
	string texto;
	string nombre;

	cout << "Ingrese el nombre de la contrasenia de la cual desea conocer las especificaciones: ";
	cin >> nombre;

	archivo.open(nombre + ".txt", ios::in);

	if (archivo.is_open())
	{
		while (!archivo.eof())
		{
			//leeemos linea por linea
			getline(archivo, texto);
			detallesContrasenias->agregarAlFinal(texto);
		}
		cout << "\nURL USUARIO CONTRASENIA NOTAS\n";
		detallesContrasenias->imprimeDatos();
	}
	else {
		cout << "\nEl archivo no existe";
	}
	detallesContrasenias->vaciarLista();
}

void verURLs() {
	cout << "\nUrls de este folder:\n";
	urls->imprimirVector();
	urls->vaciarVector();
	menu();
}

void verUsuarios() {
	cout << "\nUsuarios en este folder:\n";
	usuarios->imprimirVector();
	usuarios->vaciarVector();
	menu();
}

void verClaves() {
	cout << "\nClaves de este folder:\n";
	claves->imprimirVector();
	claves->vaciarVector();
	menu();
}

void verNotas() {
	cout << "\nNotas de este folder:\n";
	notasT->imprimirVector();
	notasT->vaciarVector();
	menu();
}

void ingresarAFolder() {
	string folderElegido;
	string texto;
	int eleccion;
	ofstream archivo1;
	ifstream archivo2;

	cout << "Ingrese el nombre del folder al que desea ingresar: ";
	cin >> folderElegido;

	archivo2.open("folderes.txt", ios::in);
	if (archivo2.is_open())
	{
		if (folders->getTamanio() == 0) { //si la lista está vacía
			while (!archivo2.eof())
			{
				//leeemos linea por linea
				getline(archivo2, texto);
				folders->agregarAlFinal(texto);
			}
		}
		archivo2.close();
	}

	if (folders->verificarExistencia(folderElegido)==true) {
		archivo1.open(folderElegido + ".txt", ios::app);

		cout << "\n\tElija una opcion:\n";
		cout << "1) Agregar contrasenia\n";
		cout << "2) Ver contrasenias guardadas\n";
		cout << "3) Ver detalles de contrasenia\n";
		cin >> eleccion;

		switch (eleccion)
		{
		case 1:
			agregarContrasenia(folderElegido);
			menu();
			break;
		case 2:
			verContrasenias(folderElegido);
			menu();
			break;
		case 3:
			verDetallesContrasenia();
			menu();
			break;
		default:
			break;
		}
	}
	else {
		cout << "El folder elegido no existe.";
	}
}

void crearFolder() {
	ofstream archivo;
	string nuevoFolder;

	cout << "Ingrese el nombre del nuevo folder: ";
	cin >> nuevoFolder;
	
	archivo.open("folderes.txt", ios::app);

	if (archivo.is_open()) {
		archivo << nuevoFolder << endl;

		archivo.close();
	}

	folders->agregarAlFinal(nuevoFolder);

	cout << "Folder creado con exito.";
}

void verFolderes() {
	ifstream archivo;
	string texto;

	archivo.open("folderes.txt", ios::in);
	if (archivo.is_open())
	{
		if (folders->getTamanio() == 0) { //si la lista está vacía
			while (!archivo.eof())
			{
				//leeemos linea por linea
				getline(archivo, texto);
				folders->agregarAlFinal(texto);
			}
			folders->imprimeDatos();
		}
		else { //si la lista ya tiene elementos
			folders->imprimeDatos();
		}
		archivo.close();
	}
}

void menu() {
	int eleccion;

	cout << "\n\tMenu\n";
	cout << "1) Ingresar a folder.\n";
	cout << "2) Crear folder.\n";
	cout << "3) Ver folderes.\n";
	cout << "4) Ver todas las URLs guardadas en los folderes.\n";
	cout << "5) Ver todos los usuarios guardados en los folder.\n";
	cout << "6) Ver todas las claves guardadas en los folder.\n";
	cout << "7) Ver todas las notas guardadas en los folder.\n";
	cout << "8) Salir\n";
	cout << "\nIngrese una opcion: ";
	cin >> eleccion;

	switch (eleccion)
	{
	case 1:
		ingresarAFolder();
		break;
	case 2:
		crearFolder();
		menu();
		break;
	case 3:
		verFolderes();
		menu(); 
		break;
	case 4:
		verURLs();
		menu();
		break;
	case 5:
		verUsuarios();
		menu();
		break;
	case 6:
		verClaves();
		menu();
		break;
	case 7:
		verNotas();
		menu();
		break;
	case 8:
		exit(0);
	default:
		break;
	}
}