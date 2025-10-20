#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <limits>
#include <iomanip>
#include <iostream>

using namespace std;


struct Patient
{
    int id; // айди
    string surname; // фамилия пациента
    string diagnoz; // диагноз
    string doctor; // лечащий врач
    int age; // возраст пациента
    int palata; // палата пациента
    double temperture; // температура пациента
};

Patient* patients = nullptr;
int patientsCount = 0;
int capacity = 0;


void read_file(){
    //читаем файл
    ifstream file("patients.txt");
    if (!file.is_open()){
        cout<<"Error!"<<endl;
        return;
    }

    //считаем количество строк для задания размера массива
    int count = 0;
    string line;
    while (getline(file,line)){
        count++;
    }

    file.clear();  // Сбрасываем флаги ошибок
    file.seekg(0); // Возвращаемся в начало файла

    //задаем динамический массив
    capacity = count + 10; //запас 10
    patients = new Patient[capacity];
    patientsCount = count;
    

    // чтение данных
    for (int i=0; i < count ;i++){
        file >> patients[i].id >> patients[i].surname >> patients[i].diagnoz >> patients[i].doctor >> patients[i].age >> patients[i].palata >> patients[i].temperture;
    };
    file.close();
}


void show_massive(){
    for (int i=0; i < patientsCount;i++){
        cout<<"-----------------"<< endl;
        cout <<"ID: " << patients[i].id << endl;
        cout <<"Фамилия И.О.: " << patients[i].surname << endl;
        cout <<"Диагноз: " << patients[i].diagnoz << endl;
        cout <<"Лечащий врач: " << patients[i].doctor << endl;
        cout <<"Возраст: " << patients[i].age << endl;
        cout <<"Палата №" << patients[i].palata << endl;
        cout <<"Температура тела: " << patients[i].temperture << endl;
        cout<<"-----------------"<< endl;
    }
}


void increase_massive(){
    //увеличиваем вместимость вдвое
    int new_capacity = capacity*2;
    //создаем новый дм
    Patient* new_patients = new Patient[new_capacity];
    //копируем в новый из старого
    for (int i=0; i<=patientsCount;i++){
        new_patients[i] = patients[i];
    }
    //освобождаем память
    delete[] patients;
    //переобзначаем
    patients = new_patients;
    capacity = new_capacity;

}


void delete_patient(){
    //проверка есть ли пациенты
    if (patientsCount == 0){
        cout<<"В списке и так никого нету!";
        return;
    }

    int ID;
    cout<<"Введите номер ID пациента, которого вы хотите удалить: "; cin>>ID;
    for (int i=0; i<patientsCount ; i++){
        if (ID == patients[i].id){  // нашли айди
            for (int j = i; j < patientsCount-1; j++){
                patients[j] = patients[j+1]; //сместили все элементы влево
            }
            patientsCount--; //уменьшили число пациентов
            cout<<"Пациент удален!";
            return;
        }
    }
    cout<<"Пациент не найден!"<<endl; 
};


void add_patient(){
    //новый пациент
    Patient newPatient;
    //проверка на размер дм
    if (patientsCount >= capacity){
        //если места мало, увеличиваем массив
        increase_massive();
    }
    //+1 айди
    newPatient.id = patientsCount + 1;
    cout<<"Введите фамилия_И.О. (пациента): "; cin>>newPatient.surname;
    cout<<"Введите диагноз: "; cin>>newPatient.diagnoz;
    cout<<"Введите лечащего врача Фамилия_И.О."; cin>>newPatient.doctor;
    cout<<"Введите возраст пациента: "; cin>>newPatient.age;
    cout<<"Введите номер палаты №"; cin>>newPatient.palata;
    cout<<"Введите текущую температуру пациента"; cin>>newPatient.temperture;
    
    //добавляем нового пациента
    patients[patientsCount] = newPatient;
    patientsCount++;
}

void change_patient(){
    cout<<"Введите ID пациента для изменения";
    int ID;
    cin>>ID;
    bool found = false;
    for (int i=0; i < patientsCount; i++){
        if (ID == patients[i].id){
            found = true;

            cout << "Что вы хотите изменить?" << endl;
            cout << "1. Лечащего врача" << endl;
            cout << "2. Возраст" << endl;
            cout << "3. Номер палаты" << endl;

            int chs; cin>>chs;

            switch (chs) {
                case 0:
                cout<<"Error";
                break;
                case 1:{ // фио врача
                    cout << "Введите нового врача: ";
                    string new_doctor; cin>>new_doctor;
                    patients[i].doctor = new_doctor;
                    cout << "Данные врача обновлены!" << endl;
                    break;
                }
                case 2:{ // температура
                    cout << "Введите новый возраст: ";
                    int new_age; cin>>new_age;
                    patients[i].age = new_age;
                    cout << "Возраст обновлен!" << endl;
                    break;
                }
                case 3:{ // номер палаты
                    cout << "Введите новую палату: ";
                    int new_palata; cin>>new_palata;
                    patients[i].palata = new_palata;
                    cout << "Номер палаты обновлен!" << endl;
                    break;
                }
                default:
                    cout<<"Error";
            }
            break;
        }
    }
    if (!found){
        cout<<"Пациент не найден!";
    };
    cin.clear(); // на случай, если предыдущий ввод завершился с ошибкой
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


void calculate(){
    //средняя температура
    //максимальный и минимальный возраст
    //средний возраст
    //колво пациентов
    double ageall = 0;
    int max_age = patients[0].age;
    int min_age = patients[0].age;
    for (int i=0; i< patientsCount; i++){
        ageall += patients[i].age;
        if (max_age<patients[i].age) max_age = patients[i].age;
        if (min_age>patients[i].age) min_age = patients[i].age;
    }
    cout<<"===СТАТИСТИКА==="<<endl;
    cout<<"Количество пациентов: "<<patientsCount<<endl;
    cout<<"Средний возраст пациентов: "<< ageall / patientsCount<<endl;
    cout<<"Максимальный возраст: "<< max_age<<endl;
    cout<<"Минимальный возраст: "<< min_age<<endl;
}

void save_to_file(){
    string filename;
    cout<<"Введите имя нового файла: "; cin>>filename;
    size_t dot = filename.find_last_of('.');
    if (dot != string::npos){
        filename = filename.substr(0,dot); //только имя без расширения
    }
    filename+=".txt";
    
    ofstream file(filename);
    if (!file.is_open()){
        cout<<"Ошибка создания файла!"<<endl;
        return;
    }

    for (int i=0; i<patientsCount; i++){
        file << patients[i].id << " " << patients[i].surname<< " "  << patients[i].diagnoz<< " "  << patients[i].doctor<< " "  << patients[i].age<< " "  << patients[i].palata<< " "  << patients[i].temperture;
        if (i < (patientsCount- 1)) file<<endl;
    }
    file.close();
    cout<<"данные сохранены в файл: "<< filename<<endl;
    Sleep(5000);

}

int main(){
    read_file();
    system("chcp 65001 > nul");
    
    bool flag = true;
    while (flag){
        cout<<u8"Медицина. Выберите действие (1-3). \n 1. Показать всех \n 2. Добавить \n 3. Удалить \n 4. Изменить \n 5. Показать статистику \n 6. выйти + сохранить файл"<<endl;
        int choice;
        cin >> choice;
        switch (choice){
            case 0:
                cout<<"wrong choice!";
                break;
            case 1:
                show_massive();
                cout<<"Введите Enter для продолжения"<<endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                system("cls");
                break;
            case 2:
                add_patient();
                break;
            case 3:
                delete_patient();
                break;
            case 4:
                change_patient();
                break;
            case 5:
                calculate();
                cout<<"Введите Enter для продолжения"<<endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                system("cls");
                break;
            case 6:
                save_to_file();
                flag = false;
                break;
            default:
                cout<<"eh";
        };

    };
    if (patients != nullptr) {
        delete[] patients;
    }
    return 0;
}
