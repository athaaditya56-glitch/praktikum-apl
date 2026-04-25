#include <iostream>
#include <cctype>
#include <stdexcept>
using namespace std;

struct RekamMedis{
    string id;
    string nama;
    string tanggal;
    string diagnosis;
    string terapi;
    string catatan;
};

struct User{
    string username;
    string password;
    RekamMedis data[100];
    int jumlahData=0;
};

// ================= VALIDASI =================
void cekInput(){
    if(cin.fail()){
        cin.clear();
        cin.ignore(1000,'\n');
        throw invalid_argument("Input harus berupa angka!");
    }
}

// ================= AMBIL ANGKA =================
int ambilAngka(string id){
    int angka = 0;
    for(int i=0;i<id.length();i++){
        if(isdigit(id[i])){
            angka = angka * 10 + (id[i]-'0');
        }
    }
    return angka;
}

// ================= LOGIN =================
bool loginUser(User &user){
    int percobaan=0;
    string username,password;

    try{
        while(percobaan<3){
            cout<<" LOGIN "<<endl;

            cout<<"Username: ";
            cin>>username;

            cout<<"Password: ";
            cin>>password;

            if(username==user.username && password==user.password){
                cout<<"Login berhasil!"<<endl;
                return true;
            }
            else{
                percobaan++;
                cout<<"Username/password salah ("<<percobaan<<"/3)"<<endl;
            }
        }

        throw runtime_error("Program berhenti!");
    }
    catch(exception &e){
        cout<<e.what()<<endl;
        return false;
    }
}

// ================= TAMBAH DATA =================
void tambahData(User &user){
    try{
        cout<<" CREATE DATA PASIEN "<<endl;

        if(user.jumlahData >= 100){
            throw length_error("Data penuh!");
        }

        int i = user.jumlahData;
        cin.ignore();

        cout<<"ID Pasien: ";
        getline(cin,user.data[i].id);

        cout<<"Nama Pasien: ";
        getline(cin,user.data[i].nama);

        cout<<"Tanggal (YYYY-MM-DD): ";
        getline(cin,user.data[i].tanggal);

        cout<<"Diagnosis: ";
        getline(cin,user.data[i].diagnosis);

        cout<<"Terapi: ";
        getline(cin,user.data[i].terapi);

        cout<<"Catatan: ";
        getline(cin,user.data[i].catatan);

        user.jumlahData++;

        cout<<"Data berhasil ditambahkan"<<endl;
    }
    catch(exception &e){
        cout<<"Error: "<<e.what()<<endl;
    }
}

// ================= LIHAT DATA =================
void lihatData(User &user){
    try{
        cout<<" DAFTAR REKAM MEDIS "<<endl;

        if(user.jumlahData==0){
            throw runtime_error("Belum ada data");
        }

        cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"No\tID\tNama\t\tTanggal\t\tDiagnosis\tTerapi\t\tCatatan"<<endl;
        cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;

        for(int i=0;i<user.jumlahData;i++){
            cout<<i+1<<"\t"
                <<user.data[i].id<<"\t"
                <<user.data[i].nama<<"\t\t"
                <<user.data[i].tanggal<<"\t"
                <<user.data[i].diagnosis<<"\t\t"
                <<user.data[i].terapi<<"\t\t"
                <<user.data[i].catatan<<endl;
        }
    }
    catch(exception &e){
        cout<<e.what()<<endl;
    }
}

// ================= UBAH DATA =================
void ubahData(User &user){
    try{
        int n;
        cout<<"Nomor data: ";
        cin>>n;
        cekInput();
        cin.ignore();

        n--;

        if(!(n>=0 && n<user.jumlahData)){
            throw out_of_range("Data tidak ditemukan");
        }

        cout<<"ID baru: ";
        getline(cin,user.data[n].id);

        cout<<"Nama baru: ";
        getline(cin,user.data[n].nama);

        cout<<"Tanggal baru: ";
        getline(cin,user.data[n].tanggal);

        cout<<"Diagnosis baru: ";
        getline(cin,user.data[n].diagnosis);

        cout<<"Terapi baru: ";
        getline(cin,user.data[n].terapi);

        cout<<"Catatan baru: ";
        getline(cin,user.data[n].catatan);

        cout<<"Data berhasil diubah"<<endl;
    }
    catch(exception &e){
        cout<<e.what()<<endl;
    }
}

// ================= HAPUS DATA =================
void hapusData(User *user){
    try{
        int n;
        cout<<"Nomor data: ";
        cin>>n;
        cekInput();

        n--;

        if(!(n>=0 && n<user->jumlahData)){
            throw out_of_range("Data tidak ditemukan");
        }

        for(int i=n;i<user->jumlahData-1;i++){
            user->data[i]=user->data[i+1];
        }
        user->jumlahData--;
        cout<<"Data berhasil dihapus"<<endl;
    }
    catch(exception &e){
        cout<<e.what()<<endl;
    }
}

// ================= SORTING =================

// quick sort (Nama Desc)
int partitionNama(User &user,int low,int high){
    string pivot = user.data[high].nama;
    int i=low-1;

    for(int j=low;j<high;j++){
        if(user.data[j].nama > pivot){
            i++;
            swap(user.data[i],user.data[j]);
        }
    }

    swap(user.data[i+1],user.data[high]);
    return i+1;
}

void quickSortNama(User &user,int low,int high){
    if(low<high){
        int pi = partitionNama(user,low,high);
        quickSortNama(user,low,pi-1);
        quickSortNama(user,pi+1,high);
    }
}

// SELECTION SORT (ID ASC)
void selectionSortID(User &user){
    for(int i=0;i<user.jumlahData-1;i++){
        int min=i;
        for(int j=i+1;j<user.jumlahData;j++){
            if(ambilAngka(user.data[j].id) < ambilAngka(user.data[min].id)){
                min=j;
            }
        }
        swap(user.data[i],user.data[min]);
    }
}

// INSERTION SORT (Tanggal ASC)
void insertionSortTanggal(User &user){
    for(int i=1;i<user.jumlahData;i++){
        RekamMedis key = user.data[i];
        int j=i-1;

        while(j>=0 && user.data[j].tanggal > key.tanggal){
            user.data[j+1]=user.data[j];
            j--;
        }

        user.data[j+1]=key;
    }
}

// ================= SEARCHING =================

// BINARY SEARCH (ID)
int binarySearchID(User *user, int key){
    int low = 0;
    int high = user->jumlahData - 1;

    while(low <= high){
        int mid = (low + high) / 2;
        int nilaiMid = ambilAngka(user->data[mid].id);

        if(nilaiMid == key) return mid;
        else if(nilaiMid < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// LINEAR SEARCH (Nama)
int linearSearchNama(User *user, string key){
    for(int i=0;i<user->jumlahData;i++){
        if(user->data[i].nama == key){
            return i;
        }
    }
    return -1;
}

// ================= FUNGSI SEARCH =================
void cariID(User *user){
    try{
        if(user->jumlahData==0){
            throw runtime_error("Data kosong");
        }

        int key;
        cout<<"Masukkan ID (angka): ";
        cin>>key;
        cekInput();

        selectionSortID(*user);

        int hasil = binarySearchID(user,key);

        if(hasil!=-1){
            cout<<"Data ditemukan:\n";
            cout<<user->data[hasil].id<<" - "<<user->data[hasil].nama<<endl;
        } else {
            throw runtime_error("Data tidak ditemukan");
        }
    }
    catch(exception &e){
        cout<<e.what()<<endl;
    }
}

void cariNama(User *user){
    try{
        if(user->jumlahData==0){
            throw runtime_error("Data kosong");
        }

        string key;
        cin.ignore();
        cout<<"Masukkan nama: ";
        getline(cin,key);

        int hasil = linearSearchNama(user,key);

        if(hasil!=-1){
            cout<<"Data ditemukan:\n";
            cout<<user->data[hasil].id<<" - "<<user->data[hasil].nama<<endl;
        } else {
            throw runtime_error("Data tidak ditemukan");
        }
    }
    catch(exception &e){
        cout<<e.what()<<endl;
    }
}

// ================= MAIN =================
int main(){
    User user;
    user.username="Aditya";
    user.password="082";

    if(!loginUser(user)) return 0;

    int pilih;

    do{
        cout<<"\nMENU\n";
        cout<<"1. Tambah\n";
        cout<<"2. Lihat\n";
        cout<<"3. Ubah\n";
        cout<<"4. Hapus\n";
        cout<<"5. Sort Nama\n";
        cout<<"6. Sort ID\n";
        cout<<"7. Sort Tanggal\n";
        cout<<"8. Cari ID\n";
        cout<<"9. Cari Nama\n";
        cout<<"10. Logout\n";
        cout<<"Pilih: ";
        cin>>pilih;

        try{
            cekInput();

            if(pilih==1) tambahData(user);
            else if(pilih==2) lihatData(user);
            else if(pilih==3) ubahData(user);
            else if(pilih==4) hapusData(&user);

            else if(pilih==5){
                if(user.jumlahData==0){
                    cout<<"Tidak ada data"<<endl;
                } else {
                    quickSortNama(user,0,user.jumlahData-1);
                    cout<<"Sorting nama DESC berhasil"<<endl;
                }
            }

            else if(pilih==6){
                if(user.jumlahData==0){
                    cout<<"Tidak ada data"<<endl;
                } else {
                    selectionSortID(user);
                    cout<<"Sorting ID ASC berhasil"<<endl;
                }
            }

            else if(pilih==7){
                if(user.jumlahData==0){
                    cout<<"Tidak ada data"<<endl;
                } else {
                    insertionSortTanggal(user);
                    cout<<"Sorting tanggal ASC berhasil"<<endl;
                }
            }

            else if(pilih==8) cariID(&user);
            else if(pilih==9) cariNama(&user);

        }
        catch(exception &e){
            cout<<"Error: "<<e.what()<<endl;
        }

    }while(pilih!=10);

    cout<<"Logout..."<<endl;
}